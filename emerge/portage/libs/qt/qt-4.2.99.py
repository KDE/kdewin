import base
import utils
from utils import die
import os
import sys
import shutil

DEPEND = """
dev-util/dbus
dev-util/mingw
gnuwin32/sed
gnuwin32/patch
"""

#SRC_URI= """
#http://switch.dl.sf.net/sourceforge/qtwin/acs-4.2.2-patch1.zip
#"""

class subclass(base.baseclass):
  def __init__(self):
    #base.baseclass.__init__( self, SRC_URI )
    base.baseclass.__init__( self, "" )

  def unpack( self ):
    # apply patch from windbus to enable qdbus
    print "qt unpack called"
    svnpath = "trunk"
    packdir = "qt-copy"
    self.kdeSvnUnpack( svnpath, packdir )
	
    #utils.unpackFile( self.downloaddir, "acs-4.2.2-patch1.zip", \
    #	os.path.join( self.workdir, "qt-win-opensource-src-4.2.2" ) )

    os.chdir( os.path.join( self.workdir, "qt-copy" ) )
    patchfile = os.path.join( self.downloaddir, \
        "svn-src\\dbus\\trunk\\QtDBus-win32-qt43.patch" )
    command = "patch -p0 < %s" % patchfile
    os.system( command ) and die( "qt patch" )
    
    # apply additional compiler support patch
    #os.system( r"qtwin_patch\patch.exe -p1 -i qtwin_patch\msvc_bcc32_42.patch") \
    #	and die ( "installpatch" )
    return True
    
  def compile( self ):
    print "qt compile called"

    os.chdir( os.path.join( self.workdir, "qt-copy" ) )
    os.putenv( "DBUSDIR", os.path.join( self.rootdir, "dbus" ) )
    os.system( "echo yes | configure.exe" ) and die( "qt configure" )

    os.system( "mingw32-make sub-src sub-tools" )and die( "qt make" )

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
    qtsrcdir = os.path.join( self.workdir, "qt-copy" )
    os.chdir( qtsrcdir )
    os.system( "mingw32-make INSTALL_ROOT=%s install" % self.imagedir[2:] )
    os.chdir( "tools\\qdbus" )
    os.system( "mingw32-make INSTALL_ROOT=%s install" % self.imagedir[2:] )
    utils.moveImageDirContents( self.imagedir, qtsrcdir[3:], "qt" )

    # hmm, some programs are not installed, for example qmake.exe ...
    srcbindir = os.path.join( qtsrcdir, "bin" )
    destbindir = os.path.join( self.imagedir, "qt", "bin" )
    for entry in os.listdir( srcbindir ):
      print "got this entry:", entry
      shutil.copy( os.path.join( srcbindir, entry ), destbindir )
    return True

subclass().execute()
