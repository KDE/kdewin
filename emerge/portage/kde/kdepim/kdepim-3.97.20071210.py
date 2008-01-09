import base
import os
import sys

DEPEND = """
kde/kdebase
kde/kdepimlibs
"""

class subclass(base.baseclass):
    def __init__(self):
        base.baseclass.__init__( self, "" )
        self.instsrcdir = "kdepim"

    def kdeSvnPath( self ):
        return "trunk/KDE/kdepim"
        
    def unpack( self ):
        return self.kdeSvnUnpack()

    def compile( self ):
        return self.kdeCompile()

    def install( self ):
        return self.kdeInstall()

    def make_package( self ):
        return self.doPackaging( "kdepim", os.path.basename(sys.argv[0]).replace("kdepim-", "").replace(".py", ""), True )
		
if __name__ == '__main__':
    subclass().execute()
