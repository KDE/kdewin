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
    self.kdeSvnUnpack( "trunk/kdesupport", "strigi" )

    #copy the needed changed cmake files over...
    destdir = os.path.join( self.workdir, "strigi", "cmake" )
    utils.copySrcDirToDestDir( self.filesdir, destdir )

    # now patch config.h.cmake for ICONV_SECOND_ARGUMENT_IS_CONST
    path = os.path.join( self.workdir, "strigi" )
    file = "config.h.cmake"
    sedcommand = """ -e "s/cmakedefine ICONV_SECOND/define ICONV_SECOND/" """
    utils.sedFile( path, file, sedcommand )

    return True

  def compile( self ):
    return self.kdeCompile()

  def install( self ):
    return self.kdeInstall()

subclass().execute()
