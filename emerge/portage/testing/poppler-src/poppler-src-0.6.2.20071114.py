import base
import os
import utils
from utils import die

PACKAGE_NAME         = "poppler"
PACKAGE_VER          = "0.6.2"
PACKAGE_FULL_VER     = "0.6.2"
PACKAGE_FULL_NAME    = "%s-%s" % ( PACKAGE_NAME, PACKAGE_VER )
PACKAGE_DLL_NAME     = "poppler"

SRC_URI= """
http://poppler.freedesktop.org/""" + PACKAGE_FULL_NAME + """.tar.gz
"""

DEPEND = """
gnuwin32/patch
testing/freetype-src
testing/fontconfig-src
"""

class subclass(base.baseclass):
    def __init__( self ):
        base.baseclass.__init__( self, "" )

    def unpack( self ):
        if( not base.baseclass.unpack( self ) ):
            return False
            
        src = os.path.join( self.workdir, self.instsrcdir )

        cmd = "cd %s && patch -p0 < %s" % \
              ( os.path.join( self.workdir, self.instsrcdir ), os.path.join( self.packagedir , "poppler-cmake.patch" ) )
        if not self.stayQuiet:
            print cmd
        os.system( cmd ) or die( "patch" )

        return True
    def compile( self ):
        return self.kdeCompile()

    def install( self ):
        return self.kdeInstall()

    def make_package( self ):
        # auto-create both import libs with the help of pexports
        self.stripLibs( PACKAGE_DLL_NAME )

        # auto-create both import libs with the help of pexports
        self.createImportLibs( PACKAGE_DLL_NAME )

        # now do packaging with kdewin-packager
        self.doPackaging( PACKAGE_NAME, PACKAGE_FULL_VER, True )

        return True

subclass().execute()
