import base

DEPEND = """
kde/kdelibs
kde/kdepimlibs
"""

class subclass(base.baseclass):
  def __init__(self):
    base.baseclass.__init__( self, "" )

  def unpack( self ):
    return self.kdeSvnUnpack( "trunk/KDE", "kdebase" )

  def compile( self ):
    self.kdeCustomDefines = "-DKDE4_DISABLE_MULTIMEDIA=ON"
    return self.kdeCompile()

  def install( self ):
    return self.kdeInstall()
		
subclass().execute()
