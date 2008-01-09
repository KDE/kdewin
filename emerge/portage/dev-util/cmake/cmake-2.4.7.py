import base

SRC_URI= "http://www.cmake.org/files/v2.4/cmake-2.4.7-win32-x86.zip"

class subclass(base.baseclass):
  def __init__(self):
    base.baseclass.__init__( self, SRC_URI )
    self.instsrcdir = "cmake-2.4.7-win32-x86"
    if self.traditional:
      self.instdestdir = "cmake"

if __name__ == '__main__':
    subclass().execute()
