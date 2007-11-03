import base
import os
import shutil

PACKAGE_NAME         = "boost-jam"
PACKAGE_VER          = "3.1.15"
PACKAGE_FULL_VER     = "3.1.15-1"
PACKAGE_FULL_NAME    = "%s-%s" % ( PACKAGE_NAME, PACKAGE_FULL_VER)

SRC_URI= """
http://downloads.sourceforge.net/boost/""" + PACKAGE_FULL_NAME + """-ntx86.zip
"""

DEPEND = """
"""

class subclass(base.baseclass):
    def __init__(self):
        base.baseclass.__init__( self, SRC_URI )
        if self.traditional:
            self.instdestdir = "bjam\bin"
        else:
            self.instdestdir = "bin"
        self.instsrcdir = PACKAGE_FULL_NAME + "-ntx86"

subclass().execute()
