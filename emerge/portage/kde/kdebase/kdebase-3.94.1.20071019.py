import base

DEPEND = """
kde/kdelibs
kde/kdepimlibs
"""

class subclass(base.baseclass):
    def __init__( self ):
        base.baseclass.__init__( self, "" )

    def kdeSvnPath( self ):
        return "trunk/KDE/kdebase"
        
    def unpack( self ):
        return self.kdeSvnUnpack()

    def compile( self ):
        self.kdeCustomDefines = "-DKDE4_DISABLE_MULTIMEDIA=ON"
        return self.kdeCompile()

    def install( self ):
        return self.kdeInstall()

    def make_package( self ):
        return self.doPackaging( "kdebase", "3.94-1", True )

		
subclass().execute()
