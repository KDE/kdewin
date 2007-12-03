import base

SRC_URI= """
http://downloads.sourceforge.net/gnuwin32/gettext-0.14.4-bin.zip
http://downloads.sourceforge.net/gnuwin32/gettext-0.14.4-lib.zip
http://downloads.sourceforge.net/gnuwin32/libgw32c-0.4-lib.zip
"""

DEPEND = """
dev-util/win32libs
"""
class subclass(base.baseclass):
  def __init__(self):
    base.baseclass.__init__( self, SRC_URI )
    if self.traditional:
        self.instdestdir = "win32libs"
    else:
        self.instdestdir = ""

subclass().execute()
