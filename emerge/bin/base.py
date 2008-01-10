# this package contains the base class for all packages

# copyright:
# Holger Schroeder <holger [AT] holgis [DOT] net>
# Patrick Spendrin <ps_ml [AT] gmx [DOT] de>

import sys
import os

import shutil

# for get functions etc...
import utils
# for the msys interface
import msys_build
#from utils import die

ROOTDIR=os.getenv( "KDEROOT" )
COMPILER=os.getenv( "KDECOMPILER" )
DOWNLOADDIR=os.getenv( "DOWNLOADDIR" )
if ( DOWNLOADDIR == None ):
    DOWNLOADDIR=os.path.join( ROOTDIR, "distfiles" )

KDESVNDIR=os.getenv( "KDESVNDIR" )
if ( KDESVNDIR == None ):
    KDESVNDIR=os.path.join( DOWNLOADDIR, "svn-src", "kde" )
KDESVNSERVER=os.getenv( "KDESVNSERVER" )
if ( KDESVNSERVER == None ):
    KDESVNSERVER="svn://anonsvn.kde.org"
KDESVNUSERNAME=os.getenv( "KDESVNUSERNAME" )
KDESVNPASSWORD=os.getenv( "KDESVNPASSWORD" )

DIRECTORYLAYOUT=os.getenv( "directory_layout" )
if ( not DIRECTORYLAYOUT == "installer" ):
    """ traditional layout is using the categories as subfolders of kderoot """
    """ installer layout has no category subfolder """
    DIRECTORYLAYOUT = "traditional"

# ok, we have the following dirs:
# ROOTDIR: the root where all this is below
# DOWNLOADDIR: the dir under rootdir, where the downloaded files are put into
# WORKDIR: the directory, under which the files are unpacked and compiled.
#            here rootdir/tmp/packagename/work
# IMAGEDIR: the directory, under which the compiled files are installed.
#            here rootdir/tmp/packagename/image


