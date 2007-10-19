import base
import utils
import os

DEPEND = """
kde/kdebase
"""

class subclass(base.baseclass):
    def __init__(self):
        base.baseclass.__init__( self, "" )

    def unpack( self ):
        return self.kdeSvnUnpack( "trunk/KDE", "kdeedu" )

    def compile( self ):
        return self.kdeCompile()

    def install( self ):
        return self.kdeInstall()

    def make_package( self ):
        return self.doPackaging( "kdeedu", "3.94-1", True )

subclass().execute()
