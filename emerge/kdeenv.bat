@echo off
rem    this file sets some environment variables that are needed
rem    for finding programs and libraries etc.
rem    by Holger Schroeder <schroder@kde.org>

rem    you should copy kdesettings-example.bat to ..\etc\kdesettings.bat
rem    and adapt it to your needs (see that file for more info)

call ..\etc\kdesettings.bat

set PATH=%PATH%;%KDEROOT%\emerge\bin
if /i %KDECOMPILER% == mingw (
    set PATH=%PATH%;%KDEROOT%\mingw\bin
)

if /i %directory_layout% == installer (
    set PATH=%KDEROOT%\bin;%PATH%
    set PATH=%KDEROOT%\lib;%PATH%
    set KDEDIRS=%KDEROOT%
) else (
    set PATH=%PATH%;%KDEROOT%\gnuwin32\bin
    set PATH=%PATH%;%KDEROOT%\subversion\bin
    set PATH=%PATH%;%KDEROOT%\qt\bin
    set PATH=%PATH%;%KDEROOT%\qt\lib
    set PATH=%PATH%;%KDEROOT%\cmake\bin
    set PATH=%PATH%;%KDEROOT%\kdewin32\bin
    set PATH=%PATH%;%KDEROOT%\win32libs\bin
    set PATH=%PATH%;%KDEROOT%\kde\bin
    set PATH=%PATH%;%KDEROOT%\kde\lib
    set PATH=%PATH%;%KDEROOT%\dbus\bin
    set PATH=%PATH%;%KDEROOT%\mc
    set PATH=%PATH%;%KDEROOT%\perl\bin
    set PATH=%PATH%;%KDEROOT%\strigi\bin
    set KDEDIRS=%KDEROOT%\kde
)

cmd /e:on /K "cd %KDEROOT%"
