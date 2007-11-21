import base
import os

SRC_URI= "ftp://ftp.ruby-lang.org/pub/ruby/binaries/mswin32/ruby-1.8.6-i386-mswin32.zip"

class subclass(base.baseclass):
  def __init__(self):
    base.baseclass.__init__( self, SRC_URI )
    if self.traditional:
        self.instdestdir = "ruby"

  def unpack(self):
    res = base.baseclass.unpack( self )
    # ruby package contains a file called MANIFEST that we need to get
    # out of the way so we can make the manifest dir
    if res:
      os.remove( os.path.join( self.workdir, self.instsrcdir, "MANIFEST" ) )
    return res

subclass().execute()
