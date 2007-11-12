import base
import os
import utils
import shutil

PACKAGE_NAME         = "fontconfig"
PACKAGE_VER          = "2.4.2"
PACKAGE_FULL_VER     = "2.4.2-1"
PACKAGE_FULL_NAME    = "%s-%s" % ( PACKAGE_NAME, PACKAGE_VER )
PACKAGE_DLL_NAME     = "libfontconfig"

SRC_URI= """
http://fontconfig.org/release/""" + PACKAGE_FULL_NAME + """.tar.gz
"""

DEPEND = """
dev-util/win32libs
testing/freetype-src
"""

class subclass(base.baseclass):
    def __init__(self):
        base.baseclass.__init__( self, SRC_URI )
        self.instsrcdir = PACKAGE_FULL_NAME
        self.createCombinedPackage = True

    def execute( self ):
        base.baseclass.execute( self )
        if self.compiler <> "mingw":
            print "error: can only be build with MinGW right now."
            exit( 1 )

    def unpack( self ):
        if( not base.baseclass.unpack( self ) ):
            return False
        shutil.copyfile( os.path.join( self.packagedir, "pkg-config" ), os.path.join( self.workdir, self.instsrcdir, "pkg-config" ) )
        return True

    def msysConfigureFlags ( self ):
        includedir = os.path.join( self.rootdir, "include" )
        libdir = os.path.join( self.rootdir, "lib" )
        flags = "--enable-libxml2 LIBXML2_CFLAGS=-I" + utils.toMSysPath( includedir ) + " LIBXML2_LIBS='-L" + utils.toMSysPath( libdir ) + " -lxml2' --prefix=/ "
        return flags

    def compile( self ):
        config = os.path.join( self.workdir, self.instsrcdir, "configure" )
        build  = os.path.join( self.workdir, self.instsrcdir )

        sh = os.path.join( self.msysdir, "bin", "sh.exe" )

        cmd = "%s --login -c \"cd %s && %s %s && make -j2\"" % \
              ( sh, utils.toMSysPath( build ), utils.toMSysPath( config ), \
                self.msysConfigureFlags() )
        if not self.stayQuiet:
            print cmd
        self.system( cmd )
        return True

    def install( self ):
        return self.msysInstall( False )

    def make_package( self ):
        dst = os.path.join( self.imagedir, self.instdestdir, "lib" )
        utils.cleanDirectory( dst )

        self.stripLibs( "libfontconfig" )
        self.createImportLibs( "libfontconfig" )
        # now do packaging with kdewin-packager
        # it's a in-source build, do not pack sources
        self.doPackaging( PACKAGE_NAME, PACKAGE_FULL_VER, False )

        return True

subclass().execute()
