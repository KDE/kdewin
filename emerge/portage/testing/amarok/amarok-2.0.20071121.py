import base

DEPEND = """
kde/kdelibs
kde/kdebase
testing/ruby
"""

class subclass(base.baseclass):
    def __init__( self ):
        base.baseclass.__init__( self, "" )
        self.instsrcdir = "amarok"

    def kdeSvnPath( self ):
        return "trunk/extragear/multimedia/amarok"
        
    def unpack( self ):
        return self.kdeSvnUnpack()

    def compile( self ):
        return self.kdeCompile()

    def install( self ):
        return self.kdeInstall()

    def make_package( self ):
        return self.doPackaging( "amarok", "2.0-SVN", True )

		
subclass().execute()
