import base
import utils
from utils import die
import os

DEPEND = """
virtual/base
libs/qt
"""

class subclass(base.baseclass):
    def __init__(self):
        base.baseclass.__init__( self, "" )

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
            self.instsrcdir = "kdewin-installer"
        return self.doPackaging( "kdewin-installer", "20071019", True )

subclass().execute()
