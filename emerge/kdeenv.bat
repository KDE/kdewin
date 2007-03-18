::rem   this file sets some environment variables that are needed
::rem   for finding programs and libraries etc.
::rem   by Holger Schroeder <holger-kde@holgis.net>

::rem FIXME this should be known from the path to this file,
::rem then take the parent directory
::rem set KDEROOT=e:\secondroot
::rem set KDEROOT=e:\foo\thirdroot
::rem set KDEROOT=e:\vcroot


:rem argh, how do i set a path relative to _this_file_ ?
:rem instead of the actual directory of cmd.exe ?
call etc\kdesettings.bat
:rem there you should set KDEROOT and KDECOMPILER
:rem msvc2005 and mingw are supported right now


set PATH=%KDEROOT%\emerge\bin;%PATH%
set PATH=%KDEROOT%\gnuwin32\bin;%PATH%
set PATH=%KDEROOT%\mingw\bin;%PATH%
set PATH=%KDEROOT%\cmake\bin;%PATH%
set PATH=%KDEROOT%\subversion\bin;%PATH%
set PATH=%KDEROOT%\win32libs\bin;%PATH%
set PATH=%KDEROOT%\kdewin32\bin;%PATH%
set PATH=%KDEROOT%\mc;%PATH%
set PATH=%KDEROOT%\qt\bin;%PATH%
set PATH=%KDEROOT%\dbus\bin;%PATH%
set PATH=%KDEROOT%\perl\bin;%PATH%
set PATH=%KDEROOT%\kde\bin;%PATH%
set PATH=%KDEROOT%\kde\lib;%PATH%
