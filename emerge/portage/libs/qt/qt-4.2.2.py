import base
import utils
from utils import die
import os
import sys
import shutil

#DEPEND = """
#dev-util/dbus
#dev-util/mingw
#gnuwin32/sed
#gnuwin32/patch
#"""

SRC_URI= """
ftp://ftp.trolltech.com/pub/qt/source/qt-win-opensource-src-4.2.2.zip
http://switch.dl.sf.net/sourceforge/qtwin/acs-4.2.2-patch1.zip
"""

class subclass(base.baseclass):
  def __init__(self):
    base.baseclass.__init__( self, SRC_URI )
    self.instsrcdir="qt-win-opensource-src-4.2.2"
    self.instdestdir="qt"

  def unpack( self ):
    # apply patch from windbus to enable qdbus
    print "qt unpack called"
    utils.unpackFiles( self.downloaddir, self.filenames, self.workdir )
    os.chdir( os.path.join( self.workdir, "qt-win-opensource-src-4.2.2" ) )
    #patchfile = os.path.join( self.rootdir, \
    #    "distfiles\\svn-src\\windbus\\trunk\\QtDBus-win32.patch" )
    #command = "patch -p0 < %s" % patchfile
    #os.system( command ) and die( "qt patch" )
    
    # disable demo and example subdirs in main .pro file
    #file = "projects.pro"		
    #os.rename( file, "%s.orig" % file )
    #sedcommand = """ "s/\(SUBDIRS += demos\)/#\\1/" """ 		
    #command = "type %s.orig | sed -e %s > %s" % ( file, sedcommand, file )
    #print "command:", command
    #os.system( command )and die( "qt sed" )

    return True
    
  def compile( self ):
    print "qt compile called"
    print "press enter"
    sys.stdin.readline()

    os.chdir( os.path.join( self.workdir, "qt-win-opensource-src-4.2.2" ) )
    os.putenv( "DBUSDIR", os.path.join( self.rootdir, "dbus" ) )
    os.system( "echo yes | configure.exe" ) and die( "qt configure" )
    #print "press enter"
    #sys.stdin.readline()

    os.system( "mingw32-make" )and die( "qt make" )
    #print "press enter"
    #sys.stdin.readline()

    # now build qdbus
    os.chdir( "tools\\qdbus" )
    # set dbus dir...
    os.putenv( "DBUSDIR", os.path.join( self.rootdir, "dbus" ) )
    os.system( "..\\..\\bin\\qmake -recursive" ) and die( "dbus qmake" )
    os.system( "mingw32-make" ) and die( "dbus mingw32-make" )
    # here errors can happen, that seems to be ok...
    os.system( "mingw32-make install" )
    print "end of qt compile"
    return True

  def install( self ):
    print "qt install called"
    qtsrcdir = os.path.join( self.workdir, "qt-win-opensource-src-4.2.2" )
    os.chdir( qtsrcdir )
    ##os.system( "mingw32-make INSTALL_ROOT=%s install" % self.imagedir[2:] )
    os.chdir( "tools\\qdbus" )
    ##os.system( "mingw32-make INSTALL_ROOT=%s install" % self.imagedir[2:] )
    ##utils.moveImageDirContents( self.imagedir, qtsrcdir[3:], "qt" )

    # hmm, some programs are not installed, for example qmake.exe ...
    srcbindir = os.path.join( qtsrcdir, "bin" )
    destbindir = os.path.join( self.imagedir, "qt", "bin" )
    for entry in os.listdir( srcbindir ):
      print "got this entry:", entry
      shutil.copy( os.path.join( srcbindir, entry ), destbindir )
    return True

subclass().execute()
