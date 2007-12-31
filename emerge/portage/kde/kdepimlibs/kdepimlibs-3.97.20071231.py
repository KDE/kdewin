import base
import utils
import os
import sys

DEPEND = """
kde/kdelibs
"""

class subclass(base.baseclass):
    def __init__(self):
        base.baseclass.__init__( self, "" )
        self.instsrcdir = "kdepimlibs"

    def kdeSvnPath( self ):
        return "trunk/KDE/kdepimlibs"
        
    def unpack( self ):
        return self.kdeSvnUnpack()

    def compile( self ):
        # add env var so that boost headers are found
        path = os.path.join( self.rootdir, "win32libs" )
        os.putenv( "BOOST_ROOT", path )

        return self.kdeCompile()

    def install( self ):
        return self.kdeInstall()

    def make_package( self ):
        return self.doPackaging( "kdepimlibs", os.path.basename(sys.argv[0]).replace("kdepimlibs-", "").replace(".py", ""), True )


subclass().execute()
