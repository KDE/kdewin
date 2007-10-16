import base

DEPEND = """
kde4-beta3/kdelibs-beta3
kde4-beta3/kdepimlibs-beta3
"""

class subclass(base.baseclass):
  def __init__(self):
    base.baseclass.__init__( self, "" )
    self.buildType = "Debug"
    self.instsrcdir = "kdebase"
    self.instdestdir = "kde"

  def unpack( self ):
    return self.kdeSvnUnpack( "tags/KDE/3.94/", "kdebase" )

  def compile( self ):
    self.kdeCustomDefines = "-DKDE4_DISABLE_MULTIMEDIA=ON"
    return self.kdeCompile()

  def install( self ):
    return self.kdeInstall()
		
  def make_package( self ):
    return self.doPackaging( "kdebase", "3.94-1", True )

subclass().execute()
