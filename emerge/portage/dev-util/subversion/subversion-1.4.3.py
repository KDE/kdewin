import base

SRC_URI = "http://subversion.tigris.org/downloads/svn-win32-1.4.3.zip"

class subclass(base.baseclass):
  def __init__(self):
    base.baseclass.__init__( self, SRC_URI )
    self.instsrcdir = "svn-win32-1.4.3"
    self.instdestdir = "subversion"

subclass().execute()
