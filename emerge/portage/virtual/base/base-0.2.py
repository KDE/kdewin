import base

DEPENDS = """
dev-util/cmake
dev-util/mingw
dev-util/perl
dev-util/subversion
dev-util/win32libs
gnuwin32/patch
gnuwin32/sed
gnuwin32/wget
""" 

class subclass(base.baseclass):
  def __init__(self):
    base.baseclass.__init__( self, "" )

subclass().execute()