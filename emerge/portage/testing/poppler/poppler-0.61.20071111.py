import base
import os
import utils

PACKAGE_NAME         = "poppler"
PACKAGE_VER          = "0.61"
PACKAGE_FULL_VER     = "0.61"
PACKAGE_FULL_NAME    = "%s-%s" % ( PACKAGE_NAME, PACKAGE_VER )
PACKAGE_DLL_NAME     = "poppler"

SRC_URI= """
http://poppler.freedesktop.org/poppler-0.6.2.tar.gz
"""

DEPEND = """
testing/freetype-src
testing/fontconfig-src
"""

class subclass(base.baseclass):
    def __init__( self ):
        base.baseclass.__init__( self, "" )

subclass().execute()
