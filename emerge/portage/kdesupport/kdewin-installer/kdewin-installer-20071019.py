import base
import utils
from utils import die
import os
import sys

DEPEND = """
virtual/base
libs/qt
"""

class subclass(base.baseclass):
    def __init__(self):
        base.baseclass.__init__( self, "" )
        self.instsrcdir = "kdewin-installer"

    def kdeSvnPath( self ):
        return "trunk/kdesupport/kdewin-installer"

    def unpack( self ):
        return self.kdeSvnUnpack()

    def compile( self ):
        return self.kdeCompile()

    def install( self ):
        return self.kdeInstall()

    def make_package( self ):
        if self.traditional:
            self.instdestdir = "kde"
        return self.doPackaging( "kdewin-installer", os.path.basename(sys.argv[0]).replace("kdewin-installer-", "").replace(".py", ""), True )

subclass().execute()
