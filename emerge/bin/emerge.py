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
import utils

# get KDEROOT from env
KDEROOT = os.getenv( "KDEROOT" )
print "KDEROOT:", KDEROOT

buildaction = "all"

doPretend = False
offline = False
opts = ""

for i in sys.argv:
    print "got this param: %s" % i
    if ( i == "-p" ):
        doPretend = True
    elif ( i == "--offline" ):
        opts = i
        offline = True
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
    elif ( i == "--digest" ):
        buildaction = "digest"
    elif ( i == "--package" ):
        buildaction = "package"
    elif ( i == "--full-package" ):
        buildaction = "full-package"
    elif ( i.startswith( "-" ) ):
        print "error: emerge flag %s not understood" % i
        exit ( 1 )
    else:
        packagename = i

print "buildaction:", buildaction
print "doPretend:", doPretend
print "packagename", packagename


os.putenv( "PYTHONPATH", os.path.join( KDEROOT, "emerge", "bin" ) )

def doExec( category, package, version, action, opts ):
    print "doExec called opts:", opts
    file = os.path.join( utils.getPortageDir(), category, package, "%s-%s.py" % \
                         ( package, version ) )
    print "file:", file
    commandstring = "python %s %s %s" % ( file, action, opts )
    print "commandstring", commandstring
    if ( os.system( commandstring ) ):
        return False
    return True

def handlePackage( category, package, version, buildaction, opts ):
    print "handlePackage called:", category, package, version, buildaction
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
    else:
        print "could not understand this buildaction: %s" % buildaction
        success = false

    return success
    


deplist = []
utils.solveDependencies( "", packagename, "", deplist )
print "deplist:", deplist

deplist.reverse()
success = True

if ( buildaction == "digest" ):
    package = deplist[0]
    ok = handlePackage( package[0], package[1], package[2], buildaction, opts )
elif ( buildaction != "all" ):
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


#os.system( "cmake.py fetch" )
#os.system( "cmake.py unpack" )
#os.system( "cmake.py compile" )
#os.system( "cmake.py install" )
#os.system( "cmake.py qmerge" )

# digest
# clean
# preinst
# postinst
# qmerge
# unmerge, ...
