import base
import utils
from utils import die
import os

DEPEND = """
kde/kdelibs
"""

class subclass(base.baseclass):
  def __init__(self):
    base.baseclass.__init__( self, "" )

  def unpack( self ):
    print "%s unpack called" % self.package
    svnpath = "trunk/KDE/"
    dir = "kdegames"
    self.kdeSvnUnpack( svnpath, dir )
    return True

  def compile( self ):
    print "%s compile called" % self.package
    os.chdir( self.workdir )
    builddir = "%s-build" % self.package

    if ( not os.path.exists( builddir ) ):
      os.mkdir( builddir )

    utils.cleanDirectory( builddir )
    os.chdir( builddir )

    command = r"""cmake -G "MinGW Makefiles" %s """ % self.kdeDefaultDefines()
    print "cmake command:", command
    os.system( command ) and die ( "cmake" )
    os.system( "mingw32-make" ) and die( "mingw32-make" )
    
    return True

  def install( self ):
    print "%s install called" % self.package
    self.kdeInstall()
    return True

subclass().execute()
