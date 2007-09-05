import base
import os
import shutil
import utils
from utils import die

GIFLIB_NAME         = "giflib"
GIFLIB_VER          = "4.1.4"
GIFLIB_FULL_VER     = "4.1.4-2"
GIFLIB_FULL_NAME    = "%s-%s" % ( GIFLIB_NAME, GIFLIB_VER )
GIFLIB_DLL_NAME     = "giflib4"

# C:\tmp>expat-win32bin-2.0.1.exe /DIR="C:\tmp\expat" /SILENT
# C:\tmp>c:\tmp\expat\Uninstall\unins000.exe /SILENT

SRC_URI= """
http://switch.dl.sourceforge.net/sourceforge/gnuwin32/giflib-4.1.4-1.exe
"""

DEPEND = """
"""

class subclass(base.baseclass):
  def __init__(self):
    base.baseclass.__init__( self, SRC_URI )

  def unpack( self ):

    # hopefully only one...
    for filename in self.filenames:
        os.system( os.path.join( self.downloaddir, filename ) + " /DIR=\"" + self.workdir + "\" /SILENT")

    return True

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

    src = os.path.join( self.workdir, self.instsrcdir, "bin", "giflib4.dll" )
    dst = os.path.join( self.imagedir, self.instdestdir, "bin", "giflib4.dll" )
    shutil.copy( src, dst )

    # /contrib/GIFLIB_NAME/GIFLIB_FULL_VER
    src = os.path.join( self.workdir, self.instsrcdir, "contrib" )
    dst = os.path.join( self.imagedir, self.instdestdir, "contrib" )
    utils.copySrcDirToDestDir( src, dst )

    # /doc can be used from zip package
    src = os.path.join( self.workdir, self.instsrcdir, "doc" )
    dst = os.path.join( self.imagedir, self.instdestdir, "doc" )
    utils.copySrcDirToDestDir( src, dst )

    # /include can be used from zip package
    src = os.path.join( self.workdir, self.instsrcdir, "include" )
    dst = os.path.join( self.imagedir, self.instdestdir, "include" )
    utils.copySrcDirToDestDir( src, dst )

    # /lib needs a complete rebuild - done in make_package
    dst = os.path.join( self.imagedir, self.instdestdir, "lib" )
    utils.cleanDirectory( dst )

    return True
  def make_package( self ):
    self.instsrcdir = ""

    # auto-create both import libs with the help of pexports
    self.createImportLibs( GIFLIB_DLL_NAME )

    # now do packaging with kdewin-packager
    self.doPackaging( GIFLIB_NAME, GIFLIB_FULL_VER, False )

    return True
  
subclass().execute()
