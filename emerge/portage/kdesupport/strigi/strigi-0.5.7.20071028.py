import base
import os
import sys

DEPEND = """
virtual/base
libs/qt
kdesupport/kdewin32
kdesupport/clucene-core
"""

#currently build without clucene...

class subclass(base.baseclass):
    def __init__(self):
        base.baseclass.__init__( self, "" )
        self.instsrcdir = "strigi"

    def kdeSvnPath( self ):
        return "trunk/kdesupport/strigi"

    def unpack( self ):
        return self.kdeSvnUnpack()

    def compile( self ):
        return self.kdeCompile()

    def install( self ):
        return self.kdeInstall()

    def make_package( self ):
        if self.traditional:
            self.instdestdir = "kde"
            return self.doPackaging( "strigi", "0.5.7-1", True )
        else:
            return self.doPackaging( "strigi", os.path.basename(sys.argv[0]).replace("strigi-", "").replace(".py", ""), True )

subclass().execute()
