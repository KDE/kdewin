import base
import utils
import os

DEPEND = """
kde/kdelibs
"""

class subclass(base.baseclass):
    def __init__(self):
        base.baseclass.__init__( self, "" )

    def kdeSvnPath( self ):
        return "trunk/KDE/kdepimlibs"
        
    def unpack( self ):
        return self.kdeSvnUnpack( "trunk/KDE", "kdepimlibs" )

    def compile( self ):
        # add env var so that boost headers are found
        path = os.path.join( self.rootdir, "win32libs" )
        os.putenv( "BOOST_ROOT", path )

        return self.kdeCompile()

    def install( self ):
        return self.kdeInstall()

    def make_package( self ):
        return self.doPackaging( "kdepimlibs", "3.94-1", True )


subclass().execute()
