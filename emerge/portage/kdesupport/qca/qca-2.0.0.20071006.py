import base
import utils
import os

DEPEND = """
virtual/base
libs/qt
"""

class subclass(base.baseclass):
  def __init__(self):
    base.baseclass.__init__( self, "" )

  def unpack( self ):
    return self.kdeSvnUnpack( "trunk/kdesupport", "qca" )

  def compile( self ):
    return self.kdeCompile()

  def install( self ):
    return self.kdeInstall()

  def make_package( self ):
    # FIXME?
    if self.traditional:
        self.instdestdir = "kde"
    self.instsrcdir = "qca"
    return self.doPackaging( "qca", "2.0.0-3", True )

subclass().execute()
