import base

DEPEND = """
dev-util/win32libs
"""

class subclass(base.baseclass):
    def __init__(self):
        base.baseclass.__init__( self, "" )

    def kdeSvnPath( self ):
        return "trunk/kdesupport/taglib"

    def unpack( self ):
        return self.kdeSvnUnpack( "trunk/kdesupport", "taglib" )

    def compile( self ):
        return self.kdeCompile()

    def install( self ):
        return self.kdeInstall()

    def make_package( self ):
        if self.traditional:
            self.instdestdir = "kde"
            self.instsrcdir = "taglib"
        return self.doPackaging( "taglib", "1.4.0-3", True )

subclass().execute()
