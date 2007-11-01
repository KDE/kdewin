import base
import utils
import os

DEPEND = """
kde/kdebase
"""

class subclass(base.baseclass):
  def __init__(self):
    base.baseclass.__init__( self, "" )
    self.instsrcdir = "kdegraphics"
    if self.traditional:
        self.instdestdir = "kde"

  def unpack( self ):
    return self.kdeSvnUnpack( "trunk/KDE/", "kdegraphics" )

  def compile( self ):
    return self.kdeCompile()

  def install( self ):
    return self.kdeInstall()

  def make_package( self ):
    return self.doPackaging( "kdegraphics", "3.94-1", True )

subclass().execute()
