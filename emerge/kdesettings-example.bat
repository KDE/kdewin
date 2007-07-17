rem here you set the base directory under which the whole kde
rem system will live
set KDEROOT=e:\mingwroot

rem here you set the compiler to be used:
rem mingw : use the mingw gcc compiler (recommended)
rem msvc2005: use the microsoft visual studio 2005 c-compiler
set KDECOMPILER=mingw

rem here you should set the path to your python installation
rem this is needed, so that python will be found, when
rem python scripts will be executed. by setting this here,
rem you don´t have to change the environment settings of
rem windows at all
set PYTHONPATH=e:\python25

rem here you can set the download directory to another dir
rem if you want, so you can share the same download dir between
rem mingw and msvc
set DOWNLOADDIR=e:\distfiles

rem here you can tell emerge in which dir you want to save the
rem svn checkout of kde sources, and you can optionally
rem set the svn.kde.org server instead of the anonsvn.kde.org
rem one, so that you can directly commit your changes from the
rem svn checkout from emerge, if you want.
set KDESVNDIR=e:\kdesvn
set KDESVNSERVER=svn://anonsvn.kde.org
set KDESVNUSERNAME=username
rem for security reasons you better log in to the kde server by hand
rem and set the username and password at first login. then svn will
rem remember the password and it does not have to be written down here
rem set KDESVNPASSWORD=password

rem if you use svn+ssh, you'll need a ssh-agent equaivalent for managing the authorization 
rem Pageant is provided by putty, get it at 
rem http://www.chiark.greenend.org.uk/~sgtatham/putty/download.html
rem and make sure plink is in your path and Pageant is configured (you need to import your key)
set SVN_SSH=plink 

rem No editing should be necessary below this line (in an ideal world)
rem ##################################################################

set PATH=%PATH%;%PYTHONPATH%
set PATH=%PATH%;%KDEROOT%\mingw\bin
set PATH=%PATH%;%KDEROOT%\gnuwin32\bin
set PATH=%PATH%;%KDEROOT%\qt\bin
set PATH=%PATH%;%KDEROOT%\qt\lib
set PATH=%PATH%;%KDEROOT%\cmake\bin
set PATH=%PATH%;%KDEROOT%\win32libs\bin
set PATH=%PATH%;%KDEROOT%\kde\bin
set PATH=%PATH%;%KDEROOT%\kde\lib
set PATH=%PATH%;%KDEROOT%\dbus\bin
set KDEWIN_DIR=%KDEROOT%\win32libs
set STRIGI_HOME=%KDEROOT%\kde
set DBUSDIR=%KDEROOT%\dbus

@echo kdesettings.bat executed
@echo KDEROOT     : %KDEROOT%
@echo KDECOMPILER : %KDECOMPILER%
@echo KDESVNDIR   : %KDESVNDIR%
@echo PYTHONPATH  : %PYTHONPATH%
@echo DOWNLOADDIR : %DOWNLOADDIR%

