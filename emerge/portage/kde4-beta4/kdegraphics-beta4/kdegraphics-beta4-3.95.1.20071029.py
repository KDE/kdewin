import base

DEPEND = """
kde4-beta4/kdelibs-beta4
"""

class subclass(base.baseclass):
  def __init__(self):
    base.baseclass.__init__( self, "" )
    self.buildType = "RelWithDebInfo"
    self.instsrcdir = "kdegraphics"
    self.instdestdir = "kde"

  def unpack( self ):
    return self.kdeSvnUnpack( "tags/KDE/3.95/", "kdegraphics" )

  def compile( self ):
    return self.kdeCompile()

  def install( self ):
    return self.kdeInstall()

  def make_package( self ):
    return self.doPackaging( "kdegraphics", "3.95-1", True )

subclass().execute()
