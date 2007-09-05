import base
import utils
from utils import die
import os

# FIXME implement shadow build and installation into image dir.

DEPEND = """
dev-util/dbus
virtual/base
"""

SRC_URI= """
ftp://ftp.trolltech.com/qt/source/qt-all-opensource-src-4.3.0.tar.gz
"""

class subclass(base.baseclass):
  def __init__(self):
    base.baseclass.__init__( self, SRC_URI )

  def unpack( self ):
    print "qt unpack called"
    qtsrcdir = os.path.join( self.workdir, "qt-all-opensource-src-4.3.0" )

    base.baseclass.unpack( self )
    
    # disable demos and examples
    sedcommand = r""" -e "s:SUBDIRS += examples::" -e "s:SUBDIRS += demos::" """
    utils.sedFile( qtsrcdir, "projects.pro", sedcommand )
    
    # patch to disable building of pbuilder_pbx.cpp, as it takes ages
    path = os.path.join( qtsrcdir, "qmake" )
    file = "Makefile.win32-g++"
    sedcommand = """ -e "s/pbuilder_pbx.o//" """
    utils.sedFile( path, file, sedcommand )

    # disable usage of it
    path = os.path.join( qtsrcdir, "qmake", "generators" )
    file = "metamakefile.cpp"
    sedcommand = r""" -e "s:^.*ProjectBuilder://\0:" """
    utils.sedFile( path, file, sedcommand )

    # somehow linking against jpeg only works with this change for me...
    path = os.path.join( qtsrcdir, "src", "plugins", "imageformats", "jpeg" )
    file = "jpeg.pro"
    sedcommand = r""" -e "s/libjpeg.lib/-ljpeg/" """
    utils.sedFile( path, file, sedcommand )

    # somehow linking against tiff only works with this change for me...
    path = os.path.join( qtsrcdir, "src", "plugins", "imageformats", "tiff" )
    file = "tiff.pro"
    sedcommand = r""" -e "s/libtiff.lib/-ltiff/" """
    utils.sedFile( path, file, sedcommand )
    return True

  def compile( self ):
    print "qt compile called"
    qtsrcdir = os.path.join( self.workdir, "qt-all-opensource-src-4.3.0" )
    os.chdir( qtsrcdir )

    # so that the mkspecs can be found, when -prefix is set
    os.putenv( "QMAKEPATH", qtsrcdir )

    win32incdir = os.path.join( self.rootdir, "win32libs", "include" ) \
                  .replace( "\\", "/" )
    win32libdir = os.path.join( self.rootdir, "win32libs", "lib" ) \
                  .replace( "\\", "/" )

    dbusincdir = os.path.join( self.rootdir, "dbus", "include" ) \
                  .replace( "\\", "/" )
    dbuslibdir = os.path.join( self.rootdir, "dbus", "lib" ) \
                  .replace( "\\", "/" )

    # recommended from README.qt-copy
    #  "configure.exe -prefix ..\..\image\qt -platform win32-g++ " \
    #  "-qt-gif -no-exceptions -debug -system-zlib -system-libpng -system-libmng " \
    #  "-system-libtiff -system-libjpeg -openssl " \
    #  "-I %s -L %s" % ( win32incdir, win32libdir )

    # configure qt
    prefix = os.path.join( self.rootdir, "qt" ).replace( "\\", "/" )
    command = r"echo yes | configure.exe -prefix %s " \
      "-platform win32-g++ " \
      "-qdbus -qt-gif -no-exceptions -debug -qt-libpng " \
      "-system-libjpeg -system-libtiff -openssl " \
      "-I %s -L %s -I %s -L %s" % ( prefix, win32incdir, win32libdir, dbusincdir, dbuslibdir )
    print "command: ", command
    os.system( command ) and die( "qt configure failed" )

    # build qt
    os.system( "mingw32-make" )and die( "qt make failed" )
    return True

  def install( self ):
    # FIXME create bin/qt.conf, so that qmake -v gives the right path
    print "qt install called"
    qtsrcdir = os.path.join( self.workdir, "qt-all-opensource-src-4.3.0" )
    os.chdir( qtsrcdir )

    os.system( "mingw32-make install" ) and die( "qt make install failed" )
    return True

subclass().execute()
