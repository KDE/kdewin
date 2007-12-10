import base
import utils
import os
import sys

DEPEND = """
kde/kdebase
"""

class subclass(base.baseclass):
    def __init__(self):
        base.baseclass.__init__( self, "" )
        self.instsrcdir = "kdetoys"
        
    def kdeSvnPath( self ):
        return "trunk/KDE/kdetoys"
        
    def unpack( self ):
        return self.kdeSvnUnpack()

    def compile( self ):
        return self.kdeCompile()

    def install( self ):
        return self.kdeInstall()

    def make_package( self ):
        return self.doPackaging( "kdetoys", os.path.basename(sys.argv[0]).replace("kdetoys-", "").replace(".py", ""), True )

subclass().execute()
