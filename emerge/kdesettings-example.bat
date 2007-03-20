: here you set the base directory onder which the whole kde
: system will live
set KDEROOT=e:\mingwroot

: here you set the compiler to be used:
: mingw : use the mingw gcc compiler (recommended)
: msvc2005: use the microsoft visual studio 2005 c-compiler
set KDECOMPILER=mingw

: here you should set the path to your python installation
: this is needed, so that python will be found, when
: python scripts will be executed. by setting this here,
: you don´t have to change the environment settings of
: windows at all
set PYTHONPATH=e:\python25

set PATH=%PATH%;%PYTHONPATH%

: here you can set the download directory to another dir
: if you want, so you can share the same download dir between
: mingw and msvc
set DOWNLOADDIR=e:\distfiles

: here you can tell emerge in which dir you want to save the
: svn checkout of kde sources, and you can optionally
: set the svn.kde.org server instead of the anonsvn.kde.org
: one, so that you can directly commit your changes from the
: svn checkout from emerge, if you want.
set KDESVNDIR=e:\kdesvn
set KDESVNSERVER=svn://anonsvn.kde.org
set KDESVNUSERNAME=username
set KDESVNPASSWORD=password

@echo kdesettings.bat executed
@echo KDEROOT     : %KDEROOT%
@echo KDECOMPILER : %KDECOMPILER%
@echo KDESVNDIR   : %KDESVNDIR%
@echo PYTHONPATH  : %PYTHONPATH%
@echo DOWNLOADDIR : %DOWNLOADDIR%

