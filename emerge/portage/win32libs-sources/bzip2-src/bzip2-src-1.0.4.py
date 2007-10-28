import base
import os
import shutil
import utils
from utils import die

PACKAGE_NAME         = "libbzip2"
PACKAGE_VER          = "1.0.4"
PACKAGE_FULL_VER     = "1.0.4-5"
PACKAGE_FULL_NAME    = "%s-%s" % ( PACKAGE_NAME, PACKAGE_VER )
PACKAGE_DLL_NAME     = "bzip2"

SRC_URI= """
http://www.bzip.org/1.0.4/bzip2-1.0.4.tar.gz
"""

DEPEND = """
"""

class subclass(base.baseclass):
  def __init__(self):
    base.baseclass.__init__( self, SRC_URI )
    self.instsrcdir = "bzip2-1.0.4"
    self.instdestdir = "kde"
    self.createCombinedPackage = True
    self.buildType = "Release"

  def unpack( self ):
    if( not base.baseclass.unpack( self ) ):
      return False
    # we have an own cmake script - copy it to the right place
    cmake_script = os.path.join( self.packagedir , "CMakeLists.txt" )
    cmake_dest = os.path.join( self.workdir, self.instsrcdir, "CMakeLists.txt" )
    shutil.copy( cmake_script, cmake_dest )

    bzip2_dir  = os.path.join( self.workdir, self.instsrcdir )

    cmd = "cd %s && patch -p0 < %s" % \
          ( bzip2_dir, os.path.join( self.packagedir, "bzip.diff" ) )
    os.system( cmd ) or die

    return True

  def compile( self ):
    return self.kdeCompile()

  def install( self ):
    return self.kdeInstall()

  def make_package( self ):
    # auto-create both import libs with the help of pexports
    self.stripLibs( PACKAGE_DLL_NAME )

    # auto-create both import libs with the help of pexports
    self.createImportLibs( PACKAGE_DLL_NAME )

    # now do packaging with kdewin-packager
    self.doPackaging( PACKAGE_NAME, PACKAGE_FULL_VER, True )

    return True

subclass().execute()
