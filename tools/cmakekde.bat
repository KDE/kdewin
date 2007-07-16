rem helper script for calling CMake manually, you need to execute kdesettings before calling this script 
rem currently only for MinGW

@if not exist %KDEROOT% echo KDEROOT is not set, or the path does not exist!
@set PATH=%KDEROOT%\mingw\bin;%PATH%

cmake -G "MinGW Makefiles" -DCMAKE_INSTALL_PREFIX=%KDEROOT%\kde -DKDEWIN32_INSTALL_PREFIX=%KDEROOT%\kdewin32 -DWIN32LIBS_INSTALL_PREFIX=%KDEROOT%\kde\win32libs -DSTRIGI_INSTALL_PREFIX=%KDEROOT%\kde -DSHARED_MIME_INFO_INSTALL_PREFIX=%KDEROOT%\shared-mime-info -DWIN32LIBS_DIR=%KDEROOT%\win32libs %1 %2 %3 %4 %5 %6 %7 %8 %9 %10
