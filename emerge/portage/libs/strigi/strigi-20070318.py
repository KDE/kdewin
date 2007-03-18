import base
import utils
from utils import die
import os

DEPEND = """
virtual/base
"""

class subclass(base.baseclass):
  def __init__(self):
    base.baseclass.__init__( self, "" )

  def unpack( self ):
    print "%s unpack called" % self.package

    repo = "svn://anonsvn.kde.org/home/kde/trunk/kdesupport/strigi"
    self.svnFetch( repo )

    utils.cleanDirectory( self.workdir )

    # now copy the tree to workdir
    srcdir = os.path.join( self.svndir, "strigi" )
    destdir = os.path.join( self.workdir, "strigi" )
    utils.copySrcDirToDestDir( srcdir, destdir )
    
    #copy the needed changed cmake files over...
    destdir = os.path.join( self.workdir, "strigi", "cmake" )
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

    options = "-DCMAKE_INSTALL_PREFIX=%s/%s ..\\%s " \
      % (self.cmakeInstallPrefix, self.package, self.package)

    options = options + "-DWIN32LIBS_INSTALL_PREFIX=%s " % \
        os.path.join( self.rootdir, "win32libs" ).replace( "\\", "/" )

    options = options + "-DGNUWIN32_INSTALL_PREFIX=%s " % \
        os.path.join( self.rootdir, "gnuwin32" ).replace( "\\", "/" )
	    
    command = r"""cmake -G "MinGW Makefiles" %s """ % options 
    print "command: %s" % command
    os.system( command ) and die( "cmake" )
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