class baseclass:
# methods of baseclass:
# __init__                   the baseclass constructor
# execute                    called to run the derived class
# fetch                      getting the package
# unpack                     unpacking the source tarball
# compile                    compiling the tarball
# install                    installing the files into the normal
# qmerge                     mergeing the local directory to the kderoot
# unmerge                    unmergeing the local directory again
# manifest                   getting the headers
# make_package               overload this function to make the packages themselves
# setDirectories
# svnFetch                  getting sources from a custom repo url
# __kdesinglecheckout
# kdeSvnFetch
# kdeSvnUnpack
# kdeDefaultDefines
# kdeConfigureInternal
# kdeMakeInternal
# kdeCompile                 running for compilation from cmake
# kdeInstallInternal
# kdeInstall                 running for installation from cmake
# doPackaging                
# createImportLibs           creating import libs for mingw and msvc
# stripLibs                  stripping libs
# msysConfigureFlags         called by msysCompile: overload it to set 
# msysCompile                running the msys sh and compiling autotool based stuff
# msysInstall                install from msys sh
# system                     instead of using the os.system command, please use this one - it makes later changes easier


    def __init__( self, SRC_URI ):
        """ the baseclass constructor """
        self.SRC_URI                = SRC_URI
        self.instsrcdir             = ""
        self.instdestdir            = ""
        self.traditional            = True
        self.noCopy                 = False
        self.buildTests             = False
        self.forced                 = False
        self.versioned              = False
        self.noFetch                = False
        self.kdeCustomDefines       = ""
        self.createCombinedPackage  = False

        self.msys = msys_interface()
        
        if os.getenv( "EMERGE_OFFLINE" ) == "True":
            self.noFetch = True
        if os.getenv( "EMERGE_NOCOPY" ) == "True":
            self.noCopy = True
        if os.getenv( "EMERGE_BUILDTESTS" ) == "True":
            self.buildTests = True
        if DIRECTORYLAYOUT == "installer":
            self.traditional = False

        # Build type for kdeCompile() / kdeInstall() - packages
        # "" -> debug and release
        Type=os.getenv( "EMERGE_BUILDTYPE" )
        if ( not Type == None ):
            if utils.verbose() > 1:
                print "BuildType: %s" % Type
            self.buildType = Type
        else:
            self.buildType = None

        if COMPILER == "msvc2005":
            self.compiler = "msvc2005"
        elif COMPILER == "mingw":
            self.compiler = "mingw"
        else:
            print "emerge error: KDECOMPILER: %s not understood" % COMPILER
            exit( 1 )

    def execute( self ):
        """called to run the derived class"""
        """this will be executed from the package if the package is started on its own"""
        """it shouldn't be called if the package is imported as a python module"""
        if utils.verbose() > 1:
            print "base exec called. args:", sys.argv

        command = sys.argv[ 1 ]
        options = ""
        if ( len( sys.argv )  > 2 ):
            options = sys.argv[ 2: ]
        self.noFetch = False
        if ( "--offline" in options ):
            self.noFetch  = True
        if ( "--forced" in options ):
            self.forced = True
        if ( "--versioned" in options ):
            self.versioned = True
        if utils.verbose() > 1:
            print "command:", command
            print "opts:", options

        self.setDirectories()

        ok = True
        if command == "fetch":          ok = self.fetch()
        elif command == "cleanimage":   self.cleanup()
        elif command == "unpack":   ok = self.unpack()
        elif command == "compile":  ok = self.compile()
        elif command == "configure":  ok = self.compile()
        elif command == "make":  ok = self.compile()
        elif command == "install": ok = self.install()
        elif command == "qmerge":   ok = self.qmerge()
        elif command == "unmerge":   ok = self.unmerge()
        elif command == "manifest":   ok = self.manifest()
        elif command == "package":  ok = self.make_package()
        else:
            ok = utils.error( "command %s not understood" % command )

        if ( not ok ):
            utils.die( "command %s failed" % command )

    def cleanup( self ):
        """cleanup before install to imagedir"""
        if ( os.path.exists( self.imagedir ) ):
            if not utils.verbose() > 1:
                print "cleaning image dir:", self.imagedir
            utils.cleanDirectory( self.imagedir )
    
    def fetch( self ):
        """getting normal tarballs from SRC_URI"""
        if utils.verbose() > 1:
            print "base fetch called"
        if ( self.noFetch ):
            if utils.verbose() > 0:
                print "skipping fetch (--offline)"
            return True
        
        return utils.getFiles( self.SRC_URI, self.downloaddir )

    def unpack( self ):
        """unpacking all zipped(gz,zip,bz2) tarballs"""
        if utils.verbose() > 1:
            print "base unpack called, files:", self.filenames
        return utils.unpackFiles( self.downloaddir, self.filenames, self.workdir )

    def compile( self ):
        """overload this function according to the packages needs"""
        if utils.verbose() > 1:
            print "base compile called, doing nothing..."
        return True

    def install( self ):
        """installing binary tarballs"""
        if utils.verbose() > 1:
            print "base install called"
        srcdir = os.path.join( self.workdir, self.instsrcdir )
        destdir = os.path.join( self.imagedir, self.instdestdir )
        utils.copySrcDirToDestDir( srcdir, destdir )
        return True

    def qmerge( self ):
        """mergeing the imagedirectory into the filesystem"""
        if utils.verbose() > 1:
            print "base qmerge called"
        utils.mergeImageDirToRootDir( self.imagedir, self.rootdir )
        utils.addInstalled( self.category, self.package, self.version )
        return True

    def unmerge( self ):
        """unmergeing the files from the filesystem"""
        if utils.verbose() > 1:
            print "base unmerge called"
        utils.unmerge( self.rootdir, self.package, self.forced )
        utils.remInstalled( self.category, self.package, self.version )
        return True
        
    def manifest( self ):
        """installer compatibility: make the manifest files that make up the installers"""
        """install database"""
        if utils.verbose() > 1:
            print "base manifest called"
        utils.manifestDir( os.path.join( self.workdir, self.instsrcdir, self.package ), self.imagedir, self.package, self.version )
        return True
        
    def make_package( self ):
        """overload this function with the package specific packaging instructions"""
        if utils.verbose() > 1:
            print "currently only supported for some interal packages"
        return True

    def setDirectories( self ):
        """setting all important stuff that isn't coped with in the c'tor"""
        """parts will probably go to infoclass"""
        if utils.verbose() > 1:
            print "setdirectories called"
        #print "basename:", sys.argv[ 0 ]
        #print "src_uri", self.SRC_URI

        filenames = []
        for uri in self.SRC_URI.split():
            filenames.append( os.path.basename( uri ) )
        self.filenames = filenames
        #print "filenames:", self.filenames

        #( self.progname, ext ) = os.path.splitext( os.path.basename( sys.argv[ 0 ] ) )
        ( self.PV, ext ) = os.path.splitext( os.path.basename( sys.argv[ 0 ] ) )
        #print "progname:", self.progname        

        ( self.category, self.package, self.version ) = \
                       utils.getCategoryPackageVersion( sys.argv[ 0 ] )

        #self.progname = self.package        
        if utils.verbose() > 0:
            print "setdir category: %s, package: %s, version: %s" %\
              ( self.category, self.package, self.version )

        self.cmakeInstallPrefix = ROOTDIR.replace( "\\", "/" )
        if utils.verbose() > 0:
            print "cmakeInstallPrefix:", self.cmakeInstallPrefix

        if COMPILER == "msvc2005":
            self.cmakeMakefileGenerator = "NMake Makefiles"
            self.cmakeMakeProgramm = "nmake"
        elif COMPILER == "mingw":
            self.cmakeMakefileGenerator = "MinGW Makefiles"
            self.cmakeMakeProgramm = "mingw32-make"
        else:
            utils.die( "KDECOMPILER: %s not understood" % COMPILER )

        self.rootdir     = ROOTDIR
        self.downloaddir = DOWNLOADDIR
        self.workdir     = os.path.join( ROOTDIR, "tmp", self.PV, "work" )
        self.imagedir    = os.path.join( ROOTDIR, "tmp", self.PV, "image-" + COMPILER )

        self.packagedir = os.path.join( ROOTDIR, "emerge", "portage", self.category, self.package )
        self.filesdir = os.path.join( self.packagedir, "files" )
        self.kdesvndir = KDESVNDIR
        self.kdesvnserver = KDESVNSERVER
        self.kdesvnuser = KDESVNUSERNAME
        self.kdesvnpass = KDESVNPASSWORD
        
        self.strigidir = os.getenv( "STRIGI_HOME" )
        self.dbusdir = os.getenv( "DBUSDIR" )

        self.msys.setDirectories( [ self.imagedir, self.workdir, self.instsrcdir, self.instdestdir ] )

    def svnFetch( self, repo ):
        """getting sources from a custom svn repo"""
        if utils.verbose() > 1:
            print "base svnFetch called"
        self.svndir = os.path.join( self.downloaddir, "svn-src", self.package )
        if ( self.noFetch ):
            if utils.verbose() > 0:
                print "skipping svn fetch/update (--offline)"
            return True
        
        utils.svnFetch( repo, self.svndir )

    def __kdesinglecheckout( self, repourl, ownpath, codir, doRecursive = False ):
        """in ownpath try to checkout codir from repourl """
        """if codir exists and doRecursive is false, simply return,"""
        """if codir does not exist, but ownpath/.svn exists,"""
        """   do a svn update codir"""
        """else do svn co repourl/codir"""
        """if doRecursive is false, add -N to the svn command """

        if ( os.path.exists( os.path.join( ownpath, codir ) ) \
                             and not doRecursive ):
            if utils.verbose() > 0:
                print "ksco exists:", ownpath, codir
            return

        if ( doRecursive ):
                recFlag = ""
        else:
                recFlag = "-N"

        if ( os.path.exists( os.path.join( ownpath, ".svn" ) ) ):
            # svn up
            svncmd = "svn update %s %s" % ( recFlag, codir)
        else:
            #svn co
            svncmd = "svn checkout %s %s" % \
                     ( recFlag, repourl + codir )

        if utils.verbose() > 1:
            print "kdesinglecheckout:pwd ", ownpath
            print "kdesinglecheckout:   ", svncmd
        os.chdir( ownpath )
        self.system( svncmd )
                
    def kdeSvnFetch( self, svnpath, packagedir ):
        """svnpath is the part of the repo url after /home/kde, for example"""
        """"trunk/kdesupport/", which leads to the package itself,"""
        """without the package"""
        
        if utils.verbose() > 1:
            print "base kdeSvnFetch called. svnpath: %s dir: %s" % ( svnpath, packagedir )

        if ( self.noFetch ):
            if utils.verbose() > 0:
                print "skipping svn fetch/update (--offline)"
            return True
        
        mydir = self.kdesvndir
        if ( not os.path.exists( mydir ) ):
                os.mkdir( mydir )

        repourl = self.kdesvnserver + "/home/kde/"

        for tmpdir in svnpath.split( "/" ):
            if ( tmpdir == "" ):
                    continue
            if utils.verbose() > 1:
                print "  mydir: %s" % mydir
                print "  dir to checkout: %s" % tmpdir
                print "  repourl", repourl

            self.__kdesinglecheckout( repourl, mydir, tmpdir, False )
            mydir = os.path.join( mydir, tmpdir )
            repourl = repourl + tmpdir + "/"
                
        if utils.verbose() > 0:
            print "dir in which to really checkout: %s" % mydir
            print "dir to really checkout: %s" % packagedir
        self.__kdesinglecheckout( repourl, mydir, packagedir, True )

        svndir = os.path.join( self.kdesvndir, svnpath ).replace( "/", "\\" )
        #repo = self.kdesvnserver + "/home/kde/" + svnpath + dir
        #utils.svnFetch( repo, svndir, self.kdesvnuser, self.kdesvnpass )
        if utils.verbose() > 1:
            print "kdesvndir", self.kdesvndir
            print "svndir", svndir
        self.svndir = os.path.join( svndir, packagedir )
        
        return True

    def kdeSvnPath( self ):
        """overload this function in kde packages to use the nocopy option"""
        """this function should return the full path seen from /home/KDE/"""
        return False
        
    def kdeSvnUnpack( self, svnpath=None, packagedir=None ):
        """fetching and copying the sources from svn"""
        if svnpath == None and packagedir == None:
            if self.kdeSvnPath():
                svnpath = self.kdeSvnPath()[ :self.kdeSvnPath().rfind('/') ]
                packagedir = self.kdeSvnPath()[ self.kdeSvnPath().rfind('/') + 1:]
            else:
                utils.die( "no svn repository information are available" )
        self.kdeSvnFetch( svnpath, packagedir )
        
        if( not os.path.exists( self.workdir ) ):
            os.makedirs( self.workdir )
            
        if not ( self.noCopy and self.kdeSvnPath() ):
            # now copy the tree to workdir
            srcdir  = os.path.join( self.kdesvndir, svnpath, packagedir )
            destdir = os.path.join( self.workdir, packagedir )
            utils.copySrcDirToDestDir( srcdir, destdir )
        return True
        
    def kdeDefaultDefines( self ):
        """defining the default cmake cmd line"""
        #FIXME: can we define the paths externally???
        if utils.verbose() > 1 and self.kdeSvnPath():
            print "noCopy: %s" % self.noCopy
            print "kdeSvnPath(): %s" % self.kdeSvnPath().replace("/", "\\")
        if not ( self.noCopy and self.kdeSvnPath() ) :
            source_path = "..\\%s" % self.instsrcdir
        else:
            source_path = "%s" % os.path.join(self.kdesvndir, self.kdeSvnPath() ).replace("/", "\\")
