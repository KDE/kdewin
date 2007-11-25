import base
import os
import shutil
import re
import utils
from utils import die

PACKAGE_NAME         = "boost"
PACKAGE_VER          = "1_34"
PACKAGE_FULL_VER     = "1_34_1"
PACKAGE_FULL_NAME    = "%s_%s" % ( PACKAGE_NAME, PACKAGE_FULL_VER)

SRC_URI= """
http://downloads.sourceforge.net/boost/""" + PACKAGE_FULL_NAME + """.tar.bz2
"""

DEPEND = """
dev-util/bjam
"""

# #########################################################################################
# ATTENTION: currently the only libraries that are built are boost.python libs
# that implies that the bin package requires the lib package as well to be used for compilation
# #########################################################################################

class subclass(base.baseclass):
    def __init__(self):
        base.baseclass.__init__( self, SRC_URI )
        self.instsrcdir = PACKAGE_FULL_NAME
        self.createCombinedPackage = True
        if self.compiler == "mingw":
            self.toolset = "gcc"
        else:
            self.toolset = "msvc"

    def execute( self ):
        base.baseclass.execute( self )

    def compile( self ):
        """"""
        cmd = "cd %s && bjam --toolset=%s --prefix=%s --with-python --layout=system" % ( os.path.join( self.workdir, self.instsrcdir ),
        self.toolset, os.path.join( self.workdir, self.imagedir ))
        if utils.verbose() >= 1:
            print cmd
        os.system( cmd ) and die( "compile failed because of this cobbled stuff: %s" % ( cmd ) )
        return True

    def install( self ):
        """"""
        cmd = "cd %s && bjam --toolset=%s --prefix=%s --with-python --layout=system install" % ( os.path.join( self.workdir, self.instsrcdir ),
        self.toolset, os.path.join( self.workdir, self.imagedir ))
        if utils.verbose() >= 1:
            print cmd
        os.system( cmd ) and die( "compile failed because of this cobbled stuff: %s" % ( cmd ) )

        # add another boost include dir boost-1_34
        srcdir  = os.path.join( self.workdir, self.imagedir, "include", "boost" )
        destdir = os.path.join( self.workdir, self.imagedir, "include", PACKAGE_NAME + "-" + PACKAGE_FULL_VER, "boost" )
        utils.copySrcDirToDestDir( srcdir, destdir )

        # add another boost include dir boost-1_34_1
        srcdir  = os.path.join( self.workdir, self.imagedir, "include", "boost" )
        destdir = os.path.join( self.workdir, self.imagedir, "include", PACKAGE_NAME + "-" + PACKAGE_VER, "boost" )
        utils.copySrcDirToDestDir( srcdir, destdir )
        
        # copy runtime libraries to the bin folder
        cmd = "cd %s && mkdir bin && copy lib\\*.dll bin" % ( os.path.join( self.workdir, self.imagedir ) )
        if utils.verbose() >= 1:
            print cmd
        os.system( cmd ) and die( "compile failed because of this cobbled stuff: %s" % ( cmd ) )
        return True

    def make_package( self ):
        return self.doPackaging( PACKAGE_NAME, PACKAGE_FULL_VER, True )

subclass().execute()
