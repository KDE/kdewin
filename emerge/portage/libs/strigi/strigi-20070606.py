import base
import utils
from utils import die
import os

DEPEND = """
virtual/base
gnuwin32/openssl
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
    print "%s compile called" % self.package
    os.chdir( self.workdir )

    builddir = "%s-build" % self.package

    if ( not os.path.exists( builddir ) ):
      os.mkdir( builddir )

    utils.cleanDirectory( builddir )

    os.chdir( builddir )

    options = "-DCMAKE_INSTALL_PREFIX=%s/strigi ..\\%s " % \
        ( self.rootdir.replace( "\\", "/" ), self.package )

    options = options + "-DKDEWIN32_INSTALL_PREFIX=%s " % \
        os.path.join( self.rootdir, "kdewin32" ).replace( "\\", "/" )

    options = options + "-DWIN32LIBS_INSTALL_PREFIX=%s " % \
        os.path.join( self.rootdir, "win32libs" ).replace( "\\", "/" )

    command = r"""cmake -G "MinGW Makefiles" %s """ % options 
    print "command: %s" % command
    os.system( command ) and die( "cmake" )
    os.system( "mingw32-make" ) and die( "mingw32-make" )
    
    return True

  def install( self ):
    return self.kdeInstall()

subclass().execute()
