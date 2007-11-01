import base

DEPEND = """
kde4-beta4/kdelibs-beta4
kde4-beta4/kdepimlibs-beta4
"""

class subclass(base.baseclass):
  def __init__(self):
    base.baseclass.__init__( self, "" )
    self.buildType = "RelWithDebInfo"
    self.instsrcdir = "kdebase"
    self.instdestdir = "kde"

  def unpack( self ):
    return self.kdeSvnUnpack( "tags/KDE/3.95/", "kdebase" )

  def compile( self ):
    self.kdeCustomDefines = "-DKDE4_DISABLE_MULTIMEDIA=ON"
    return self.kdeCompile()

  def install( self ):
    return self.kdeInstall()
		
  def make_package( self ):
    return self.doPackaging( "kdebase", "3.95-1", True )

subclass().execute()
