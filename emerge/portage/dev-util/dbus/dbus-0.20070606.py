import base
import utils
import os
import shutil


DEPENDS = """
virtual/base
"""

# FIXME create dbus-1d lib for qt to link against...

class subclass(base.baseclass):
  def __init__(self):
    base.baseclass.__init__( self, "" )

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

    if ( not os.path.exists( "dbus-build" ) ):
        os.mkdir( "dbus-build" )

    os.chdir( "dbus-build" )

    options = "-DWIN32LIBS_INSTALL_PREFIX=%s " % \
        os.path.join( self.rootdir, "win32libs" ).replace( "\\", "/" )

    options = options + "-DCMAKE_INSTALL_PREFIX=%s/dbus " % \
    		self.cmakeInstallPrefix 

    command = r"""cmake -G "MinGW Makefiles" ..\dbus\cmake\ %s""" % options

    print "command:", command
    os.system( command )

    os.system( "mingw32-make" ) and die ( "mingw32-make failed" )
    return True

  def install( self ):
    print "dbus install called"

    os.chdir( os.path.join( self.workdir, "dbus-build" ) )

    os.system( "mingw32-make DESTDIR=%s install" % self.imagedir ) \
		and die ( "mingw32-make install failed" )

    utils.fixCmakeImageDir( self.imagedir, self.rootdir )
    
    #now copy release dll to debug dll
    os.chdir( os.path.join(self.imagedir, "dbus", "bin") )
    shutil.copy( "libdbus-1.dll", "libdbus-1d.dll" )

    os.chdir( os.path.join(self.imagedir, "dbus", "lib") )
    shutil.copy( "libdbus-1.dll.a", "libdbus-1d.dll.a" )
    
    return True


subclass().execute()
