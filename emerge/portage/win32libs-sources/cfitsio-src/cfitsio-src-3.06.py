import base
import os
import shutil
import re
import utils
from utils import die

PACKAGE_NAME         = "cfitsio"
PACKAGE_VER          = "3.06"
PACKAGE_FULL_VER     = "3060"
PACKAGE_FULL_NAME    = "%s-%s" % ( PACKAGE_NAME, PACKAGE_FULL_VER )

SRC_URI= """
ftp://heasarc.gsfc.nasa.gov/software/fitsio/c/""" + PACKAGE_NAME + PACKAGE_FULL_VER + """.tar.gz
"""

DEPEND = """
"""

#
# this library is used by kdeedu/kstars
# the library is c-only but it may not work due to __stdcall - we'll see
# it should be no problem to compile it with msvc and/or create a CMakeLists.txt
# to fix this problem if there's one
#

class subclass(base.baseclass):
    def __init__(self):
        base.baseclass.__init__( self, SRC_URI )
        self.instsrcdir = PACKAGE_NAME
        self.createCombinedPackage = True

    def execute( self ):
        base.baseclass.execute( self )
        if self.compiler <> "mingw":
            print "error: can only be build with MinGW right now."
            exit( 1 )

    def unpack( self ):
        if( not base.baseclass.unpack( self ) ):
            return False
            
        src = os.path.join( self.workdir, self.instsrcdir )

        cmd = "cd %s && patch -p0 < %s" % \
              ( os.path.join( self.workdir, self.instsrcdir ), os.path.join( self.packagedir , "configure.diff" ) )
        if not self.stayQuiet:
            print cmd
        os.system( cmd ) or die

        cmd = "cd %s && patch -p0 < %s" % \
              ( os.path.join( self.workdir, self.instsrcdir ), os.path.join( self.packagedir , "Makefile.in.diff" ) )
        if not self.stayQuiet:
            print cmd
        os.system( cmd ) or die
        
        return True

    def msysConfigureFlags ( self ):
        flags = "--prefix=/ "
        return flags

    def compile( self ):
        return self.msysCompile( False )

    def install( self ):
        return self.msysInstall( False )

    def make_package( self ):
        dst = os.path.join( self.imagedir, self.instdestdir, "lib" )
        utils.cleanDirectory( dst )

        self.stripLibs( "libcfitsio" )
        self.createImportLibs( "libcfitsio" )
        # now do packaging with kdewin-packager
        self.doPackaging( PACKAGE_NAME, PACKAGE_FULL_VER, True )

        return True

subclass().execute()
