import base
import utils
from utils import die
import os

DEPEND = """
virtual/base
kde/kdewin32
"""

class subclass(base.baseclass):
  def __init__(self):
    base.baseclass.__init__( self, "" )

  def unpack( self ):
    return self.kdeSvnUnpack( "trunk/kdesupport", "soprano" )

  def compile( self ):
    return self.kdeCompile()

  def install( self ):
    return self.kdeInstall()

  def make_package( self ):
    # FIXME?
    self.instdestdir = "kde"
    self.instsrcdir = "soprano"
    return self.doPackaging( "soprano", "20070915", True )

subclass().execute()
