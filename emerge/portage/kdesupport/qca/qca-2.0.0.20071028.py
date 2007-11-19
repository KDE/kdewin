import base

DEPEND = """
virtual/base
libs/qt
"""

class subclass(base.baseclass):
    def __init__(self):
        base.baseclass.__init__( self, "" )

    def kdeSvnPath( self ):
        return "trunk/kdesupport/qca"

    def unpack( self ):
        return self.kdeSvnUnpack( "trunk/kdesupport", "qca" )

    def compile( self ):
        return self.kdeCompile()

    def install( self ):
        return self.kdeInstall()

    def make_package( self ):
        if self.traditional:
            self.instdestdir = "kde"
            self.instsrcdir = "qca"
        return self.doPackaging( "qca", "2.0.0-4", True )

subclass().execute()
