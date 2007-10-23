import base
import os
import shutil
import re
import utils
from utils import die

PACKAGE_NAME         = "openbabel"
PACKAGE_VER          = "2.1.1"
PACKAGE_FULL_VER     = "2.1.1"
PACKAGE_FULL_NAME    = "%s-%s" % ( PACKAGE_NAME, PACKAGE_VER )

SRC_URI= """
http://heanet.dl.sourceforge.net/sourceforge/openbabel/""" + PACKAGE_FULL_NAME + """.tar.gz
"""

DEPEND = """
"""

#
# this library is used by kdeedu/kalzium
# thanks to the people from Molekel (http://bioinformatics.org/molekel/wiki/Main/OpenBabel)
# for making most of it working and providing current instructions
#

class subclass(base.baseclass):
    def __init__(self):
        base.baseclass.__init__( self, SRC_URI )
        self.instsrcdir = PACKAGE_FULL_NAME
        self.createCombinedPackage = True

    def execute( self ):
        base.baseclass.execute( self )
        if self.compiler <> "mingw":
            print "error: can only be build with MinGW ."
            exit( 1 )

    def unpack( self ):
        if( not base.baseclass.unpack( self ) ):
            return False
            
        src = os.path.join( self.workdir, self.instsrcdir )

        cmd = "cd %s && patch -p0 < %s" % \
              ( os.path.join( self.workdir, self.instsrcdir, "src" ), os.path.join( self.packagedir , "src.Makefile.in.diff" ) )
        if not self.stayQuiet:
            print cmd
        os.system( cmd ) or die
        cmd = "cd %s && patch -p0 < %s" % \
              ( os.path.join( self.workdir, self.instsrcdir, "src" ), os.path.join( self.packagedir , "src.config.h.in.diff" ) )
        if not self.stayQuiet:
            print cmd
        os.system( cmd ) or die
        cmd = "cd %s && patch -p0 < %s" % \
              ( os.path.join( self.workdir, self.instsrcdir, "include", "openbabel" ), os.path.join( self.packagedir , "include.openbabel.obmolecformat.h.diff" ) )
        if not self.stayQuiet:
            print cmd
        os.system( cmd ) or die
        cmd = "cd %s && patch -p0 < %s" % \
              ( os.path.join( self.workdir, self.instsrcdir, "tools" ), os.path.join( self.packagedir , "tools.Makefile.in.diff" ) )
        if not self.stayQuiet:
            print cmd
        os.system( cmd ) or die
        cmd = "cd %s && patch -p0 < %s" % \
              ( os.path.join( self.workdir, self.instsrcdir, "tools" ), os.path.join( self.packagedir , "tools.babel.cpp.diff" ) )
        if not self.stayQuiet:
            print cmd
        os.system( cmd ) or die
        
        return True

    def msysConfigureFlags ( self ):
        flags = "--prefix=/ "
        flags += "--with-zlib=" + utils.toMSysPath( self.rootdir ) + " "
        flags += "CPPFLAGS=\"-I" + utils.toMSysPath( os.path.join( self.workdir, self.instsrcdir, "data" ) ) + "\" "
        return flags

    def compile( self ):
        return self.msysCompile()

    def install( self ):
        return self.msysInstall()

    def make_package( self ):
        # now do packaging with kdewin-packager
        self.doPackaging( PACKAGE_NAME, PACKAGE_FULL_VER, True )

        return True

subclass().execute()
