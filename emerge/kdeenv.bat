::rem   this file sets some environment variables that are needed
::rem   for finding programs and libraries etc.
::rem   by Holger Schroeder <schroder@kde.org>

:rem in ..\etc\kdesettings.bat you should set the following env vars:
:rem KDEROOT, KDECOMPILER and PYTHONPATH
:rem msvc2005 and mingw are supported right now
:rem they must be in a file outside of this svn checkout, so that your
:rem changes are not overwritten every time you make an svn update

:rem like this:
:rem set KDEROOT=e:\mingwroot
:rem set KDECOMPILER=mingw
:rem set PYTHONPATH=e:\python25
:rem set PATH=%PATH%;%PYTHONPATH%

call etc\kdesettings.bat


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
