import base
import utils
from utils import die
import os

DEPEND = """
virtual/base
libs/qt
"""

class subclass(base.baseclass):
  def __init__(self):
    base.baseclass.__init__( self, "" )

  def unpack( self ):
    print "%s unpack called" % self.package

    #repo = "svn://anonsvn.kde.org/home/kde/trunk/kdesupport/kdewin32"
    svnpath = "trunk/kdesupport/"
    dir = "kdewin32/"
    self.kdeSvnFetch( svnpath, dir )

    utils.cleanDirectory( self.workdir )

    # now copy the tree to workdir
    srcdir = os.path.join( self.kdesvndir, svnpath, dir ).replace( "/", "\\" )
    destdir = os.path.join( self.workdir, dir )
    utils.copySrcDirToDestDir( srcdir, destdir )

    return True

  def compile( self ):
    print "%s compile called" % self.package
    os.chdir( self.workdir )

    builddir = "%s-build" % self.package

    if ( not os.path.exists( builddir ) ):
      os.mkdir( builddir )

    utils.cleanDirectory( builddir )

    os.chdir( builddir )

    options = "-DCMAKE_INSTALL_PREFIX=%s/%s ..\\%s " \
      % (self.cmakeInstallPrefix, self.package, self.package)

    os.system( r"""cmake -G "MinGW Makefiles" %s """ % options ) and die( "cmake" )
    os.system( "mingw32-make" ) and die( "mingw32-make" )
    
    return True

  def install( self ):
    print "kdewin32 install called"
    os.chdir( os.path.join( self.workdir, "%s-build" % self.package ) )
    os.system( "mingw32-make DESTDIR=%s install" % self.imagedir ) \
               and die( "mingw32-make install" )
    utils.fixCmakeImageDir( self.imagedir, self.rootdir )
    return True

subclass().execute()
