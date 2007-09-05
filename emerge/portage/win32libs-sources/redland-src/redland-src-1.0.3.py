import base
import os
import shutil
import utils

PACKAGE_NAME         = "redland"
PACKAGE_VER          = "1.0.3"
PACKAGE_FULL_VER     = "1.0.3-4"
PACKAGE_FULL_NAME    = "%s-%s" % ( PACKAGE_NAME, PACKAGE_VER )
PACKAGE_DLL_NAMES    = """
libcurl
libdb43
librdf
raptor
rasqal
"""

# C:\tmp>expat-win32bin-2.0.1.exe /DIR="C:\tmp\expat" /SILENT
# C:\tmp>c:\tmp\expat\Uninstall\unins000.exe /SILENT

SRC_URI= """
http://download.librdf.org/binaries/win32/1.0.3/redland-1.0.3-Win32-Dev.zip
"""

DEPEND = """
"""

class subclass(base.baseclass):
  def __init__(self):
    base.baseclass.__init__( self, SRC_URI )

  def compile( self ):
    # binary-only package - nothing to compile
    return True

  def install( self ):
    # cleanup
    dst = os.path.join( self.imagedir )
    utils.cleanDirectory( dst )
    dst = os.path.join( self.imagedir, self.instdestdir )
    utils.cleanDirectory( dst )

    # /bin only contains zlib1.dll
    dst = os.path.join( self.imagedir, self.instdestdir, "bin" )
    utils.cleanDirectory( dst )

    for libs in PACKAGE_DLL_NAMES.split():
        src = os.path.join( self.workdir, self.instsrcdir, libs + ".dll" )
        dst = os.path.join( self.imagedir, self.instdestdir, "bin", libs + ".dll" )
        shutil.copy( src, dst )

    # /contrib/PACKAGE_NAME/PACKAGE_FULL_VER
    dst = os.path.join( self.imagedir, self.instdestdir, "contrib" )
    utils.cleanDirectory( dst )
    dst = os.path.join( dst, PACKAGE_NAME )
    utils.cleanDirectory( dst )
    dst = os.path.join( dst, PACKAGE_FULL_VER )
    utils.cleanDirectory( dst )

    src = os.path.join( self.workdir )
    shutil.copy( os.path.join( src, "AUTHORS" ),  os.path.join( dst, "AUTHORS" ) )
    shutil.copy( os.path.join( src, "COPYING" ),  os.path.join( dst, "COPYING" ) )
    shutil.copy( os.path.join( src, "COPYING.LIB" ),  os.path.join( dst, "COPYING.LIB" ) )
    shutil.copy( os.path.join( src, "LICENSE.txt" ),  os.path.join( dst, "LICENSE.txt" ) )
    shutil.copy( os.path.join( src, "LICENSE-2.0.txt" ),  os.path.join( dst, "LICENSE-2.0.txt" ) )
    shutil.copy( os.path.join( src, "NOTICE" ),  os.path.join( dst, "NOTICE" ) )
    shutil.copy( os.path.join( src, "README" ),  os.path.join( dst, "README" ) )

    # /doc can be used from zip package
    src = os.path.join( self.workdir, self.instsrcdir, "include" )
    dst = os.path.join( self.imagedir, self.instdestdir, "include" )
    utils.copySrcDirToDestDir( src, dst )

    # /lib needs a complete rebuild - done in make_package
    dst = os.path.join( self.imagedir, self.instdestdir, "lib" )
    utils.cleanDirectory( dst )

    return True
  def make_package( self ):
    self.instsrcdir = "source"

    # auto-create both import libs with the help of pexports
    for libs in PACKAGE_DLL_NAMES.split():
        self.createImportLibs( libs )

    # now do packaging with kdewin-packager
    self.doPackaging( PACKAGE_NAME, PACKAGE_FULL_VER, True )

    return True
  
subclass().execute()
