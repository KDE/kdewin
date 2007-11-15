import sys
import os

import shutil

# for get functions etc...
import utils
from utils import die

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

# an optional dir to compile autmake based sources
MSYSDIR = os.getenv( "MSYSDIR" )

quiet=os.getenv( "EMERGE_STAYQUIET" )
if ( quiet == "TRUE" ):
    stayQuiet = True
else:
    stayQuiet = False
    
# ok, we have the following dirs:
# ROOTDIR: the root where all this is below
# DOWNLOADDIR: the dir under rootdir, where the downloaded files are put into
# WORKDIR: the directory, under which the files are unpacked and compiled.
#            here rootdir/tmp/packagename/work
# IMAGEDIR: the directory, under which the compiled files are installed.
#            here rootdir/tmp/packagename/image

    
class baseclass:
# methods of baseclass:
# __init__                   constructor
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
# kdeCompileInternal
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
        #print "base init called"
        self.SRC_URI = SRC_URI
        self.instsrcdir = ""
        self.instdestdir = ""
        self.traditional = True
        self.stayQuiet = True
        self.forced = False
        self.versioned = False
        if not os.getenv( "EMERGE_STAYQUIET" ) == "TRUE":
            self.stayQuiet = False
        if DIRECTORYLAYOUT == "installer":
            self.traditional = False

        self.kdeCustomDefines = ""
        self.createCombinedPackage = False
        # Build type for kdeCompile() / kdeInstall() - packages
        # "" -> debug and release
        Type=os.getenv( "EMERGE_BUILDTYPE" )
        if ( not Type == None ):
            print "BuildType: %s" % Type
            self.buildType = Type
        else:
            self.buildType = None

        if COMPILER == "msvc2005":
            self.compiler = "msvc2005"
        elif COMPILER == "mingw":
            self.compiler = "mingw"
        else:
            print "error: KDECOMPILER: %s not understood" % COMPILER
            exit( 1 )

    def execute( self ):
        if not self.stayQuiet:
            print "base exec called. args:", sys.argv

        command = sys.argv[ 1 ]
        options = ""
        if ( len( sys.argv)  > 2 ):
            options = sys.argv[ 2: ]
        self.noFetch = False
        if ( "--offline" in options ):
            self.noFetch  = True
        if ( "--forced" in options ):
            self.forced = True
        if ( "--versioned" in options ):
            self.versioned = True
        if not self.stayQuiet:
            print "command:", command
            print "opts:", options
        
        self.setDirectories()

        ok = True
        if command == "fetch":        ok = self.fetch()
        elif command == "unpack":   ok = self.unpack()
        elif command == "compile":  ok = self.compile()
        elif command == "install":
            # make sure the image dir is clean
            if ( os.path.exists( self.imagedir ) ):
                if not self.stayQuiet:
                    print "cleaning image dir:", self.imagedir
                utils.cleanDirectory( self.imagedir )
            ok = self.install()
        elif command == "qmerge":   ok = self.qmerge()
        elif command == "unmerge":   ok = self.unmerge()
        elif command == "manifest":   ok = self.manifest()
        elif command == "merge":
            ok = self.fetch()
            if ( ok ):    ok = self.unpack()
            if ( ok ):    ok = self.compile()
            if ( os.path.exists( self.imagedir ) ):
                print "cleaning image dir:", self.imagedir
                utils.cleanDirectory( self.imagedir )
            if ( ok ):    ok = self.install()
            if ( ok ):    ok = self.qmerge()
            if ( ok ):
                print "merge success"
        elif command == "digest":   ok = self.digest()
        elif command == "package":  ok = self.make_package()
        else:
            print "command %s not understood" % command
            ok = False

        if ( not ok ):
            print "an error happened"
            exit( 1 )

    def fetch( self ):
        if not self.stayQuiet:
            print "base fetch called"
        if ( self.noFetch ):
            print "skipping fetch (--offline)"
            return True
        
        return utils.getFiles( self.SRC_URI, self.downloaddir )

    def unpack( self ):
        if not self.stayQuiet:
            print "base unpack called, files:", self.filenames
        return utils.unpackFiles( self.downloaddir, self.filenames, self.workdir )

    def compile( self ):
        if not self.stayQuiet:
            print "base compile called, doing nothing..."
        return True

    def install( self ):
        if not self.stayQuiet:
            print "base install called"
        srcdir = os.path.join( self.workdir, self.instsrcdir )
        destdir = os.path.join( self.imagedir, self.instdestdir )
        utils.copySrcDirToDestDir( srcdir, destdir )
        return True

    def qmerge( self ):
        if not self.stayQuiet:
            print "base qmerge called"
        utils.mergeImageDirToRootDir( self.imagedir, self.rootdir )
        utils.addInstalled( self.category, self.package, self.version )
        return True

    def unmerge( self ):
        if not self.stayQuiet:
            print "base unmerge called"
        utils.unmerge( self.rootdir, self.package, self.forced )
        utils.remInstalled( self.category, self.package, self.version )
        return True
        
    def manifest( self ):
        if not self.stayQuiet:
            print "base manifest called"
        utils.manifestDir( os.path.join( self.workdir, self.instsrcdir, self.package ), self.imagedir, self.package, self.version )
        return True
        
    def make_package( self ):
        if not self.stayQuiet:
            print "currently only supported for some interal packages"
        return True

    def setDirectories( self ):
        if not self.stayQuiet:
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
        if not self.stayQuiet:
            print "setdir category: %s, package: %s, version: %s" %\
              ( self.category, self.package, self.version )

        self.cmakeInstallPrefix = ROOTDIR.replace( "\\", "/" )
        if not self.stayQuiet:
            print "cmakeInstallPrefix:", self.cmakeInstallPrefix

        if COMPILER == "msvc2005":
            self.cmakeMakefileGenerator = "NMake Makefiles"
            self.cmakeMakeProgramm = "nmake"
        elif COMPILER == "mingw":
            self.cmakeMakefileGenerator = "MinGW Makefiles"
            self.cmakeMakeProgramm = "mingw32-make"
        else:
            print "error: KDECOMPILER: %s not understood" % COMPILER
            exit( 1 )

        self.rootdir     = ROOTDIR
        self.downloaddir = DOWNLOADDIR
        self.workdir     = os.path.join( ROOTDIR, "tmp", self.PV, "work" )
        self.imagedir    = os.path.join( ROOTDIR, "tmp", self.PV, "image-" + COMPILER )

        self.packagedir = os.path.join( ROOTDIR, "emerge", \
            "portage", self.category, self.package )
        self.filesdir = os.path.join( self.packagedir, "files" )
        self.kdesvndir = KDESVNDIR
        self.kdesvnserver = KDESVNSERVER
        self.kdesvnuser = KDESVNUSERNAME
        self.kdesvnpass = KDESVNPASSWORD
        self.msysdir = MSYSDIR
        self.strigidir = os.getenv( "STRIGI_HOME" )
        self.dbusdir = os.getenv( "DBUSDIR" )

    def svnFetch( self, repo ):
        """getting sources from a custom svn repo"""
        if not self.stayQuiet:
            print "base svnFetch called"
        self.svndir = os.path.join( self.downloaddir, "svn-src", self.package )
        if ( self.noFetch ):
            if not self.stayQuiet:
                print "skipping svn fetch/update (--offline)"
            return True
        
        utils.svnFetch( repo, self.svndir )

    def __kdesinglecheckout( self, repourl, ownpath, codir, doRecursive = False ):
        """in ownpath try to checkout codir from repourl 
           if codir exists and doRecursive is false, simply return,
           if codir does not exist, but ownpath/.svn exists,
              do a svn update codir
           else do svn co repourl/codir
           if doRecursive is false, add -N to the svn command """

        if ( os.path.exists( os.path.join( ownpath, codir ) ) \
                             and not doRecursive ):
            if not self.stayQuiet:
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

        if not self.stayQuiet:
            print "kdesinglecheckout:pwd ", ownpath
            print "kdesinglecheckout:   ", svncmd
        os.chdir( ownpath )
        self.system( svncmd )
                
    def kdeSvnFetch( self, svnpath, packagedir ):
        """svnpath is the part of the repo url after /home/kde, for example
           "trunk/kdesupport/", which leads to the package itself,
           without the package"""
        if not self.stayQuiet:
            print "base kdeSvnFetch called. svnpath: %s dir: %s" % \
                      ( svnpath, packagedir )

        if ( self.noFetch ):
            if not self.stayQuiet:
                print "skipping svn fetch/update (--offline)"
            return True
        
        mydir = self.kdesvndir
        if ( not os.path.exists( mydir ) ):
                os.mkdir( mydir )

        repourl = self.kdesvnserver + "/home/kde/"

        for tmpdir in svnpath.split( "/" ):
            if ( tmpdir == "" ):
                    continue
            if not self.stayQuiet:
                print "  mydir: %s" % mydir
                print "  dir to checkout: %s" % tmpdir
                print "  repourl", repourl

            self.__kdesinglecheckout( repourl, mydir, tmpdir, False )
            mydir = os.path.join( mydir, tmpdir )
            repourl = repourl + tmpdir + "/"
                
            if not self.stayQuiet:
                print "dir in which to really checkout: %s" % mydir
                print "dir to really checkout: %s" % packagedir
            self.__kdesinglecheckout( repourl, mydir, packagedir, True )

        svndir = os.path.join( self.kdesvndir, svnpath ).replace( "/", "\\" )
        #repo = self.kdesvnserver + "/home/kde/" + svnpath + dir
        #utils.svnFetch( repo, svndir, self.kdesvnuser, self.kdesvnpass )
        if not self.stayQuiet:
            print "kdesvndir", self.kdesvndir
            print "svndir", svndir
            print "dir", dir
        self.svndir = os.path.join( svndir, packagedir )
        
        return True

    def kdeSvnUnpack( self, svnpath, packagedir ):
        """fetching and copying the sources from svn"""
        self.kdeSvnFetch( svnpath, packagedir )
        
        if( not os.path.exists( self.workdir ) ):
            os.makedirs( self. workdir )
        
        # now copy the tree to workdir
        srcdir  = os.path.join( self.kdesvndir, svnpath, packagedir )
        destdir = os.path.join( self.workdir, packagedir )
        utils.copySrcDirToDestDir( srcdir, destdir )
        return True
        
    def kdeDefaultDefines( self ):
        #FIXME: can we define the paths externally???
        package_path = self.package
        if( not self.instsrcdir == "" ):
            package_path = self.instsrcdir

        if self.traditional:
            options = "..\\%s -DCMAKE_INSTALL_PREFIX=%s/kde " % \
                  ( package_path, self.rootdir.replace( "\\", "/" ) )

            options = options + "-DCMAKE_INCLUDE_PATH=%s;%s " % \
                    ( os.path.join( self.rootdir, "win32libs", "include" ).replace( "\\", "/" ), \
                      os.path.join( self.rootdir, "kde", "include" ).replace( "\\", "/" ) \
                    )

            options = options + "-DCMAKE_LIBRARY_PATH=%s;%s " % \
                    ( os.path.join( self.rootdir, "win32libs", "lib" ).replace( "\\", "/" ), \
                      os.path.join( self.rootdir, "kde", "lib" ).replace( "\\", "/" ) \
                    )
        else:
            options = "..\\%s -DCMAKE_INSTALL_PREFIX=%s " % \
                  ( package_path, self.rootdir.replace( "\\", "/" ) )
            
            options = options + "-DCMAKE_INCLUDE_PATH=%s " % \
                    os.path.join( self.rootdir, "include" ).replace( "\\", "/" )
            
            options = options + "-DCMAKE_LIBRARY_PATH=%s " % \
                    os.path.join( self.rootdir, "lib" ).replace( "\\", "/" )

        
        return options

    def kdeCompileInternal( self, buildType ):
        builddir = "%s-build-%s" % ( self.package, self.compiler )

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

        if not self.stayQuiet:
            print command
        self.system( command )
        self.system( self.cmakeMakeProgramm )
        return True

    def kdeCompile( self ):
        if( not self.buildType == None ) :
            if( not self.kdeCompileInternal( self.buildType ) ):
                return False
        else:
            if( not self.kdeCompileInternal( "debug" ) ):
                return False
            if( not self.kdeCompileInternal( "release" ) ):
                return False
        return True

    def kdeInstallInternal( self, buildType ):
        builddir = "%s-build-%s" % ( self.package, self.compiler )

        if( not buildType == None ):
            builddir = "%s-%s" % ( builddir, buildType )

        os.chdir( self.workdir )
        os.chdir( builddir )
        if not self.stayQuiet:
            print "builddir: " + builddir

        self.system( "%s DESTDIR=%s install" % \
                   ( self.cmakeMakeProgramm , self.imagedir ) )
        return True

    def kdeInstall( self ):
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
        dstpath = os.path.join( self.rootdir, "tmp", self.PV )
        binpath = os.path.join( self.imagedir, self.instdestdir )
        tmp = os.path.join( binpath, "kde" )

        if( os.path.exists( tmp ) ):
            binpath = tmp

        if ( packSources ):
            srcpath = os.path.join( self.workdir, self.instsrcdir )
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
        basepath = os.path.join( self.imagedir, self.instdestdir )
        dllpath = os.path.join( basepath, "bin", "%s.dll" % pkg_name )

        cmd = "strip -s " + dllpath
        self.system( cmd )
        return True

    def msysConfigureFlags ( self ):
        flags  = "--disable-nls "
        flags += "--disable-static "
        flags += "--prefix=/ "
        return flags

    def msysCompile( self, bOutOfSource = True ):
        config = os.path.join( self.workdir, self.instsrcdir, "configure" )
        build  = os.path.join( self.workdir )
        if( bOutOfSource ):
           build  = os.path.join( build, self.instsrcdir + "-build" )
           utils.cleanDirectory( build )
        else:
           build  = os.path.join( build, self.instsrcdir )

        sh = os.path.join( self.msysdir, "bin", "sh.exe" )

        cmd = "%s --login -c \"cd %s && %s %s && make -j2\"" % \
              ( sh, utils.toMSysPath( build ), utils.toMSysPath( config ), \
                self.msysConfigureFlags() )
        if not self.stayQuiet:
            print cmd
        self.system( cmd )
        return True

    def msysInstall( self, bOutOfSource = True ):
        install = os.path.join( self.imagedir, self.instdestdir )
        build  = os.path.join( self.workdir )
        if( bOutOfSource ):
           build  = os.path.join( build, self.instsrcdir + "-build" )
        else:
           build  = os.path.join( build, self.instsrcdir )

        sh = os.path.join( self.msysdir, "bin", "sh.exe" )

        cmd = "%s --login -c \"cd %s && make -j2 install DESTDIR=%s\"" % \
              ( sh, utils.toMSysPath( build ), utils.toMSysPath( install ) )
        if not self.stayQuiet:
            print cmd
        self.system( cmd )
        return True

    def system( self, command , infileName = None, outfileName = os.path.join( ROOTDIR, "out.log" ), errfileName = os.path.join( ROOTDIR, "out.log" ) ):
        """ this function should be called instead of os.system it will return the errorstatus 
            and take the name of a possible command file and the names of stdout and stderr
            logfiles. it should be called  """
        os.system( command ) and \
            utils.die( "os.system ( %s ) failed" % command)
        return True

# ############################################################################################
# for testing purpose only:
# ############################################################################################
if '__main__' in globals().keys():
    if not stayQuiet:    
        print "KDEROOT:     ", ROOTDIR
        print "KDECOMPILER: ", COMPILER
        print "DOWNLOADDIR: ", DOWNLOADDIR
        print "KDESVNDIR:   ", KDESVNDIR
        print "KDESVNSERVER:", KDESVNSERVER
        print "MSYSDIR:", MSYSDIR
    
    test = baseclass()
    test.system( "dir" )
