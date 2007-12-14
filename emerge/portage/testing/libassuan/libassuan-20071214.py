import base
import utils
import os
import shutil
from utils import die


PACKAGE_NAME = "libassuan"
PACKAGE_FULL_VER = "20071214"
DEPENDS = """
virtual/base
"""

class subclass(base.baseclass):
  def __init__(self):
    base.baseclass.__init__( self, "" )
#    self.instdestdir = "kde"
    # cmake scripts are not in src root...
    self.instsrcdir = "libassuan"

  def unpack( self ):
    print "dbus unpack called"
    # do the svn fetch/update
    repo = "svn://cvs.gnupg.org/libassuan/trunk"
    self.svnFetch( repo )

    utils.cleanDirectory( self.workdir )

    # now copy the tree below destdir/trunk to workdir
    srcdir = os.path.join( self.svndir, "trunk" )
    destdir = os.path.join( self.workdir, "libassuan" )
    utils.copySrcDirToDestDir( srcdir, destdir )

    os.chdir( destdir )
    os.system( "patch -p0 < libassuan.diff" )

    return True


  def compile( self ):
    return self.kdeCompile()

  def install( self ):
    return self.kdeInstall()

  def make_package( self ):

    # now do packaging with kdewin-packager
    self.doPackaging( PACKAGE_NAME, PACKAGE_FULL_VER, True )

    return True

subclass().execute()
