import base
import utils
from utils import die
import os
import sys
import shutil

# ok, in the end this would be cool to compile qt, but it does not work yet
# mkdir work/qt-copy
# mkdir work/qt-build
# mkdir image/qt
#
# cd work\qt-build
# ..\qt-copy\configure.exe -prefix ..\..\image\qt
# does not work yet

# include/QtCore/qatomic_windows.h from src/corelib/arch
# include/QtCore/qt_windows.h from src/corelib/global


DEPEND = """
dev-util/dbus
virtual/base
"""

class subclass(base.baseclass):
  def __init__(self):
    base.baseclass.__init__( self, "" )

  def unpack( self ):
    print "qt unpack called"
    svnpath = "trunk"
    packdir = "qt-copy"
    self.kdeSvnUnpack( svnpath, packdir )

    os.chdir( os.path.join( self.workdir ) )
    os.mkdir( "qt-build" )
	
    # patch qdbuscpp2xml to create usable xml files
    #os.chdir( os.path.join( self.workdir, "qt-copy" ) )
    #file = "tools\\qdbus\\tools\\qdbuscpp2xml\\qdbuscpp2xml.cpp"
    #os.rename( file, "%s.orig" % file )
    #sedcommand = r""" "s:input->readLine():input->readLine().replace( \"\\r\\n\", \"\\n\" ):" """
    #command = "type %s.orig | sed -e %s > %s" % ( file, sedcommand, file )
    #os.system( command ) and die( "qt sed" )

    # enable qdbus like this, so that no change of .qmake.cache is needed
    # after configure run, it forgot the install prefix...
    os.chdir( os.path.join( self.workdir, "qt-copy" ) )
    file = "tools\\tools.pro"
    os.rename( file, "%s.orig" % file )
    sedcommand = r""" "s:qtestlib:qtestlib qdbus:" """
    command = "type %s.orig | sed -e %s > %s" % ( file, sedcommand, file )
    os.system( command ) and die( "qt sed" )


    # patch to disable usage of pbuilder_pbx.cpp, as it hangs the compiler
    # update: it just takes minutes to compile this single file, so it works, but is slow...
    os.chdir( os.path.join( self.workdir, "qt-copy", "qmake" ) )
    file = "Makefile.win32-g++"
    os.rename( file, "%s.orig" % file )
    sedcommand = """ "s/pbuilder_pbx.o//" """
    command = "type %s.orig | sed -e %s > %s" % ( file, sedcommand, file )
    os.system( command ) and die( "qt sed" )
    
    # disable usage of it
    os.chdir( os.path.join( self.workdir, "qt-copy", "qmake" ) )
    file = "generators\\metamakefile.cpp"
    os.rename( file, "%s.orig" % file )
    sedcommand = r""" "s:^.*ProjectBuilder://\0:" """
    command = "type %s.orig | sed -e %s > %s" % ( file, sedcommand, file )
    os.system( command ) and die( "qt sed" )
    
    # somehow linking against jpeg only works with this change for me...
    os.chdir( os.path.join( self.workdir, "qt-copy", "src", "plugins" ) )
    file = "imageformats\\jpeg\\jpeg.pro"
    os.rename( file, "%s.orig" % file )
    sedcommand = r""" "s/libjpeg.lib/-ljpeg/" """
    command = "type %s.orig | sed -e %s > %s" % ( file, sedcommand, file )
    os.system( command ) and die( "qt sed" )
    
    # apply additional compiler support patch
    #os.system( r"qtwin_patch\patch.exe -p1 -i qtwin_patch\msvc_bcc32_42.patch") \
    #	and die ( "installpatch" )
    return True
    
  def compile( self ):
    print "qt compile called"

    os.chdir( os.path.join( self.workdir, "qt-copy" ) )
    
    #os.putenv( "DBUSDIR", os.path.join( self.rootdir, "dbus" ) )

    # only build libs and tools, no examples, no demos
    os.putenv( "QT_PROJECTS", "libs tools" )

    # so that the mkspecs can be found, when -prefix is set
    os.putenv( "QMAKEPATH", os.path.join( self.workdir, "qt-copy" ) )

    win32incdir = os.path.join( self.rootdir, "win32libs", "include" ) \
                  .replace( "\\", "/" )
    win32libdir = os.path.join( self.rootdir, "win32libs", "lib" ) \
                  .replace( "\\", "/" )

    dbusincdir = os.path.join( self.rootdir, "dbus", "include" ) \
                  .replace( "\\", "/" )
    dbuslibdir = os.path.join( self.rootdir, "dbus", "lib" ) \
                  .replace( "\\", "/" )

    # build only the debug version
    #command = r"echo yes | configure.exe -prefix ..\..\image\qt -platform win32-g++" \
    #  " -debug -openssl -I %s -L %s -L %s" % ( win32incdir, win32libdir, win32bindir )

    #command = r"echo yes | configure.exe -prefix ..\..\image\qt -platform win32-g++" \
    #  " -system-jpeg -debug -openssl -I %s -L %s" % ( win32incdir, win32libdir )

    # recommended from README.qt-copy
    #command = r"echo yes | configure.exe -prefix ..\..\image\qt -platform win32-g++ " \
    #  "-qt-gif -no-exceptions -debug -system-zlib -system-libpng -system-libmng " \
    #  "-system-libtiff -system-libjpeg -openssl " \
    #  "-I %s -L %s" % ( win32incdir, win32libdir )


    # shadow build still does not work for me...
    #os.chdir( os.path.join( self.workdir, "qt-build" ) )

    # disable tiff support, does not compile for me...
    prefix = os.path.join( self.rootdir, "qt" ).replace( "\\", "/" )
    command = r"echo yes | ..\qt-copy\configure.exe -prefix %s -platform win32-g++ " \
      "-qt-gif -no-exceptions -debug -qt-libpng " \
      "-system-libjpeg -no-libtiff -openssl " \
      "-I %s -L %s -I %s -L %s" % ( prefix, win32incdir, win32libdir, dbusincdir, dbuslibdir )
    print "command: ", command
    os.system( command ) and die( "qt configure" )

    # argh, this somehow forgets the install prefix...
    # now enable dbus
    #command = r"echo QT_CONFIG += qdbus >> mkspecs\qconfig.pri"
    #print "command: ", command
    #os.system( command )
    #command = "echo QT_INSTALL_PREFIX = %s >> .qmake.cache" % prefix
    #print "command: ", command
    #os.system( command )

    # qmake -recursive, so that dbus will be built too, and so that
    # the Makefiles in tools/qdbus will be created now with the set DBUSDIR
    #os.chdir( os.path.join( self.workdir, "qt-copy", "tools", "qdbus" ) )
    #os.system( "qmake -recursive" ) and die( "qmake -recursive" )

    # build main qt
    os.chdir( os.path.join( self.workdir, "qt-copy" ) )
    os.system( "mingw32-make sub-src sub-tools" )and die( "qt make" )

    # now build qdbus
    #os.chdir( os.path.join( self.workdir, "qt-copy", "tools", "qdbus" ) )
    #os.system( "mingw32-make" )and die( "qdbus make" )
    #os.system( "mingw32-make" )and die( "qt make" )

    # now build qdbus
    #os.chdir( "tools\\qdbus" )
    # set dbus dir...
    #os.system( "..\\..\\bin\\qmake -recursive" ) and die( "dbus qmake" )
    #os.system( "mingw32-make" ) and die( "dbus mingw32-make" )
    # here errors can happen, that seems to be ok...
    #os.system( "mingw32-make install" )
    print "end of qt compile"
    return True

  def install( self ):
    # FIXME create bin/qt.conf, so that qmake -v gives the right path
    print "qt install called"

    os.chdir( os.path.join( self.workdir, "qt-copy" ) )
    install_subtargets = " sub-winmain-install_subtargets-ordered" \
      " sub-moc-install_subtargets-ordered sub-rcc-install_subtargets-ordered" \
      " sub-uic-install_subtargets-ordered sub-corelib-install_subtargets-ordered" \
      " sub-xml-install_subtargets-ordered sub-gui-install_subtargets-ordered" \
      " sub-sql-install_subtargets-ordered sub-network-install_subtargets-ordered " \
      " sub-svg-install_subtargets-ordered sub-script-install_subtargets-ordered" \
      " sub-opengl-install_subtargets-ordered sub-qt3support-install_subtargets-ordered"\
      " sub-uic3-install_subtargets-ordered sub-plugins-install_subtargets-ordered" \
      " sub-tools-install_subtargets-ordered"
    #a = "sub-demos-install_subtargets-ordered" \
    #  " sub-examples-install_subtargets-ordered FORCE"

    #command = "mingw32-make INSTALL_ROOT=%s install_subtargets install_qmake" \
    #          "install_mkspecs" % self.imagedir[2:]
    command = "mingw32-make %s install_qmake install_mkspecs" % install_subtargets
    print "command", command
    os.system( command ) and die( "mingw32-make install..." )

    # install missing windows headers
    list = []
    list.append( [ "src/corelib/arch/qatomic_windows.h", "Qt" ] )
    list.append( [ "src/corelib/global/qt_windows.h", "Qt" ] )
    list.append( [ "src/gui/kernel/qwindowdefs_win.h", "Qt" ] )

    list.append( [ "src/corelib/arch/qatomic_windows.h", "QtCore" ] )
    list.append( [ "src/corelib/global/qt_windows.h", "QtCore" ] )
    list.append( [ "src/gui/kernel/qwindowdefs_win.h", "QtGui" ] )

    for x in list:
      print "from: %s to: %s" % ( x[0], x[1] )
      shutil.copy( os.path.join( self.workdir, "qt-copy", x[ 0 ] ),
                   os.path.join( self.rootdir, "qt", "include", x[ 1 ] ) )

    return True

subclass().execute()
