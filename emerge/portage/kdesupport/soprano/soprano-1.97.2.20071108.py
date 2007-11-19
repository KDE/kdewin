import base

DEPEND = """
virtual/base
libs/qt
kdesupport/clucene-core
"""

class subclass(base.baseclass):
    def __init__(self):
        base.baseclass.__init__( self, "" )

    def kdeSvnPath( self ):
        return "trunk/kdesupport/soprano"

    def unpack( self ):
        return self.kdeSvnUnpack()

    def compile( self ):
        return self.kdeCompile()

    def install( self ):
        return self.kdeInstall()

    def make_package( self ):
        if self.traditional:
            self.instdestdir = "kde"
            self.instsrcdir = "soprano"
        return self.doPackaging( "soprano", "1.97.2-1", True )

subclass().execute()
