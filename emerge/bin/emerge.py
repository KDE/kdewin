# this will emerge some programs...

# call this with "emerge.py <packagename> <action>"
# where packagename is the program you want to install
# and action is the action you want to do, see base.py
#
# Holger Schroeder <holger@holgis.net>

# syntax:
# emerge <options> <action> <packagename>
#
# action can be:
# --fetch, --unpack, --compile, --install, --qmerge
#
# options can be:
# -p for pretend

import sys
import os

def usage():
    print
    print 'usage: emerge [-f|-p|-q|-v][--fetch|--unpack|--compile|--install|'
    print '                            --manifest|--qmerge|--unmerge|--package|'
    print '                            --full-package] packagename'
    print 'emerge.py is a script for easier building.'
    print
    print 'flags:'
    print '-p               pretend to do everything - a dry run'
    print '-q               suppress all output'
    print '-f               force removal of files with unmerge'
    print '-v               print additional output'
    print '--buildtype=[KdeBuildType] where KdeBuildType is one of the used BuildTypes'
    print '                 This will automatically overrun all buildtype definitions'
    print '                 made in the package\'s .py-file'
    print 'options:'
    print '--fetch          just fetch the packages'
    print '--unpack         unpack the packages and apply the patches if needed'
    print '--compile        configure and build the package'
    print '--install        install the package to an image directory'
    print '--manifest       add the installdb files to the image directory'
    print '--qmerge         install the image directories contents to the kderoot'
    print '--package        package the image directory with the kdewin-packager[*]'
    print '--full-package   make all of the above steps'
    print '--unmerge        try to unmerge package'
    print
    print '[*] - this requires the packager to be installed already'
    print 'please see http://windows.kde.org for more information'
    print 'send bugs and feature requests to kde-windows@kde.org'
    print

buildaction = "all"

doPretend = False
stayQuiet = False
offline = False
opts = ""
verbose = 0

if len( sys.argv ) < 2:
    usage()
    exit( 1 )

quiet=os.getenv( "EMERGE_STAYQUIET" )
if ( quiet == "TRUE" ):
    stayQuiet = True
else:
    stayQuiet = False
verbose=os.getenv( "EMERGE_VERBOSE" )
if verbose == None or not verbose.isdigit():
    verbose = 0
    os.environ["EMERGE_VERBOSE"]=""
opts = list()
for i in sys.argv:
#    print "got this param: %s" % i
    if ( i == "-p" ):
        doPretend = True
    elif ( i == "-q" ):
        stayQuiet = True
    elif ( i == "--offline" ):
        opts.append( "--offline" )
        offline = True
    elif ( i == "-f" ):
        opts.append( "--forced" )
    elif ( i.startswith( "--version=" ) ):
        print "versioned", i.replace( "--version=", "" )
        srcversion = i.replace( "--version=", "" )
        opts.append( "--versioned" )
    elif ( i.startswith( "--buildtype=" ) ):
        print "chosen buildtype: ", i.replace( "--buildtype=", "" )
        os.environ["EMERGE_BUILDTYPE"] = i.replace( "--buildtype=", "" )
    elif ( i == "-v" ):
        verbose = int(verbose) + 1
        os.environ["EMERGE_VERBOSE"] = str(verbose)
    elif ( i == "--fetch" ):
        buildaction = "fetch"
    elif ( i == "--unpack" ):
        buildaction = "unpack"
    elif ( i == "--compile" ):
        buildaction = "compile"
    elif ( i == "--install" ):
        buildaction = "install"
    elif ( i == "--qmerge" ):
        buildaction = "qmerge"
    elif ( i == "--manifest" ):
        buildaction = "manifest"        
    elif ( i == "--package" ):
        buildaction = "package"
    elif ( i == "--unmerge" ):
        buildaction = "unmerge"
    elif ( i == "--full-package" ):
        buildaction = "full-package"
    elif ( i.startswith( "-" ) ):
        usage()
        exit ( 1 )
    else:
        packagename = i
if stayQuiet == True:
    os.environ["EMERGE_STAYQUIET"]="TRUE"
else:
    os.environ["EMERGE_STAYQUIET"]="FALSE"
import utils

