import base
import os
import shutil
import utils

PACKAGE_NAME         = "libpng"
PACKAGE_VER          = "1.2.20"
PACKAGE_FULL_VER     = "1.2.20"
PACKAGE_FULL_NAME    = "%s-%s" % ( PACKAGE_NAME, PACKAGE_VER)
PACKAGE_DLL_NAME     = "libpng12"

SRC_URI= """
http://ovh.dl.sourceforge.net/sourceforge/libpng/""" + PACKAGE_FULL_NAME + """.tar.gz
"""

DEPEND = """
dev-util/win32libs
"""

class subclass(base.baseclass):
  def __init__(self):
    base.baseclass.__init__( self, SRC_URI )
    self.package = PACKAGE_FULL_NAME
    self.createCombinedPackage = False

  def execute( self ):
    base.baseclass.execute( self )
    if self.compiler <> "mingw":
      print "error: can only be build with MinGW (but in the end a mingw/msvc combined package is created"
      exit( 1 )

  def compile( self ):
    # the cmake script is in libpng-src/scripts
    srcdir  = os.path.join( self.workdir, self.package, "scripts", "CMakeLists.txt" )
    destdir = os.path.join( self.workdir, self.package, "",        "CMakeLists.txt" )
    shutil.copy( srcdir, destdir )

    self.kdeCustomDefines = "-DPNG_TESTS=OFF -DPNG_STATIC=OFF"
    return self.kdeCompile()

  def install( self ):
    return self.kdeInstall()

  def make_package( self ):
    self.instdestdir = "kde"

    # auto-create both import libs with the help of pexports
    self.stripLibs( PACKAGE_DLL_NAME )

    # auto-create both import libs with the help of pexports
    self.createImportLibs( PACKAGE_DLL_NAME )

    # now do packaging with kdewin-packager
    self.doPackaging( PACKAGE_NAME, PACKAGE_FULL_VER )

    return True

subclass().execute()
