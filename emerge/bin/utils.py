# this file contains some helper functions for emerge

import httplib
import ftplib
import os
import urlparse
import shutil
import zipfile
import tarfile

import portage_versions


### fetch functions

def getFiles( urls, destdir ):
    print "getfiles called. urls:", urls
    # make sure distfiles dir exists
    if ( not os.path.exists( destdir ) ):
        os.makedirs( destdir )

    for url in urls.split():
        #print "getfiles url:", url
        if ( not getFile( url, destdir ) ):
            return False

    return True

def getFile( url, destdir ):
    print "getFile called. url:", url
    if url == "":
        print "fetch error: no url given"
        return False

    wgetpath = os.path.join( os.getenv( "KDEROOT" ), "gnuwin32", "bin", "wget.exe" )
    if ( os.path.exists( wgetpath ) ):
        return wgetFile( url, destdir )

    scheme, host, path, params, qu, fr = urlparse.urlparse( url )

    print scheme
    print host
    print path

    filename = os.path.basename( path )
    print filename

    if ( scheme == "http" ):
        return getHttpFile( host, path, destdir, filename )
    elif ( scheme == "ftp" ):
        return getFtpFile( host, path, destdir, filename )
    else:
        print "getFile error: protocol not understood"
        return False

def wgetFile( url, destdir ):
    print "wgetfile called"
    compath = os.path.join( os.getenv( "KDEROOT" ), "gnuwin32", "bin", "wget.exe" )
    command = "%s -c -t 1 -P %s %s" % ( compath, destdir, url )
    print "executing this command:", command
    ret = os.system( command )
    print "wget ret:", ret
    if ( ret == 0 ):
        return True
    else:
        return False
    
def getFtpFile( host, path, destdir, filename ):
    # FIXME check return values here (implement useful error handling)...
    print "FIXME getFtpFile called.", host, path
    
    outfile = open( os.path.join( destdir, filename ), "wb" )
    ftp = ftplib.FTP( host )
    ftp.login( "anonymous", "johndoe" )
    ftp.retrbinary( "RETR " + path, outfile.write )

    outfile.close()
    return True

def getHttpFile( host, path, destdir, filename ):
    # FIXME check return values here (implement useful error handling)...
    print "getHttpFile called.", host, path
    
    conn = httplib.HTTPConnection( host )
    conn.request( "GET", path )
    r1 = conn.getresponse()
    print r1.status, r1.reason

    data = r1.read()

    f = open( os.path.join( destdir, filename ), "wb" )
    f.write( data )
    f.close()
    return True


### unpack functions

def unpackFiles( downloaddir, filenames, workdir ):
    # make sure that the workdir is empty
    if ( os.path.exists( workdir ) ):
        cleanDirectory( workdir )

    # make sure the workdir exists
    if ( not os.path.exists( workdir ) ):
        os.makedirs( workdir )
    
    for filename in filenames:
        print "unpacking this file:", filename
        if ( not unpackFile( downloaddir, filename, workdir ) ):
            return False

    return True        


def unpackFile( downloaddir, filename, workdir ):
    ( shortname, ext ) = os.path.splitext( filename )
    if ( ext == ".zip" ):
        return unZip( os.path.join( downloaddir, filename ), workdir )
    elif ( ext == ".gz" or ext == ".bz2" ):
        ( myshortname, myext ) = os.path.splitext( shortname )
        if ( myext == ".tar" ):
            return unTar( os.path.join( downloaddir, filename ), workdir )
        else:
            print "error:", myext
            return False
    else:
        if ( ext == ".exe" ):
            print "unpack ignoring exe file"
            return True
        print "dont know how to unpack this file:", filename
        return False


def unTar( file, destdir ):
    print "unTar called. file: %s, destdir: %s" % ( file, destdir )
    ( shortname, ext ) = os.path.splitext( file )

    mode = "r"
    if ( ext == ".gz" ):
        mode = "r:gz"
    elif ( ext == ".bz2" ):
        mode = "r:bz2"
    
    tar = tarfile.open( file, mode )

    # FIXME how to handle errors here ?
    for foo in tar:
        tar.extract( foo, destdir )

    return True

def unZip( file, destdir ):
    print "unZip called:", file, destdir

    if not os.path.exists(destdir):
        os.makedirs(destdir)

    zip = zipfile.ZipFile(file)

    for i, name in enumerate(zip.namelist()):
        if not name.endswith('/'):
            dirname = os.path.join( destdir, os.path.dirname( name ) )

            if not os.path.exists(dirname):
                os.makedirs(dirname)
            
            outfile = open(os.path.join(destdir, name), 'wb')
            outfile.write(zip.read(name))
            outfile.flush()
            outfile.close()
    
    return True


### svn fetch/unpack functions

