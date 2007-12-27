import base
import utils
import os
import sys

DEPEND = """
kde/kdebase
"""

class subclass(base.baseclass):
    def __init__(self):
        self.buildType="Debug"
        base.baseclass.__init__( self, "" )
        self.instsrcdir = "kdevplatform"

    def kdeSvnPath( self ):
        return "trunk/KDE/kdevplatform"
        
    def unpack( self ):
        return self.kdeSvnUnpack()

    def compile( self ):
        return self.kdeCompile()

    def install( self ):
        return self.kdeInstall()

    def make_package( self ):
        return self.doPackaging( "kdevplatform", os.path.basename(sys.argv[0]).replace("kdevplatform-", "").replace(".py", ""), True )

subclass().execute()
