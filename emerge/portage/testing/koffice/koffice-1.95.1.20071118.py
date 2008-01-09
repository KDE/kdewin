import base
import os
import utils

DEPEND = """
win32libs-sources/lcms-src
kde/kdelibs
kde/kdepimlibs
"""

class subclass(base.baseclass):
    def __init__( self ):
        base.baseclass.__init__( self, "" )
        self.instsrcdir = "koffice"

    def kdeSvnPath( self ):
        return "trunk/koffice"

    def unpack( self ):
        unp = self.kdeSvnUnpack()
        # now copy the tree to workdir
        return unp


    def kdeDefaultDefines( self ):
        options = base.baseclass.kdeDefaultDefines( self )
#        options = options + "-DBUILD_karbon=OFF "
#        options = options + "-DBUILD_kdgantt=OFF "
#        options = options + "-DBUILD_kexi=OFF "
#        options = options + "-DBUILD_kivio=OFF "
#        options = options + "-DBUILD_kounavail=OFF "
#        options = options + "-DBUILD_kplato=OFF "
#        options = options + "-DBUILD_krita=OFF "
#        options = options + "-DBUILD_kword=OFF "
        options = options + "-DBUILD_doc=OFF "
        return options

    def compile( self ):
        return self.kdeCompile()

    def install( self ):
        return self.kdeInstall()

    def make_package( self ):
        return self.doPackaging( "koffice", "1.95-1", True )
		
if __name__ == '__main__':
    subclass().execute()
