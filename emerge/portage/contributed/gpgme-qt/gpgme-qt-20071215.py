import base
import utils
import os
import shutil
from utils import die


PACKAGE_NAME = "libassuan"
PACKAGE_FULL_VER = "20071214"
DEPENDS = """
virtual/base
kde/kdelibs
"""

class subclass(base.baseclass):
  def __init__(self):
    base.baseclass.__init__( self, "" )
#    self.instdestdir = "kde"
    # cmake scripts are not in src root...
    self.instsrcdir = "gpgme-qt"

  def unpack( self ):
    print "gpgme-qt unpack called"
    # do the svn fetch/update
    repo = "svn://cvs.gnupg.org/gpgme-qt/trunk"
    self.svnFetch( repo )

    utils.cleanDirectory( self.workdir )

    # now copy the tree below destdir/trunk to workdir
    srcdir = os.path.join( self.svndir, "trunk" )
    destdir = os.path.join( self.workdir, "libassuan" )
    utils.copySrcDirToDestDir( srcdir, destdir )

    os.chdir( self.workdir )
    self.system( "cd %s && patch -p0 < %s" % ( self.workdir, os.path.join( self.packagedir, "libassuan.diff" ) ) )
    self.system( "cd %s && patch -p0 < %s" % ( self.workdir, os.path.join( self.packagedir, "libassuan-cmake.diff" ) ) )
#    os.system( "patch -p0 < libassuan_cmake.diff" )

    return True


  def compile( self ):
    return self.kdeCompile()

  def install( self ):
    return self.kdeInstall()

  def make_package( self ):

    # now do packaging with kdewin-packager
    self.doPackaging( PACKAGE_NAME, PACKAGE_FULL_VER, True )

    return True
    
if __name__ == '__main__':
    subclass().execute()
