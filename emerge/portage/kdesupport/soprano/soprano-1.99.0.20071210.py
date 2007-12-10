import base
import os
import sys


DEPEND = """
virtual/base
libs/qt
kdesupport/clucene-core
"""

class subclass(base.baseclass):
    def __init__(self):
        base.baseclass.__init__( self, "" )
        self.instsrcdir = "soprano"

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
            return self.doPackaging( "soprano", "1.99.0-1", True )
        else:
            return self.doPackaging( "soprano", os.path.basename(sys.argv[0]).replace("soprano-", "").replace(".py", ""), True )

subclass().execute()
