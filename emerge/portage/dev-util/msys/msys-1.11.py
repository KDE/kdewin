import base
import utils
from utils import die
import os

SRC_URI = """
http://heanet.dl.sourceforge.net/mingw/msysCORE-1.0.11-2007.01.19-1.tar.bz2
"""

class subclass(base.baseclass):
    def __init__( self ):
        base.baseclass.__init__( self, SRC_URI )
        self.instdestdir = "msys"
	
if __name__ == '__main__':
    subclass().execute()
