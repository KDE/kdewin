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

@echo kdesettings.bat executed
@echo KDEROOT     : %KDEROOT%
@echo KDECOMPILER : %KDECOMPILER%
@echo PYTHONPATH  : %PYTHONPATH%

