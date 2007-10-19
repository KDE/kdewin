import base
import utils
import os

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

    def unpack( self ):
        return self.kdeSvnUnpack( "trunk/KDE", "kdelibs" )

    def compile( self ):
        self.kdeCustomDefines = "-DKDE4_BUILD_TESTS=OFF"
        return self.kdeCompile()

    def install( self ):
        return self.kdeInstall()

    def make_package( self ):
        return self.doPackaging( "kdelibs", "3.94-1", True )

subclass().execute()