def svnFetch( repo, destdir, username = None, password = None ):
    print "utils svnfetch", repo, destdir
    if ( not os.path.exists( destdir ) ):
        os.makedirs( destdir )
    os.chdir( destdir )

    ret = 0
    #if ( len( os.listdir( destdir ) ) == 0 ):

    dir = os.path.basename( repo.replace( "/", "\\" ) )
    path = os.path.join( destdir, dir )
    print "path: ", path 
    if ( not os.path.exists( path ) ):
        # not checked out yet
        command = "svn checkout %s" % repo
        if ( username != None ):
            command = command + " --username " + username
        if ( password != None ):
            command = command + " --password " + password
        print "executing this:", command
        ret = os.system( command )
    else:
        # already checked out, so only update
        mode = "update"
        os.chdir( path )
        print "svn up cwd:", os.getcwd()
        ret = os.system( "svn update" )

    if ( ret == 0 ):
        return True
    else:
        return False

### digest functions

def digestFiles( downloaddir, filenames, packagedir ):
    for filename in filenames:
        print "digestinging this file:", filename
        if ( not digestFile( downloaddir, filename, packagedir ) ):
            return False

    return True        


def digestFile( downloaddir, filename, packagedir ):
    #( shortname, ext ) = os.path.splitext( filename )
    #if ( ext == ".zip" ):
    #    return unZip( os.path.join( downloaddir, filename ), workdir )
    #elif ( ext == ".gz" or ext == ".bz2" ):
    #    ( myshortname, myext ) = os.path.splitext( shortname )
    #    if ( myext == ".tar" ):
    #        return unTar( os.path.join( downloaddir, filename ), workdir )
    #    else:
    #        print "error:", myext
    #        return False
    #else:
    #    print "dont know how to unpack this file:", filename
    #    return False
    return True



### package dependencies functions
    
def isInstalled( category, package, version ):
    file = os.path.join( os.getenv( "KDEROOT" ), "etc", "portage", "installed" )
    if ( not os.path.isfile( file ) ):
        print "isInstalled file does not exist"
        return False

    found = False
    f = open( file, "r" )
    for line in f.read().splitlines():
        if ( line == "%s/%s-%s" % ( category, package, version ) ):
            found = True
            break

    f.close()
    return found
    
def addInstalled( category, package, version ):
    print "addInstalled called"
    # write a line to etc/portage/installed,
    # that contains category/package-version
    path = os.path.join( os.getenv( "KDEROOT" ), "etc", "portage" )
    if ( not os.path.isdir( path ) ):
        os.makedirs( path )
    f = open( os.path.join( path, "installed" ), "a" )
    f.write( "%s/%s-%s\r\n" % ( category, package, version ) )
    f.close()

def getCategoryPackageVersion( path ):
    print "getCategoryPackageVersion:", path
    ( head, file ) = os.path.split( path )
    ( head, package ) = os.path.split( head )
    ( head, category ) = os.path.split( head )

    (foo, ext) = os.path.splitext( file )
    ( package, version, foo2 ) = portage_versions.pkgsplit(foo)
    print "category: %s, package: %s, version: %s" %( category, package, version )
    return [ category, package, version ]

def getPortageDir():
    return os.path.join( os.getenv( "KDEROOT" ), "emerge", "portage" )

def getFilename( category, package, version ):
    file = os.path.join( getPortageDir(), category, package, "%s-%s.py" % ( package, version ) )
    return file

def getCategory( package ):
    """
    returns the category of this package
    """
    print "getCategory:", package
    basedir = getPortageDir()

    for cat in os.listdir( basedir ):
        #print "category:", cat
        catpath = os.path.join( basedir, cat )
        if ( os.path.isdir( catpath ) ):
            for pack in os.listdir( catpath ):
                #print "    package:", pack
                if ( pack == package ):
                    print "found:", cat, pack
                    return cat

def getNewestVersion( category, package ):
    """
    returns the newest version of this category/package
    """
    print "getNewestVersion:", category, package
    packagepath = os.path.join( getPortageDir(), category, package )

    versions = []
    for file in os.listdir( packagepath ):
        (shortname, ext) = os.path.splitext( file )
        if ( ext != ".py" ):
            continue
        if ( shortname.startswith( package ) ):
            versions.append( shortname )

    tmpver = ""
    for ver in versions:
        if ( tmpver == "" ):
            tmpver = ver
        else:
            ret = portage_versions.pkgcmp(portage_versions.pkgsplit(ver), \
                                          portage_versions.pkgsplit(tmpver))
            if ( ret == 1 ):
                tmpver = ver

    ret = portage_versions.catpkgsplit( tmpver )
    #print "ret:", ret
    return ret[ 2 ]

