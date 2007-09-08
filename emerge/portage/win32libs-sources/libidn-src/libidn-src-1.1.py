import base
import os
import shutil
import re
import utils
from utils import die

PACKAGE_NAME         = "libidn"
PACKAGE_VER          = "1.1"
PACKAGE_FULL_VER     = "1.1"
PACKAGE_FULL_NAME    = "%s-%s" % ( PACKAGE_NAME, PACKAGE_VER)
PACKAGE_DLL_NAME     = """
libidn-11
"""

SRC_URI= """
ftp://alpha.gnu.org/pub/gnu/libidn/libidn-1.1.tar.gz
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

  def compile( self ):
    # we need a patch to /bin/sh from msys... hmmm
    src = os.path.join( self.workdir, self.instsrcdir )
    dst = os.path.join( self.workdir, self.instsrcdir )

    msys_dir = os.environ[ "MSYSPATH" ]
    sh = os.path.join( msys_dir, "bin", "sh.exe" )

    cmd = "%s --login -c \"cd %s && configure --disable-static && make -j2 install DESTDIR=%s\"" % \
          ( sh, utils.toMSysPath( src ), utils.toMSysPath( dst ) )
    print cmd
    os.system( cmd ) or die

    return True

  def install( self ):
    # we already installed in compile... not fine but currently no other idea
    # nearly all can be used from zip package
    src = os.path.join( self.workdir, self.instsrcdir, "usr", "local")
    dst = os.path.join( self.imagedir, self.instdestdir )
    utils.copySrcDirToDestDir( src, dst )

    return True

  def make_package( self ):
    # clean directory
    dst = os.path.join( self.imagedir, self.instdestdir, "lib" )
    utils.cleanDirectory( dst )
    
    # auto-create both import libs with the help of pexports
    for lib in PACKAGE_DLL_NAME.split():
        self.createImportLibs( lib )

    # now do packaging with kdewin-packager
    # We can add the source once we do an out-of-source build
    self.doPackaging( PACKAGE_NAME, PACKAGE_FULL_VER, False )

    return True

subclass().execute()
