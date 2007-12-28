import base
import utils
import os
import sys

DEPEND = """
testing/kdevplatform
kde/kdebase
"""

class subclass(base.baseclass):
    def __init__(self):
        base.baseclass.__init__( self, "" )
        self.instsrcdir = "kdevelop"

    def kdeSvnPath( self ):
        return "trunk/KDE/kdevelop"
        
    def unpack( self ):
        return self.kdeSvnUnpack()

    def compile( self ):
        return self.kdeCompile()
    
    def install( self ):
        return self.kdeInstall()

    def make_package( self ):
        return self.doPackaging( "kdevelop", os.path.basename(sys.argv[0]).replace("kdevelop-", "").replace(".py", ""), True )

subclass().execute()
