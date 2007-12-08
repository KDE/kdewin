import base


"""
from trolltech mingw package:

binutils-2.15.91-20040904-1.tar.gz
gcc-core-3.4.2-20040916-1.tar.gz
gcc-g++-3.4.2-20040916-1.tar.gz
mingw32-make-3.80.0-3.exe
mingw-runtime-3.7.tar.gz -> 3.9
w32api-3.2.tar.gz -> 3.6
"""

SRC_URI = """
http://heanet.dl.sourceforge.net/sourceforge/mingw/binutils-2.17.50-20060824-1.tar.gz
http://heanet.dl.sourceforge.net/sourceforge/mingw/gcc-core-3.4.5-20060117-1.tar.gz
http://heanet.dl.sourceforge.net/sourceforge/mingw/gcc-g++-3.4.5-20060117-1.tar.gz
http://heanet.dl.sourceforge.net/sourceforge/mingw/mingw32-make-3.81-2.tar.gz
http://heanet.dl.sourceforge.net/sourceforge/mingw/mingw-runtime-3.12.tar.gz
http://heanet.dl.sourceforge.net/sourceforge/mingw/w32api-3.9.tar.gz
http://heanet.dl.sourceforge.net/sourceforge/mingw/gdb-6.3-2.tar.bz2
"""

class subclass(base.baseclass):
    def __init__( self ):
        base.baseclass.__init__( self, SRC_URI )
#        if self.traditional:
        self.instdestdir = "mingw"

subclass().execute()
