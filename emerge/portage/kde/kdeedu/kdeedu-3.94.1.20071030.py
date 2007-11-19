import base
import utils
import os

DEPEND = """
kde/kdebase
"""
OPTIONAL_DEPEND = """
kdesupport/eigen
win32libs-sources/cfitsio-src
win32libs-sources/openbabel-src
"""
class subclass(base.baseclass):
    def __init__(self):
        base.baseclass.__init__( self, "" )

    def kdeSvnPath( self ):
        return "trunk/KDE/kdeedu"
        
    def unpack( self ):
        return self.kdeSvnUnpack( "trunk/KDE", "kdeedu" )

    def compile( self ):
        return self.kdeCompile()

    def install( self ):
        return self.kdeInstall()

    def make_package( self ):
        return self.doPackaging( "kdeedu", "3.94-1", True )

subclass().execute()
