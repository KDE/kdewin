@echo off
rem    this file sets some environment variables that are needed
rem    for finding programs and libraries etc.
rem    by Holger Schroeder <schroder@kde.org>

rem    you should copy kdesettings-example.bat to ..\etc\kdesettings.bat
rem    and adapt it to your needs (see that file for more info)

call ..\etc\kdesettings.bat


set PATH=%KDEROOT%\emerge\bin;%PATH%
set PATH=%KDEROOT%\gnuwin32\bin;%PATH%
set PATH=%KDEROOT%\mingw\bin;%PATH%
set PATH=%KDEROOT%\cmake\bin;%PATH%
set PATH=%KDEROOT%\subversion\bin;%PATH%
set PATH=%KDEROOT%\win32libs\bin;%PATH%
set PATH=%KDEROOT%\kdewin32\bin;%PATH%
set PATH=%KDEROOT%\mc;%PATH%
set PATH=%KDEROOT%\qt\bin;%PATH%
set PATH=%KDEROOT%\qt\lib;%PATH%
set PATH=%KDEROOT%\dbus\bin;%PATH%
set PATH=%KDEROOT%\perl\bin;%PATH%
set PATH=%KDEROOT%\strigi\bin;%PATH%
set PATH=%KDEROOT%\kde\bin;%PATH%
set PATH=%KDEROOT%\kde\lib;%PATH%
set PATH=%KDEROOT%\bin;%PATH%
set PATH=%KDEROOT%\lib;%PATH%
@
@rem to find FindKDEInternal.cmake from kdepimlibs etc...
set KDEDIRS=%KDEROOT%\kde

cmd /K /e:on "cd %KDEROOT%"