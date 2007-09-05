import gnuwin32

SRC_URI = """
http://switch.dl.sf.net/sourceforge/gnuwin32/sed-4.1.4-bin.zip
http://switch.dl.sf.net/sourceforge/gnuwin32/sed-4.1.4-dep.zip
"""

class subclass(gnuwin32.gnuwin32class):
  def __init__(self):
    gnuwin32.gnuwin32class.__init__( self, SRC_URI )

subclass().execute()
