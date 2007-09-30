import base
import utils
import shutil
import os

SRC_URI= """
http://garr.dl.sourceforge.net/sourceforge/clucene/clucene-core-0.9.16a.tar.bz2
"""

DEPEND = """
virtual/base
"""

class subclass(base.baseclass):
  def __init__(self):
    base.baseclass.__init__( self, SRC_URI )
    self.instsrcdir = os.path.join( "clucene-core-0.9.16a", "src" )

  def compile( self ):
    # we have an own cmake script - copy it to the right place
    cmake_script = os.path.join( self.packagedir , "CMakeLists.txt" )
    cmake_dest = os.path.join( self.workdir, self.instsrcdir, "CMakeLists.txt" )
    shutil.copy( cmake_script, cmake_dest )

    return self.kdeCompile()

  def install( self ):
    return self.kdeInstall()

  def make_package( self ):
    # FIXME?
    if self.traditional:
        self.instdestdir = "kde"
    self.instsrcdir = "clucene"
    return self.doPackaging( "clucene", "0.9.16a-1", True )

subclass().execute()
