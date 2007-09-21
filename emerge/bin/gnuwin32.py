import base
import utils
import os

class gnuwin32class(base.baseclass):
  def __init__( self, SRC_URI ):
    base.baseclass.__init__( self, SRC_URI )

  def install( self ):
    if not self.stayQuiet:
        print "gnuwin32 install called"
    if self.traditional:
        destdir = os.path.join( self.imagedir, "gnuwin32" )
    else:
        destdir = self.imagedir
    utils.copySrcDirToDestDir( self.workdir, destdir )
    return True
