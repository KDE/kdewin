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
    svndir = os.path.join( self.downloaddir, "svn-src", "dbus" )
    utils.svnFetch( repo, svndir )

    utils.cleanDirectory( self.workdir )

    # now copy the tree below destdir/trunk to workdir
    srcdir = os.path.join( svndir, "trunk" )
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

    if ( not os.path.exists( "dbus-build-release" ) ):
        os.mkdir( "dbus-build-release" )
    if ( not os.path.exists( "dbus-build-debug" ) ):
        os.mkdir( "dbus-build-debug" )
    os.chdir( "dbus-build-release" )

    if ( self.compiler == "mingw" ):
    	cmakestring = "MinGW Makefiles"
    elif ( self.compiler == "msvc2005" ):
    	cmakestring = "NMake Makefiles"

    #os.system( r"""cmake -G "MinGW Makefiles" ..\windbus\cmake\ -DDBUS_BUILD_TESTS=OFF""" )

    options = ""

    options = options + "-DKDEWIN32_INSTALL_PREFIX=%s " % \
        os.path.join( self.rootdir, "kdewin32" ).replace( "\\", "/" )

    options = options + "-DWIN32LIBS_INSTALL_PREFIX=%s " % \
        os.path.join( self.rootdir, "win32libs" ).replace( "\\", "/" )

    options = options + "-DCMAKE_INSTALL_PREFIX=%s/dbus " % \
    		self.cmakeInstallPrefix 

    cmakecommand = r"""cmake -G "%s" ..\dbus\cmake\ %s""" \
	    % ( cmakestring, options )

    print "cmakecommand:", cmakecommand
    os.system( cmakecommand )

    if ( self.compiler == "mingw" ):
		    os.system( "mingw32-make" ) and die ( "mingw32-make failed" )
    elif ( self.compiler == "msvc2005" ):
		    os.system( "nmake" ) and die ( "nmake failed" )

    # now build debug version
    os.chdir( os.path.join( self.workdir, "dbus-build-debug" ) )
    options = options + "-DCMAKE_BUILD_TYPE=debug "

    cmakecommand = r"""cmake -G "%s" ..\dbus\cmake\ %s""" \
	    % ( cmakestring, options )

    print "cmakecommand:", cmakecommand
    os.system( cmakecommand )

    if ( self.compiler == "mingw" ):
		    os.system( "mingw32-make" ) and die ( "mingw32-make failed" )
    elif ( self.compiler == "msvc2005" ):
		    os.system( "nmake" ) and die ( "nmake failed" )
    return True

  def install( self ):
    print "dbus install called"

    for tmpdir in [ "dbus-build-release", "dbus-build-debug" ]:
      print "installing in ", tmpdir
      os.chdir( os.path.join( self.workdir, tmpdir ) )
      if ( self.compiler == "mingw" ):
	os.system( "mingw32-make DESTDIR=%s install" % self.imagedir ) \
		and die ( "mingw32-make install failed" )
      elif ( self.compiler == "msvc2005" ):
		    os.system( "nmake install" ) and die ( "nmake install failed" )

    if ( self.compiler == "mingw" ):
      utils.fixCmakeImageDir( self.imagedir, self.rootdir )
    
    return True


subclass().execute()
