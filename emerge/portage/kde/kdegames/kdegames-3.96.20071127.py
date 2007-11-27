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
        self.instsrcdir = "kdegames"

    def kdeSvnPath( self ):
        return "trunk/KDE/kdegames"
        
    def unpack( self ):
        self.kdeSvnUnpack()
        return True

    def compile( self ):
        return self.kdeCompile()
    
    def install( self ):
        return self.kdeInstall()

    def make_package( self ):
        return self.doPackaging( "kdegames", os.path.basename(sys.argv[0]).replace("kdegames-", "").replace(".py", ""), True )

subclass().execute()
