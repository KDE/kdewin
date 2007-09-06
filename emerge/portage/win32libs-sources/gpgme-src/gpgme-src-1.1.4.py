import base
import os
import shutil
import re
import utils
from utils import die

PACKAGE_NAME         = "gpgme"
PACKAGE_VER          = "1.1.4"
PACKAGE_PACKAGER_VER = ""
PACKAGE_FULL_VER     = "1.1.4"
PACKAGE_FULL_NAME    = "%s-%s" % ( PACKAGE_NAME, PACKAGE_VER)
PACKAGE_GPGERR_NAME  = "%s-%s" % ( "libgpg-error", "1.5")
PACKAGE_DLL_NAME     = """
libgpg-error-0
libgpgme-11
"""

SRC_URI= """
ftp://ftp.gnupg.org/gcrypt/gpgme/""" + PACKAGE_FULL_NAME + """.tar.bz2
ftp://ftp.gnupg.org/gcrypt/libgpg-error/""" + PACKAGE_GPGERR_NAME + """.tar.bz2
"""

DEPEND = """
"""

class subclass(base.baseclass):
  def __init__(self):
    base.baseclass.__init__( self, SRC_URI )

  def execute( self ):
    base.baseclass.execute( self )
    if self.compiler <> "mingw":
      print "error: can only be build with MinGW (but in the end a \
             mingw/msvc combined package is created"
      exit( 1 )

  def win2msys( self, path ):
    path = path.replace( '\\', '/' )
    if ( path[1] == ':' ):
      path = '/' + path[0].lower() + '/' + path[3:]
    return path

  def compile( self ):
    # we need a patch to /bin/sh from msys... hmmm
    dst = os.path.join( self.imagedir )
    utils.cleanDirectory( dst )
    dst = os.path.join( self.imagedir, self.instdestdir )
    utils.cleanDirectory( dst )

    src = os.path.join( self.workdir, self.instdestdir )
    gpgerr_dir = os.path.join( src, PACKAGE_GPGERR_NAME )
    gpglib_dir = os.path.join( src, PACKAGE_FULL_NAME )
    msys_dir = os.environ[ "MSYSPATH" ]
    sh = os.path.join( msys_dir, "bin", "sh.exe" )

    # ok, ok - we maybe should split this into libgpg-error and libgpgme
    cmd = "cd %s && patch -p0 < %s" % \
          ( gpgerr_dir, os.path.join( self.packagedir , "libgpg-error-1.5.diff" ) )
    os.system( cmd ) or die

    cmd = "%s --login -c \"cd %s && configure --disable-static && make install DESTDIR=%s\"" % \
          ( sh, self.win2msys( gpgerr_dir ), self.win2msys( src ) )
    os.system( cmd ) or die

    gpgerr_inst_dir = os.path.join( src, "usr", "local" )
    os.environ[ "LDFLAGS" ] = "-L" + self.win2msys( os.path.join( gpgerr_inst_dir, "lib" ) )
    os.environ[ "CFLAGS" ]  = "-I" + self.win2msys( os.path.join( gpgerr_inst_dir, "include" ) )
    cmd = "%s --login -c \"cd %s && configure --disable-static --with-gpg-error-prefix=%s && make install DESTDIR=%s\"" % \
          ( sh, self.win2msys( gpglib_dir ), self.win2msys( gpgerr_inst_dir ), self.win2msys( src ) )
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
    self.doPackaging( PACKAGE_NAME, PACKAGE_FULL_VER, False )

    return True

subclass().execute()
