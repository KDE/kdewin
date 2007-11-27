import base
import os
import sys

DEPEND = """
virtual/base
libs/qt
"""

class subclass(base.baseclass):
    def __init__(self):
        base.baseclass.__init__( self, "" )
        self.instsrcdir = "qimageblitz"

    def kdeSvnPath( self ):
        return "trunk/kdesupport/qimageblitz"

    def unpack( self ):
        return self.kdeSvnUnpack()

    def compile( self ):
        return self.kdeCompile()

    def install( self ):
        return self.kdeInstall()

    def make_package( self ):
        if self.traditional:
            self.instdestdir = "kde"
            return self.doPackaging( "qimageblitz", "4.0.0-3", True )
        else:
            return self.doPackaging( "qimageblitz", os.path.basename(sys.argv[0]).replace("qimageblitz-", "").replace(".py", ""), True )

subclass().execute()
