import base
import utils
import os

class subclass(base.baseclass):
  def __init__(self):
    base.baseclass.__init__( self, "" )

  def unpack( self ):
    print "%s unpack called" % self.progname

    repo = "svn://anonsvn.kde.org/home/kde/trunk/KDE/%s" % self.progname
    self.svnFetch( repo )

    utils.cleanDirectory( self.workdir )
	
    # now copy the tree to workdir
    srcdir = os.path.join( self.svndir, self.progname )
    destdir = os.path.join( self.workdir, self.progname )
    utils.copySrcDirToDestDir( srcdir, destdir )
    
    #copy the needed changed cmake files over...
    destdir = os.path.join( self.workdir, self.progname, "cmake", "modules" )
    utils.copySrcDirToDestDir( self.filesdir, destdir )

    return True
		
  def compile( self ):
    print "%s compile called" % self.progname
    os.chdir( self.workdir )

    builddir = "%s-build" % self.progname

    if ( not os.path.exists( builddir ) ):
	os.mkdir( builddir )

    utils.cleanDirectory( builddir )

    os.chdir( builddir )

    #options = "-DCMAKE_INSTALL_PREFIX=../../image/kde ..\\%s " % self.progname
    options = "-DCMAKE_INSTALL_PREFIX=e:/secondroot/kde ..\\%s " % self.progname

    options = options + "-DKDEWIN32_INSTALL_PREFIX=%s " % \
	os.path.join( self.rootdir, "kdewin32" ).replace( "\\", "/" )

    options = options + "-DWIN32LIBS_INSTALL_PREFIX=%s " % \
	os.path.join( self.rootdir, "win32libs" ).replace( "\\", "/" )

    command = r"""cmake -G "MinGW Makefiles" %s """ % options
    print "cmake command:", command
    os.system( command )
    os.system( "mingw32-make" )
    
    return True
		
  def install( self ):
    print "kdewin32 install called"
    os.chdir( os.path.join( self.workdir, "%s-build" % self.progname ) )
    os.system( "mingw32-make install" )
    return True
		
subclass().execute()
