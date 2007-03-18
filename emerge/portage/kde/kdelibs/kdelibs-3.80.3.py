import base
import utils
from utils import die
import os

DEPEND = """
virtual/base
dev-util/dbus
dev-util/win32libs
kde/kdewin32
"""

# FIXME KComponentDataPrivate destructor

SRC_URI = "ftp://ftp.kde.org/pub/kde/unstable/3.80.3/src/kdelibs-3.80.3.tar.bz2"

class subclass(base.baseclass):
  def __init__(self):
    base.baseclass.__init__( self, SRC_URI )

    #def unpack( self ):
    #print "%s unpack called" % self.progname

    #repo = "svn://anonsvn.kde.org/home/kde/trunk/KDE/%s" % self.progname
    #self.svnFetch( repo )

    #utils.cleanDirectory( self.workdir )

    # now copy the tree to workdir
    #srcdir = os.path.join( self.svndir, self.progname )
    #destdir = os.path.join( self.workdir, self.progname )
    #utils.copySrcDirToDestDir( srcdir, destdir )
    
    #copy the needed changed cmake files over...
    #destdir = os.path.join( self.workdir, self.progname, "cmake", "modules" )
    #utils.copySrcDirToDestDir( self.filesdir, destdir )

    #return True

  def compile( self ):
    print "%s compile called" % self.package

    #copy the needed changed cmake files over...
    destdir = os.path.join( self.workdir, self.PV, "cmake", "modules" )
    utils.copySrcDirToDestDir( self.filesdir, destdir )

    os.chdir( self.workdir )

    builddir = "%s-build" % self.package

    if ( not os.path.exists( builddir ) ):
      os.mkdir( builddir )

    utils.cleanDirectory( builddir )

    os.chdir( builddir )

    options = "-DCMAKE_INSTALL_PREFIX=/kde ..\\%s-%s " % \
        ( self.package, self.version )

    options = options + "-DKDEWIN32_INSTALL_PREFIX=%s " % \
        os.path.join( self.rootdir, "kdewin32" ).replace( "\\", "/" )

    options = options + "-DWIN32LIBS_INSTALL_PREFIX=%s " % \
        os.path.join( self.rootdir, "win32libs" ).replace( "\\", "/" )

    command = r"""cmake -G "MinGW Makefiles" %s """ % options
    print "cmake command:", command
    os.system( command ) and die ( "cmake" )
    os.system( "mingw32-make" ) and die( "mingw32-make" )
    
    return True

  def install( self ):
    print "kdewin32 install called"
    os.chdir( os.path.join( self.workdir, "%s-build" % self.package ) )
    os.system( "mingw32-make DESTDIR=%s install" % self.imagedir ) \
               and die( "mingw32-make install" )
    #utils.fixCmakeImageDir( self.imagedir, self.rootdir )
    return True

subclass().execute()
