import base

DEPEND = """
kde/kdelibs
kde/kdepimlibs
"""

class subclass(base.baseclass):
    def __init__(self):
        base.baseclass.__init__( self, "" )

    def unpack( self ):
        return self.kdeSvnUnpack( "trunk/KDE", "kdepim" )

    def compile( self ):
        return self.kdeCompile()

    def install( self ):
        return self.kdeInstall()

    def make_package( self ):
        return self.doPackaging( "kdepim", "3.94-1", True )
		
subclass().execute()
