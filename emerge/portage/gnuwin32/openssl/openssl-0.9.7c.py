import gnuwin32
import os

SRC_URI = """
http://switch.dl.sf.net/sourceforge/gnuwin32/openssl-0.9.7c-bin.zip
http://switch.dl.sf.net/sourceforge/gnuwin32/openssl-0.9.7c-lib.zip
"""

class subclass(gnuwin32.gnuwin32class):
  def __init__(self):
    gnuwin32.gnuwin32class.__init__( self, SRC_URI )
    
  def install( self ):
    print "openssl install called"
    
    # remove this file, because it collides with the one from wget
    os.remove( os.path.join( self.workdir, "bin", "libeay32.dll" ) )
    
    gnuwin32.gnuwin32class.install( self )
    
    return True

if __name__ == '__main__':
    subclass().execute()

