import base
import os
import shutil
import re
import utils
from utils import die

PACKAGE_NAME         = "openslp"
PACKAGE_VER          = "1.2.1"
PACKAGE_FULL_VER     = "1.2.1-2"
PACKAGE_FULL_NAME    = "%s-%s" % ( PACKAGE_NAME, PACKAGE_VER)
PACKAGE_DLL_NAME     = "libslp"

SRC_URI= """
http://mesh.dl.sourceforge.net/sourceforge/openslp/""" + PACKAGE_FULL_NAME + """.tar.gz
"""

DEPEND = """
"""

class subclass(base.baseclass):
  def __init__(self):
    base.baseclass.__init__( self, SRC_URI )
    self.instsrcdir = PACKAGE_FULL_NAME

  def execute( self ):
    base.baseclass.execute( self )
    if self.compiler <> "mingw":
      print "error: can only be build with MinGW (but in the end a \
             mingw/msvc combined package is created"
      exit( 1 )

  def unpack( self ):
    if( not base.baseclass.unpack( self ) ):
      return False
    src = os.path.join( self.workdir, self.instsrcdir )

    cmd = "cd %s && patch -p0 < %s" % \
          ( src, os.path.join( self.packagedir , "openslp-1.2.1.diff" ) )
    os.system( cmd ) or die
    
    return True

  def kdeDefaultDefines( self ):
    # adjust some vars for proper compile
    cmake_src  = os.path.join( self.workdir, self.instsrcdir )
    cmake_dest = os.path.join( self.imagedir, self.instdestdir )

    options = "%s -DCMAKE_INSTALL_PREFIX=%s " % \
              ( cmake_src, cmake_dest.replace( '\\', '/' ) )
    options = options + "-DCMAKE_INCLUDE_PATH=%s " % \
              os.path.join( self.rootdir, "win32libs", "include" ).replace( "\\", "/" )

    options = options + "-DCMAKE_LIBRARY_PATH=%s " % \
              os.path.join( self.rootdir, "win32libs", "lib" ).replace( "\\", "/" )

    return options

  def compile( self ):

    # we have an own cmake script - copy it to the right place
    cmake_script = os.path.join( self.packagedir , "CMakeLists.txt" )
    cmake_dest = os.path.join( self.workdir, self.instsrcdir, "CMakeLists.txt" )
    shutil.copy( cmake_script, cmake_dest )

    return self.kdeCompile()

  def install( self ):
    os.chdir( os.path.join( self.workdir, "%s-build" % self.package ) )
    os.system( "mingw32-make install" ) and die( "mingw32-make install" )

    return True

  def make_package( self ):
    # auto-create both import libs with the help of pexports
    self.createImportLibs( PACKAGE_DLL_NAME )

    # now do packaging with kdewin-packager
    self.doPackaging( PACKAGE_NAME, PACKAGE_FULL_VER, True )

    return True

subclass().execute()
