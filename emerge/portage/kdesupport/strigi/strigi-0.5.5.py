import base
import utils
from utils import die
import os

DEPEND = """
virtual/base
gnuwin32/openssl
kde/kdewin32
"""

class subclass(base.baseclass):
  def __init__(self):
    base.baseclass.__init__( self, "" )

  def unpack( self ):
    return self.kdeSvnUnpack( "trunk/kdesupport", "strigi" )

  def compile( self ):
    return self.kdeCompile()

  def install( self ):
    return self.kdeInstall()

  def make_package( self ):
    # FIXME?
    self.instdestdir = "kde"
    self.instsrcdir = "strigi"
    return self.doPackaging( "strigi", "0.5.5", True )

subclass().execute()
