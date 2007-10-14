import base

SRC_URI = "http://subversion.tigris.org/downloads/1.4.5-win32/apache-2.0/svn-win32-1.4.5.zip"

class subclass(base.baseclass):
  def __init__(self):
    base.baseclass.__init__( self, SRC_URI )
    self.instsrcdir = "svn-win32-1.4.5"
    if self.traditional:
        self.instdestdir = "subversion"

subclass().execute()
