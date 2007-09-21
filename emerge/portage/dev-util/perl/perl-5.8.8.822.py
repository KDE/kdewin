import base

SRC_URI= "http://downloads.activestate.com/ActivePerl/Windows/5.8/ActivePerl-5.8.8.822-MSWin32-x86-280952.zip"

class subclass(base.baseclass):
  def __init__(self):
    base.baseclass.__init__( self, SRC_URI )
    self.instsrcdir = "ActivePerl-5.8.8.822-MSWin32-x86-280952\\perl"
    if self.traditional:
        self.instdestdir = "perl"
		
subclass().execute()