def getDependencies( category, package, version ):
    """
    returns the dependencies of this package as list of strings:
    category/package
    """
    f = open( getFilename( category, package, version ), "rb" )
    lines = f.read()
    #print "lines:", lines
    # get DEPENDS=... lines
    deplines = []
    inDepend = False

    # FIXME make this more clever
    for line in lines.splitlines():
        if ( inDepend == True ):
            if ( line.find( "\"\"\"" ) != -1 ):
                break
            deplines.append( line )
        if ( line.startswith( "DEPEND" ) ):
            inDepend = True

    print "deplines:", deplines

    deps = []
    for line in deplines:
        (category, package) = line.split( "/" )
        version = getNewestVersion( category, package )
        deps.append( [ category, package, version ] )
    return deps


def solveDependencies( category, package, version, deplist ):
    if ( category == "" ):
        category = getCategory( package )

    if ( version == "" ):
        version = getNewestVersion( category, package )

    deplist.append( [ category, package, version ] )

    mydeps = getDependencies( category, package, version )
    print "mydeps:", mydeps
    for dep in mydeps:
        solveDependencies( dep[0], dep[1], dep[2], deplist )
    # if package not in list, prepend it to list
    # get deps of this package
    # for every dep call solvedeps
    #return deplist

### helper functions    
def die( message ):
    print "fatal error: %s" % message
    exit( 1 )

def copySrcDirToDestDir( srcdir, destdir ):
    print "copySrcDirToDestDir called. srcdir: %s, destdir: %s" % ( srcdir, destdir )

    mysrcdir = srcdir
    if ( not srcdir.endswith( "\\" ) ):
	mysrcdir = mysrcdir + "\\"

    mydestdir = destdir
    if ( not destdir.endswith( "\\" ) ):
	mydestdir = mydestdir + "\\"
    print "copySrcDirToDestDir called. mysrcdir: %s, mydestdir: %s" % ( mysrcdir, mydestdir )
	
    
    for root, dirs, files in os.walk( mysrcdir ):
        print "rootdir:", root

        # do not copy files under .svn directories, because they are write-protected
        # and the they cannot easily be deleted...
        if ( root.find( ".svn" ) == -1 ):
            #print "srcdir:", srcdir
            #print "destdir:", destdir
            tmpdir = root.replace( mysrcdir, mydestdir )
            #print "tmpdir:", tmpdir
            if ( not os.path.exists( tmpdir ) ): os.makedirs( tmpdir )
            for file in files:
                #print "src file:", root, file
                shutil.copy( os.path.join( root, file ), tmpdir )


def mergeImageDirToRootDir( imagedir, rootdir ):
    print "mergeImageDirToRootDir called. id: %s, root: %s" % ( imagedir, rootdir )
    copySrcDirToDestDir( imagedir, rootdir )

def moveEntries( srcdir, destdir ):
    print "moveEntries:", srcdir, destdir
    for entry in os.listdir( srcdir ):
        #print "rootdir:", root
        print "entry:", entry
        src = os.path.join( srcdir, entry )
        dest = os.path.join( destdir, entry )
        print "src: %s dest: %s" %( src, dest )
        os.rename( src, dest )
    
def moveImageDirContents( imagedir, relSrcDir, relDestDir ):
    print "moveImageDirContents:", imagedir, relSrcDir, relDestDir

    srcdir = os.path.join( imagedir, relSrcDir )    
    destdir = os.path.join( imagedir, relDestDir )    

    if ( not os.path.isdir( destdir ) ):
        os.mkdir( destdir )

    moveEntries( srcdir, destdir )
    os.chdir( imagedir )    
    os.removedirs( relSrcDir )


def fixCmakeImageDir( imagedir, rootdir ):
    """
    when using DESTDIR=foo under windows, it does not _replace_
    CMAKE_INSTALL_PREFIX with it, but prepends destdir to it.
    so when we want to be able to install imagedir into KDEROOT,
    we have to move things around...
    """
    print "fixImageDir:", imagedir, rootdir
    # imagedir = e:\foo\thirdroot\tmp\dbus-0\image
    # rootdir  = e:\foo\thirdroot
    # files are installed to
    # e:\foo\thirdroot\tmp\dbus-0\image\foo\thirdroot
    ( rootdrive, rootpath ) = os.path.splitdrive( rootdir )
    #print "rp:", rootpath
    if ( rootpath.startswith( "\\" ) ):
        rootpath = rootpath[1:]
    tmp = os.path.join( imagedir, rootpath )
    print "tmp:", tmp
    tmpdir = os.path.join( imagedir, "tMpDiR" )

    if ( not os.path.isdir( tmpdir ) ):
        os.mkdir( tmpdir )

    moveEntries( tmp, tmpdir )
    os.chdir( imagedir )    
    os.removedirs( rootpath )
    moveEntries( tmpdir, imagedir )
    os.rmdir( tmpdir )

def cleanDirectory( dir ):
    print "cleanDirectory called. dir:", dir
    if ( os.path.exists( dir ) ):
        for root, dirs, files in os.walk( dir, topdown=False):
            for name in files:
                os.remove(os.path.join(root, name))
            for name in dirs:
                os.rmdir(os.path.join(root, name))


    