# get KDEROOT from env
KDEROOT = os.getenv( "KDEROOT" )

if not stayQuiet:
    print "buildaction:", buildaction
    print "doPretend:", doPretend
    print "packagename:", packagename
    print "buildType:", os.getenv("EMERGE_BUILDTYPE")
    print "KDEROOT:", KDEROOT
    
if verbose:
    print "verbose:", os.getenv("EMERGE_VERBOSE")
    

# adding emerge/bin to find base.py and gnuwin32.py etc.
os.environ["PYTHONPATH"] = os.getenv("PYTHONPATH") + ";" + os.path.join( os.getcwd(), os.path.dirname( sys.argv[0] ) )

def doExec( category, package, version, action, opts ):
    if not stayQuiet:
        print "emerge doExec called opts:", opts
    file = os.path.join( utils.getPortageDir(), category, package, "%s-%s.py" % \
                         ( package, version ) )
    opts_string = ( "%s " * len(opts) ) % tuple( opts )
    commandstring = "python %s %s %s" % ( file, action, opts_string )
    print commandstring
    if not stayQuiet:
        print "file:", file
        print "commandstring", commandstring
    if ( os.system( commandstring ) ):
        return False
    return True

def handlePackage( category, package, version, buildaction, opts ):
    if not stayQuiet:
        print "emerge handlePackage called:", category, package, version, buildaction
    success = True
    if ( buildaction == "all" or buildaction == "full-package" ):
        if ( success ):
            success = doExec( category, package, version, "fetch", opts )
        if ( success ):
            success = doExec( category, package, version, "unpack", opts )       
        if ( success ):
            success = doExec( category, package, version, "compile", opts )       
        if ( success ):
            success = doExec( category, package, version, "install", opts )       
        if ( success and buildaction == "all" ):
            success = doExec( category, package, version, "manifest", opts )
        if ( success and buildaction == "all" ):
            success = doExec( category, package, version, "qmerge", opts )
        if( success and buildaction == "full-package" ):
            success = doExec( category, package, version, "package", opts )

    elif ( buildaction == "fetch" ):
        success = doExec( category, package, version, "fetch", opts )       
    elif ( buildaction == "unpack" ):
        success = doExec( category, package, version, "unpack", opts )       
    elif ( buildaction == "compile" ):
        success = doExec( category, package, version, "compile", opts )       
    elif ( buildaction == "install" ):
        success = doExec( category, package, version, "install", opts )       
    elif ( buildaction == "qmerge" ):
        success = doExec( category, package, version, "qmerge", opts )
    elif ( buildaction == "package" ):
        success = doExec( category, package, version, "package", opts )
    elif ( buildaction == "manifest" ):
        success = doExec( category, package, version, "manifest", opts )
    elif ( buildaction == "unmerge" ):
        success = doExec( category, package, version, "unmerge", opts )
    else:
        if not stayQuiet:
            print "could not understand this buildaction: %s" % buildaction
        success = false

    return success
    


deplist = []
utils.solveDependencies( "", packagename, "", deplist )
if verbose:
    print "deplist:", deplist

deplist.reverse()
success = True

if ( buildaction != "all" ):
    # if a buildaction is given, then do not try to build dependencies
    # and do the action although the package might already be installed
    package = deplist[-1]
    ok = handlePackage( package[0], package[1], package[2], buildaction, opts )
else:
  for package in deplist:
    file = os.path.join( KDEROOT, "emerge", "portage", package[0], package[1], "%s-%s.py" % ( package[1], package[2] ) )
    if ( doPretend ):
        if ( utils.isInstalled( package[0], package[1], package[2] ) ):
            #print "already installed %s/%s-%s" % ( package[0], package[1], package[2] )
            pass
        else:
            print "pretending %s/%s-%s" % ( package[0], package[1], package[2] )
    else:
        if ( not utils.isInstalled( package[0], package[1], package[2] ) ):
            ok = handlePackage( package[0], package[1], package[2], buildaction, opts )
            if ( not ok ):
                print "fatal error: package %s/%s-%s %s failed" % \
                    (package[0], package[1], package[2], buildaction)
        else:
            print "already installed %s/%s-%s" % ( package[0], package[1], package[2] )
