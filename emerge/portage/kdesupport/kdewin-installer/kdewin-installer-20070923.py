import base
import utils
from utils import die
import os

DEPEND = """
virtual/base
libs/qt
"""

class subclass(base.baseclass):
  def __init__(self):
    base.baseclass.__init__( self, "" )

  def unpack( self ):
    return self.kdeSvnUnpack( "trunk/kdesupport", "kdewin-installer" )

  def compile( self ):
    return self.kdeCompile()

  def install( self ):
    return self.kdeInstall()

  def make_package( self ):
    # FIXME?
    if self.traditional:
        self.instdestdir = "kde"
    self.instsrcdir = "kdewin-installer"
    return self.doPackaging( "kdewin-installer", "20070923", True )

subclass().execute()
