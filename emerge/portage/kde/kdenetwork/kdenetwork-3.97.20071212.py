import base
import utils
import os
import sys


DEPEND = """
virtual/base
dev-util/win32libs
kdesupport/kdewin32
kdesupport/qimageblitz
kdesupport/soprano
kdesupport/strigi
kde/kdebase
"""

class subclass(base.baseclass):
    def __init__(self):
        base.baseclass.__init__( self, "" )
        self.instsrcdir = "kdenetwork"

    def kdeSvnPath( self ):
        return "trunk/KDE/kdenetwork"
        
    def unpack( self ):
        return self.kdeSvnUnpack()

    def compile( self ):
        return self.kdeCompile()

    def install( self ):
        return self.kdeInstall()

    def make_package( self ):
        return self.doPackaging( "kdenetwork", os.path.basename(sys.argv[0]).replace("kdenetwork-", "").replace(".py", ""), True )

if __name__ == '__main__':
    subclass().execute()
