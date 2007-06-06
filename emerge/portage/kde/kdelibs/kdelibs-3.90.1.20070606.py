import base
import utils
import os

DEPEND = """
virtual/base
dev-util/dbus
dev-util/win32libs
kde/kdewin32
libs/strigi
"""

class subclass(base.baseclass):
  def __init__(self):
    base.baseclass.__init__( self, "" )

  def unpack( self ):
    return self.kdeSvnUnpack( "trunk/KDE", "kdelibs" )

  def compile( self ):
    self.kdeCustomDefines = "-DKDE4_BUILD_TESTS=ON"
    return self.kdeCompile()

  def install( self ):
    return self.kdeInstall()

subclass().execute()
