import base
import utils
from utils import die
import os
import sys

DEPEND = """
virtual/base
"""

class subclass(base.baseclass):
    def __init__(self):
        base.baseclass.__init__( self, "" )
        # header-only package
        self.createCombinedPackage = True
        self.instsrcdir = "gmm"

    def kdeSvnPath( self ):
        return "trunk/kdesupport/gmm"

    def unpack( self ):
        return self.kdeSvnUnpack()

    def compile( self ):
        return self.kdeCompile()

    def install( self ):
        return self.kdeInstall()

    def make_package( self ):
        # FIXME?
        if self.traditional:
            self.instdestdir = "kde"
        return self.doPackaging( "gmm", os.path.basename(sys.argv[0]).replace("gmm-", "").replace(".py", ""), True )        

subclass().execute()
