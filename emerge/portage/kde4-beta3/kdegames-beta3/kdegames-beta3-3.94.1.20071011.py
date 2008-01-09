import base

DEPEND = """
kde4-beta3/kdelibs-beta3
"""

class subclass(base.baseclass):
  def __init__(self):
    base.baseclass.__init__( self, "" )
    self.buildType = "RelWithDebInfo"
    self.instsrcdir = "kdegames"
    self.instdestdir = "kde"

  def unpack( self ):
    return self.kdeSvnUnpack( "tags/KDE/3.94/", "kdegames" )

  def compile( self ):
    return self.kdeCompile()
    
  def install( self ):
    return self.kdeInstall()

  def make_package( self ):
    return self.doPackaging( "kdegames", "3.94-2", True )

if __name__ == '__main__':
    subclass().execute()
