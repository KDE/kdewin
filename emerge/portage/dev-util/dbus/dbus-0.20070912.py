import base
import utils
import os
import shutil
from utils import die


PACKAGE_NAME = "dbus"
PACKAGE_FULL_VER = "0.20070912"
DEPENDS = """
virtual/base
"""

buildtypes = "debug release"

class subclass(base.baseclass):
  def __init__(self):
    base.baseclass.__init__( self, "" )
    self.instdestdir = "dbus"

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
    print "dbus compile called"
    os.chdir( self.workdir )

    for type in buildtypes.split():
      builddir = os.path.join( self.workdir, "dbus-build-" + type )
      utils.cleanDirectory( builddir )
      os.chdir( builddir )

      options = "-DWIN32LIBS_INSTALL_PREFIX=%s " % \
                os.path.join( self.rootdir, "win32libs" ).replace( "\\", "/" )

      options = options + "-DCMAKE_INSTALL_PREFIX=%s/dbus " % \
                self.cmakeInstallPrefix

      options = options + "-DCMAKE_BUILD_TYPE=%s " % type

      command = r"""cmake -G "%s" ..\dbus\cmake\ %s""" % \
                (self.cmakeMakefileGenerator, options )

      os.system( command )

      os.system( self.cmakeMakeProgramm ) \
                 and die ( self.cmakeMakeProgramm + " failed" )

    return True

  def install( self ):
    for type in buildtypes.split():
      builddir = "dbus-build-" + type

      os.chdir( os.path.join( self.workdir, builddir ) )

      os.system( "%s DESTDIR=%s install" % \
                ( self.cmakeMakeProgramm, self.imagedir ) ) \
		and die ( self.cmakeMakeProgramm + " install failed" )

    utils.fixCmakeImageDir( self.imagedir, self.rootdir )

    return True

  def make_package( self ):

    # now do packaging with kdewin-packager
    self.doPackaging( PACKAGE_NAME, PACKAGE_FULL_VER, False )

    return True

subclass().execute()
