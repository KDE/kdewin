import base
import os
import utils

PACKAGE_NAME         = "poppler"
PACKAGE_VER          = "0.62"
PACKAGE_FULL_VER     = "0.62"
PACKAGE_FULL_NAME    = "%s-%s" % ( PACKAGE_NAME, PACKAGE_VER )
PACKAGE_DLL_NAME     = "poppler"

SRC_URI= """
http://poppler.freedesktop.org/""" + PACKAGE_FULL_NAME + """.tar.gz
"""

DEPEND = """
gnuwin32/diffutils
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
        os.system( cmd ) or die

        return True


subclass().execute()
