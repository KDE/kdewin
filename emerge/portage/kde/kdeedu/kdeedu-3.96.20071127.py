import base
import utils
import os
import sys

DEPEND = """
kde/kdebase
"""
OPTIONAL_DEPEND = """
kdesupport/eigen
win32libs-sources/cfitsio-src
win32libs-sources/libnova-src
win32libs-sources/openbabel-src
"""
class subclass(base.baseclass):
    def __init__(self):
        base.baseclass.__init__( self, "" )
        self.instsrcdir = "kdeedu"

    def kdeSvnPath( self ):
        return "trunk/KDE/kdeedu"
        
    def unpack( self ):
        return self.kdeSvnUnpack()

    def compile( self ):
        return self.kdeCompile()

    def install( self ):
        return self.kdeInstall()

    def make_package( self ):
        return self.doPackaging( "kdeedu", os.path.basename(sys.argv[0]).replace("kdeedu-", "").replace(".py", ""), True )

subclass().execute()
