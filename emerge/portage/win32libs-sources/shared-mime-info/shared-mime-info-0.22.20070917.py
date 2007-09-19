import base
import os
import shutil
import utils
import re
from utils import die

PACKAGE_NAME         = "shared-mime-info"
PACKAGE_VER          = "0.22"
PACKAGE_FULL_VER     = "0.22"
PACKAGE_FULL_NAME    = "%s-%s" % ( PACKAGE_NAME, PACKAGE_VER )

SRC_URI= """
http://freedesktop.org/~hadess/""" + PACKAGE_FULL_NAME + """.tar.bz2
ftp://ftp.gtk.org/pub/glib/2.14/glib-2.14.1.tar.bz2
"""

# deps: libxml2, libintl, iconv
# source-deps: glib (yeah!) and kdewin32
DEPEND = """
dev-util/win32libs
"""

class subclass(base.baseclass):
  def __init__(self):
    base.baseclass.__init__( self, SRC_URI )
    self.instsrcdir = PACKAGE_FULL_NAME
    self.createCombinedPackage = False

  def unpack( self ):
    if(not base.baseclass.unpack( self ) ):
      return False;
    
    # rename config.h and glibconfig.h.win32 in glib to 
    # avoid config.h confusion
    p = re.compile('.*\.[ch]$')
    glibdir = os.path.join( self.workdir, "glib-2.14.1" )
    sedcmd = r"""-e "s/config.h/config.h.win32/" """
    dir = os.path.join( glibdir, "glib" )
    if ( os.path.exists( dir ) ):
        for root, dirs, files in os.walk( dir, topdown=False ):
            print root
            for name in files:
                if( p.match( name ) ):
                    utils.sedFile( root, name, sedcmd )

    return True
    return self.kdeSvnUnpack( "trunk/kdesupport", "kdewin32")

  def kdeDefaultDefines( self ):
    # adjust some vars for proper compile
    cmake_src  = os.path.join( self.workdir, self.instsrcdir )
    cmake_dest = os.path.join( self.imagedir, self.instdestdir )

    options = "%s -DCMAKE_INSTALL_PREFIX=%s " % \
              ( cmake_src, cmake_dest.replace( '\\', '/' ) )

    options = options + "-DKDEWIN32_DIR=%s " % \
              os.path.join( self.workdir, "kdewin32" ).replace( "\\", "/" )

    options = options + "-DGLIB_DIR=%s " % \
              os.path.join( self.workdir, "glib-2.14.1" ).replace( "\\", "/" )

    options = options + "-DCMAKE_INCLUDE_PATH=%s " % \
              os.path.join( self.rootdir, "win32libs", "include" ).replace( "\\", "/" )

    options = options + "-DCMAKE_LIBRARY_PATH=%s " % \
              os.path.join( self.rootdir, "win32libs", "lib" ).replace( "\\", "/" )

    options = options + "-DCMAKE_BUILD_TYPE=Release "

    return options

  def compile( self ):

    # we have an own cmake script - copy it to the right place
    src = os.path.join( self.packagedir , "CMakeLists.txt" )
    dst = os.path.join( self.workdir, self.instsrcdir, "CMakeLists.txt" )
    shutil.copy( src, dst )

    src = os.path.join( self.packagedir , "config.h.cmake" )
    dst = os.path.join( self.workdir, self.instsrcdir, "config.h.cmake" )
    shutil.copy( src, dst )

    return self.kdeCompile()

  def install( self ):
    os.chdir( os.path.join( self.workdir, "%s-build" % self.package ) )
    os.system( "mingw32-make install" ) and die( "mingw32-make install" )
    cmd = os.path.join( self.imagedir, self.instdestdir, "bin", "update-mime-database.exe" )
    cmd = cmd + os.path.join( self.imagedir, "share", "mime" )
    os.system( cmd )
    return True

  def make_package( self ):
    # auto-create both import libs with the help of pexports
    cmd = "strip -s %s" % \
          os.path.join(self.imagedir, self.instdestdir, "bin", "update-mime-database.exe" )
    os.system( cmd ) and die ( cmd )

    # now do packaging with kdewin-packager
    self.doPackaging( PACKAGE_NAME, PACKAGE_FULL_VER, True )

    return True
  
subclass().execute()
