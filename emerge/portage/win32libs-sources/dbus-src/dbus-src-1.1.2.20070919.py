import base
import utils
import os
import shutil
from utils import die


PACKAGE_NAME = "dbus"
PACKAGE_FULL_VER = "1.1.2.20070919"
DEPENDS = """
virtual/base
"""

class subclass(base.baseclass):
  def __init__(self):
    base.baseclass.__init__( self, "" )
    self.instdestdir = "kde"
    # cmake scripts are not in src root...
    self.instsrcdir = os.path.join( "dbus", "cmake" )

  def unpack( self ):
    print "dbus unpack called"
    # do the svn fetch/update
    repo = "https://windbus.svn.sourceforge.net/svnroot/windbus/trunk"
    self.svnFetch( repo )

    utils.cleanDirectory( self.workdir )

    # now copy the tree below destdir/trunk to workdir
    srcdir = os.path.join( self.svndir, "trunk" )
    destdir = os.path.join( self.workdir, "dbus" )
    utils.copySrcDirToDestDir( srcdir, destdir )

    os.chdir( destdir )
    os.system( "patch -p0 < DBus-win32.patch" )

    #copy the needed changed cmake files over...
    destdir = os.path.join( self.workdir, "dbus", "cmake", "modules" )
    utils.copySrcDirToDestDir( self.filesdir, destdir )

    file = r"cmake\CMakeLists.txt"
    os.rename( file, "%s.orig" % file )

    # disable doc subdir in recent dbus svn
    sedcommand = r""" "s/add_subdirectory( doc )/###add_subdirectory( doc )/" """

    command = "type %s.orig | sed -e %s > %s" % ( file, sedcommand, file )
    #print "command:", command
    os.system( command )

    return True


  def compile( self ):
    return self.kdeCompile()

  def install( self ):
    return self.kdeInstall()

  def make_package( self ):
    # for src package
    self.instsrcdir = "dbus"

    # now do packaging with kdewin-packager
    self.doPackaging( PACKAGE_NAME, PACKAGE_FULL_VER, True )

    return True

subclass().execute()
