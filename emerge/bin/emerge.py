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

for i in sys.argv:
    print "got this param: %s" % i
    if ( i == "-p" ):
        doPretend = True
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
    elif ( i.startswith( "-" ) ):
        print "error: emerge flag %s not understood" % i
        exit ( 1 )
    else:
        packagename = i

print "buildaction:", buildaction
print "doPretend:", doPretend
print "packagename", packagename


os.putenv( "PYTHONPATH", os.path.join( KDEROOT, "emerge", "bin" ) )

def doExec( category, package, version, action ):
    print "doExec called"
    file = os.path.join( utils.getPortageDir(), category, package, "%s-%s.py" % \
                         ( package, version ) )
    print "file:", file
    commandstring = "python %s %s" % ( file, action )
    if ( os.system( commandstring ) ):
        return False
    return True

def handlePackage( category, package, version, buildaction ):
    print "handlePackage called:", category, package, version, buildaction
    success = True
    if ( buildaction == "all" ):
        if ( success ):
            success = doExec( category, package, version, "fetch" )
        if ( success ):
            success = doExec( category, package, version, "unpack" )       
        if ( success ):
            success = doExec( category, package, version, "compile" )       
        if ( success ):
            success = doExec( category, package, version, "install" )       
        if ( success ):
            success = doExec( category, package, version, "qmerge" )

    elif ( buildaction == "fetch" ):
        success = doExec( category, package, version, "fetch" )       
    elif ( buildaction == "unpack" ):
        success = doExec( category, package, version, "unpack" )       
    elif ( buildaction == "compile" ):
        success = doExec( category, package, version, "compile" )       
    elif ( buildaction == "install" ):
        success = doExec( category, package, version, "install" )       
    elif ( buildaction == "qmerge" ):
        success = doExec( category, package, version, "qmerge" )
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
    ok = handlePackage( package[0], package[1], package[2], buildaction )
else:
  for package in deplist:
    file = os.path.join( KDEROOT, "emerge", "portage", package[0], package[1], "%s-%s.py" % ( package[1], package[2] ) )
    if ( doPretend ):
        if ( utils.isInstalled( package[0], package[1], package[2] ) ):
            print "already installed %s/%s-%s" % ( package[0], package[1], package[2] )
        else:
            print "pretending %s/%s-%s" % ( package[0], package[1], package[2] )
    else:
        if ( not utils.isInstalled( package[0], package[1], package[2] ) ):
            ok = handlePackage( package[0], package[1], package[2], buildaction )
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
