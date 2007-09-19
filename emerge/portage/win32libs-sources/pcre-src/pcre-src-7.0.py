import base
import os
import shutil
import utils
from utils import die

PACKAGE_NAME         = "pcre"
PACKAGE_VER          = "7.0"
PACKAGE_FULL_VER     = "7.0"
PACKAGE_FULL_NAME    = "%s-%s" % ( PACKAGE_NAME, PACKAGE_VER )
PACKAGE_DLL_NAME     = "pcre"

SRC_URI= """
ftp://ftp.csx.cam.ac.uk/pub/software/programming/pcre/""" + PACKAGE_FULL_NAME + """.tar.bz2
"""

# fixme: we only need jpeg as dependency!
DEPEND = """
dev-util/win32libs
"""

class subclass(base.baseclass):
  def __init__(self):
    base.baseclass.__init__( self, SRC_URI )
    self.createCombinedPackage = False
    self.instsrcdir = PACKAGE_FULL_NAME

  def kdeDefaultDefines( self ):
    # adjust some vars for proper compile
    cmake_src  = os.path.join( self.workdir, self.instsrcdir )
    cmake_dest = os.path.join( self.imagedir, self.instdestdir )

    options = "%s -DCMAKE_INSTALL_PREFIX=%s " % \
              ( cmake_src, cmake_dest.replace( '\\', '/' ) )
    #options = options + "-DCMAKE_INCLUDE_PATH=%s " % \
    #          os.path.join( self.rootdir, "win32libs", "include" ).replace( "\\", "/" )

    #options = options + "-DCMAKE_LIBRARY_PATH=%s " % \
    #          os.path.join( self.rootdir, "win32libs", "lib" ).replace( "\\", "/" )

    return options

  def compile( self ):

    files = """
CMakeLists.txt
cmake_uninstall.cmake.in
config.h.cmake
pcrecpparg.h.cmake
pcre_stringpiece.h.cmake
pcre.h.cmake
"""
    # we have an own cmake script - copy it to the right place
    src = self.packagedir
    dst = os.path.join( self.workdir, self.instsrcdir )
    for f in files.split():
        shutil.copy( os.path.join( src, f ), os.path.join( dst, f ) )

    return self.kdeCompile()

  def install( self ):
    return self.kdeInstall()

  def make_package( self ):
    # auto-create both import libs with the help of pexports
    self.stripLibs( PACKAGE_DLL_NAME )

    # now do packaging with kdewin-packager
    self.doPackaging( PACKAGE_NAME, PACKAGE_FULL_VER, True )

    return True
  
subclass().execute()
