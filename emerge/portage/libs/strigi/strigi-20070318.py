import base
import utils
from utils import die
import os

DEPEND = """
virtual/base
gnuwin32/openssl
"""

class subclass(base.baseclass):
  def __init__(self):
    base.baseclass.__init__( self, "" )

  def unpack( self ):
    print "%s unpack called" % self.package
    svnpath = "trunk/kdesupport/"
    dir = "strigi"
    self.kdeSvnFetch( svnpath, dir )

    utils.cleanDirectory( self.workdir )

    # now copy the tree to workdir
    #srcdir = os.path.join( self.kdesvndir, svnpath, dir ).replace( "/", "\\" )
    destdir = os.path.join( self.workdir, dir )
    utils.copySrcDirToDestDir( self.svndir, destdir )

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

    options = "-DCMAKE_INSTALL_PREFIX=%s/strigi ..\\%s " % \
        ( self.rootdir.replace( "\\", "/" ), self.package )

    options = options + "-DKDEWIN32_INSTALL_PREFIX=%s " % \
        os.path.join( self.rootdir, "kdewin32" ).replace( "\\", "/" )

    options = options + "-DWIN32LIBS_INSTALL_PREFIX=%s " % \
        os.path.join( self.rootdir, "win32libs" ).replace( "\\", "/" )

    if ( self.compiler == "mingw" ):
      command = r"""cmake -G "MinGW Makefiles" %s """ % options 
      print "command: %s" % command
      os.system( command ) and die( "cmake" )
      os.system( "mingw32-make" ) and die( "mingw32-make" )
    elif ( self.compiler == "msvc2005" ):
      command = r"""cmake -G "NMake Makefiles" %s """ % options 
      print "command: %s" % command
      os.system( command ) and die( "cmake" )
      os.system( "nmake" ) and die( "nmake" )
    
    return True

  def install( self ):
    print "%s install called" % self.package
    os.chdir( os.path.join( self.workdir, "%s-build" % self.package ) )

    # FIXME how to install with nmake ?
    os.system( "mingw32-make DESTDIR=%s install" % self.imagedir ) \
               and die( "mingw32-make install" )
    utils.fixCmakeImageDir( self.imagedir, self.rootdir )
    return True

subclass().execute()
