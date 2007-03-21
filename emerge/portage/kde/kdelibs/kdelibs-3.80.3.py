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

comment = """
get rid of this kdebug.h warning if possible:
[ 31%] Building CXX object kdeui/CMakeFiles/kdeui.dir/actions/kaction.obj
e:/mingwroot/tmp/kdelibs-3.80.3/work/kdelibs/kdecore/io/kdebug.h: In instantiati
on of `kdbgstream& kdbgstream::operator<<(const T&) [with T = QLatin1Char]':
e:/mingwroot/tmp/kdelibs-3.80.3/work/kdelibs/kdecore/io/kdebug.h:130:   instanti
ated from here
e:/mingwroot/tmp/kdelibs-3.80.3/work/kdelibs/kdecore/io/kdebug.h:296: warning: '
kdbgstream& kdbgstream::operator<<(const T&) [with T = QLatin1Char]' defined loc
ally after being referenced with dllimport linkage

"""
class subclass(base.baseclass):
  def __init__(self):
    base.baseclass.__init__( self, "" )

  def unpack( self ):
    print "%s unpack called" % self.package
    svnpath = "trunk/KDE/"
    dir = "kdelibs"
    self.kdeSvnFetch( svnpath, dir )

    utils.cleanDirectory( self.workdir )

    # now copy the tree to workdir
    srcdir = os.path.join( self.kdesvndir, svnpath, dir ).replace( "/", "\\" )
    destdir = os.path.join( self.workdir, dir )
    utils.copySrcDirToDestDir( srcdir, destdir )
    #srcdir = os.path.join( self.svndir, self.package )
    #destdir = os.path.join( self.workdir, self.package )
    #utils.copySrcDirToDestDir( srcdir, destdir )
    
    #copy the needed changed cmake files over...
    destdir = os.path.join( self.workdir, self.package, "cmake", "modules" )
    utils.copySrcDirToDestDir( self.filesdir, destdir )

    return True

  def compile( self ):
    print "%s compile called" % self.package
    os.chdir( self.workdir )

    builddir = "%s-build" % self.package

    if ( not os.path.exists( builddir ) ):
      os.mkdir( builddir )

    utils.cleanDirectory( builddir )

    os.chdir( builddir )

    options = "-DCMAKE_INSTALL_PREFIX=/kde ..\\%s " % self.package

    options = options + "-DKDEWIN32_INSTALL_PREFIX=%s " % \
        os.path.join( self.rootdir, "kdewin32" ).replace( "\\", "/" )

    options = options + "-DWIN32LIBS_INSTALL_PREFIX=%s " % \
        os.path.join( self.rootdir, "win32libs" ).replace( "\\", "/" )

    options = options + "-DSTRIGI_INSTALL_PREFIX=%s " % \
        os.path.join( self.rootdir, "strigi" ).replace( "\\", "/" )

    options = options + "-DSHARED_MIME_INFO_INSTALL_PREFIX=%s " % \
        os.path.join( self.rootdir, "shared-mime-info" ).replace( "\\", "/" )

    command = r"""cmake -G "MinGW Makefiles" %s """ % options
    print "cmake command:", command
    os.system( command ) and die ( "cmake" )
    os.system( "mingw32-make" ) and die( "mingw32-make" )
    
    return True

  def install( self ):
    print "%s install called" % self.package
    os.chdir( os.path.join( self.workdir, "%s-build" % self.package ) )
    os.system( "mingw32-make DESTDIR=%s install" % self.imagedir ) \
               and die( "mingw32-make install" )
    #utils.fixCmakeImageDir( self.imagedir, self.rootdir )
    return True

subclass().execute()
