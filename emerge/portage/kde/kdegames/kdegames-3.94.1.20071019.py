import base
import utils
import os

DEPEND = """
kde/kdelibs
"""

class subclass(base.baseclass):
    def __init__(self):
        base.baseclass.__init__( self, "" )

    def unpack( self ):
        self.kdeSvnUnpack( "trunk/KDE/", "kdegames" )
        
        # for now disable libksirtet and ksirtet, they do not compile under mingw
        
        sed = r"""-e "s/add_subdirectory(libksirtet)/#add_subdirectory(libksirtet)/" """ \
              r"""-e "s/macro_optional_add_subdirectory(ksirtet)/#no ksirtet/" """ \
              r"""-e "s/macro_optional_add_subdirectory(kblackbox)/#no kblackbox/" """
    	  
        utils.sedFile( os.path.join( self.workdir, self.package ),
    	"CMakeLists.txt", sed )
        
        return True

    def compile( self ):
        return self.kdeCompile()
    
    def install( self ):
        return self.kdeInstall()

    def make_package( self ):
        return self.doPackaging( "kdegames", "3.94-1", True )

subclass().execute()