#        if( not self.instsrcdir == "" ):
#            source_path = self.instsrcdir
        print "source_path: ", source_path
        if self.traditional:
            options = "%s -DCMAKE_INSTALL_PREFIX=%s/kde " % \
                  ( source_path, self.rootdir.replace( "\\", "/" ) )

            options = options + "-DCMAKE_INCLUDE_PATH=%s;%s " % \
                    ( os.path.join( self.rootdir, "win32libs", "include" ).replace( "\\", "/" ), \
                      os.path.join( self.rootdir, "kde", "include" ).replace( "\\", "/" ) \
                    )

            options = options + "-DCMAKE_LIBRARY_PATH=%s;%s " % \
                    ( os.path.join( self.rootdir, "win32libs", "lib" ).replace( "\\", "/" ), \
                      os.path.join( self.rootdir, "kde", "lib" ).replace( "\\", "/" ) \
                    )
        else:
            options = "%s -DCMAKE_INSTALL_PREFIX=%s " % \
                  ( source_path, self.rootdir.replace( "\\", "/" ) )
            
            options = options + "-DCMAKE_INCLUDE_PATH=%s " % \
                    os.path.join( self.rootdir, "include" ).replace( "\\", "/" )
            
            options = options + "-DCMAKE_LIBRARY_PATH=%s " % \
                    os.path.join( self.rootdir, "lib" ).replace( "\\", "/" )

        if self.buildTests:
            options = options + " -DKDE4_BUILD_TESTS=1"

        options = options + "-DKDEWIN_DIR:PATH=%s" % \
               os.path.join( self.rootdir ).replace( "\\", "/" )
        
        return options

    def kdeConfigureInternal( self, buildType ):
        """Using cmake"""
        builddir = "%s" % ( self.compiler )

        if( not buildType == None ):
            buildtype = "-DCMAKE_BUILD_TYPE=%s" % buildType
            builddir = "%s-%s" % ( builddir, buildType )
    
        os.chdir( self.workdir )
        utils.cleanDirectory( builddir )
        os.chdir( builddir )

        command = r"""cmake -G "%s" %s %s %s""" % \
              ( self.cmakeMakefileGenerator, \
                self.kdeDefaultDefines(), \
                self.kdeCustomDefines, \
                buildtype )

        if utils.verbose() > 0:
            print "configuration command: %s" % command
        self.system( command )
        return True

    def kdeMakeInternal( self, buildType ):
        """Using the *make program"""
        builddir = "%s" % ( self.compiler )

        if( not buildType == None ):
            buildtype = "-DCMAKE_BUILD_TYPE=%s" % buildType
            builddir = "%s-%s" % ( builddir, buildType )
    
        os.chdir( os.path.join( self.workdir, builddir ) )
        cmd = self.cmakeMakeProgramm
        # adding Targets later
        if utils.verbose() > 1:
            cmd += " VERBOSE=1"
        self.system( cmd )
        return True
    
    def kdeCompile( self ):
        """making all required stuff for compiling cmake based modules"""
        if( not self.buildType == None ) :
            if( not ( self.kdeConfigureInternal( self.buildType ) and self.kdeMakeInternal( self.buildType ) ) ):
                return False
        else:
            if( not ( self.kdeConfigureInternal( "Debug" ) and self.kdeMakeInternal( "Debug" ) ) ):
                return False
            if( not ( self.kdeConfigureInternal( "Release" ) and self.kdeMakeInternal( "Release" ) ) ):
                return False
        return True

    def kdeInstallInternal( self, buildType ):
        """"""
        builddir = "%s" % ( self.compiler )

        if( not buildType == None ):
            builddir = "%s-%s" % ( builddir, buildType )

        os.chdir( self.workdir )
        os.chdir( builddir )
        if utils.verbose() > 0:
            print "builddir: " + builddir

        self.system( "%s DESTDIR=%s install" % \
                   ( self.cmakeMakeProgramm , self.imagedir ) )
        return True

    def kdeInstall( self ):
        """making all required stuff for installing cmake based modules"""
        if( not self.buildType == None ):
            if( not self.kdeInstallInternal( self.buildType ) ):
                return False
        else:
            if( not self.kdeInstallInternal( "debug" ) ):
                return False
            if( not self.kdeInstallInternal( "release" ) ):
                return False
        utils.fixCmakeImageDir( self.imagedir, self.rootdir )
        return True

    def doPackaging( self, pkg_name, pkg_version, packSources = True ):
        """packaging according to the gnuwin32 packaging rules"""
        """this requires the kdewin-packager"""
        
        # FIXME: add a test for the installer later
        dstpath = os.path.join( self.rootdir, "tmp", self.PV )
        binpath = os.path.join( self.imagedir, self.instdestdir )
        tmp = os.path.join( binpath, "kde" )

        if( os.path.exists( tmp ) ):
            binpath = tmp

        if ( packSources and not ( self.noCopy and self.kdeSvnPath() ) ):
            srcpath = os.path.join( self.workdir, self.instsrcdir )
            cmd = "-name %s -root %s -srcroot %s -version %s -destdir %s" % \
                  ( pkg_name, binpath, srcpath, pkg_version, dstpath )
        elif self.noCopy and self.kdeSvnPath():
            srcpath = os.path.join(self.kdesvndir, self.kdeSvnPath() ).replace("/", "\\")
            cmd = "-name %s -root %s -srcroot %s -version %s -destdir %s" % \
                  ( pkg_name, binpath, srcpath, pkg_version, dstpath )
        else:
            cmd = "-name %s -root %s -version %s -destdir %s" % \
                  ( pkg_name, binpath, pkg_version, dstpath )
        cmd = "kdewin-packager.exe -debuglibs " + cmd + " -complete -compression 2 "

        if( not self.createCombinedPackage ):
            if( self.compiler == "mingw"):
              cmd = cmd + " -type mingw "
            else:
              cmd = cmd + " -type msvc "

        self.system( cmd )
        return True

    def createImportLibs( self, pkg_name ):
        """creating the import libraries for the other compiler(if ANSI-C libs)"""
        basepath = os.path.join( self.imagedir, self.instdestdir )

        dst = os.path.join( basepath, "lib" )
        if( not os.path.exists( dst ) ):
            os.mkdir( dst )

        dllpath = os.path.join( basepath, "bin", "%s.dll" % pkg_name )
        defpath = os.path.join( basepath, "lib", "%s.def" % pkg_name )
        imppath = os.path.join( basepath, "lib", "%s.lib" % pkg_name )
        gccpath = os.path.join( basepath, "lib", "%s.dll.a" % pkg_name )

        # create .def
        cmd = "pexports %s > %s " % ( dllpath, defpath )
        self.system( cmd )

        if( not os.path.isfile( imppath ) ):
            # create .lib
            cmd = "lib /machine:x86 /def:%s /out:%s" % ( defpath, imppath )
            self.system( cmd )
        
        if( not os.path.isfile( gccpath ) ):
            # create .dll.a
            cmd = "dlltool -d %s -l %s" % ( defpath, gccpath )
            self.system( cmd )
        return True

    def stripLibs( self, pkg_name ):
        """stripping libraries"""
        basepath = os.path.join( self.imagedir, self.instdestdir )
        dllpath = os.path.join( basepath, "bin", "%s.dll" % pkg_name )

        cmd = "strip -s " + dllpath
        self.system( cmd )
        return True

    def msysConfigureFlags( self ):
        """adding configure flags always used"""
        return self.msys.msysConfigureFlags()

    def msysCompile( self, bOutOfSource = True ):
        """run configure and make for Autotools based stuff"""
        return self.msys.msysCompile( bOutOfSource )

    def msysInstall( self, bOutOfSource = True ):
        """run make install for Autotools based stuff"""
        return self.msys.msysInstall( bOutOfSource )

    def system( self, command , infileName = None, outfileName = os.path.join( ROOTDIR, "out.log" ), errfileName = os.path.join( ROOTDIR, "out.log" ) ):
        """this function should be called instead of os.system it will return the errorstatus"""
        """and take the name of a possible command file and the names of stdout and stderr"""
        """logfiles. it should be called  """
        utils.system( command ) or utils.die( "os.system ( %s ) failed" % command )
        return True

# ############################################################################################
# for testing purpose only:
# ############################################################################################
if __name__ == '__main__':
    if utils.verbose() > 0:    
        print "KDEROOT:     ", ROOTDIR
        print "KDECOMPILER: ", COMPILER
        print "DOWNLOADDIR: ", DOWNLOADDIR
        print "KDESVNDIR:   ", KDESVNDIR
        print "KDESVNSERVER:", KDESVNSERVER
        print "MSYSDIR:", MSYSDIR
    
    test = baseclass()
    test.system( "dir" )
