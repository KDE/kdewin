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
"""

class subclass(base.baseclass):
    def __init__(self):
        self.buildType = "Debug"
        base.baseclass.__init__( self, "" )
        self.instsrcdir = "kdelibs"

    def kdeSvnPath( self ):
        return "trunk/KDE/kdelibs"
        
    def unpack( self ):
        return self.kdeSvnUnpack()

    def compile( self ):
        self.kdeCustomDefines = "-DKDE4_BUILD_TESTS=OFF"
        return self.kdeCompile()

    def install( self ):
        return self.kdeInstall()

    def make_package( self ):
        return self.doPackaging( "kdelibs", os.path.basename(sys.argv[0]).replace("kdelibs-", "").replace(".py", ""), True )

if __name__ == '__main__':
    subclass().execute()
