import base
import utils
from utils import die
import os

DEPEND = """
virtual/base
"""

class subclass(base.baseclass):
    def __init__(self):
        base.baseclass.__init__( self, "" )
        # header-only package
        self.createCombinedPackage = True

    def kdeSvnPath( self ):
        return "trunk/kdesupport/gmm"

    def unpack( self ):
        return self.kdeSvnUnpack( "trunk/kdesupport", "gmm" )

    def compile( self ):
        return self.kdeCompile()

    def install( self ):
        return self.kdeInstall()

    def make_package( self ):
        # FIXME?
        if self.traditional:
            self.instdestdir = "kde"
            self.instsrcdir = "gmm"
        return self.doPackaging( "gmm", "20071019", True )

subclass().execute()
