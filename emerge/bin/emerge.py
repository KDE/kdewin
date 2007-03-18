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
    commandstring = "%s %s" % ( file, action )
    if ( os.system( commandstring ) ):
        return False
    return True

def handlePackage( category, package, version, buildaction ):
    print "handlePackage called:", category, package, version, buildaction
    success = True
    if ( ( buildaction == "fetch" or buildaction == "all" ) and success ):
         success = doExec( category, package, version, "fetch" )       
    if ( ( buildaction == "unpack" or buildaction == "all" ) and success ):
         success = doExec( category, package, version, "unpack" )       
    if ( ( buildaction == "compile" or buildaction == "all" ) and success ):
         success = doExec( category, package, version, "compile" )       
    if ( ( buildaction == "install" or buildaction == "all" ) and success ):
         success = doExec( category, package, version, "install" )       
    if ( ( buildaction == "qmerge" or buildaction == "all" ) and success ):
         success = doExec( category, package, version, "qmerge" )       

    return success
    


deplist = []
utils.solveDependencies( "", packagename, "", deplist )
print "deplist:", deplist

deplist.reverse()
success = True

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
