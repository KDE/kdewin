KDEWin is a supplementary library and provides supplementary tools which are 
required for compiling KDE applications on Windows. 

The library provides posix related definitions and functions which are not 
available on supported windows compilers and SDK's.
The tools (png2ico, svg2ico) are used by the cmake buildsystem to support 
windows application icons and to add specific vista manifests to applications
(mt for mingw and vs2005). 

history
-------
version 0.4.2
- fixed bug in kdewin32_fix_mode_string() not terminating string correclty

version 0.4.1
- added class LinkFile from kdebase/runtime/platform/win/kwinstartmenu to be usable in more kde code 

version 0.4.0
- removed 32 from project name to have room for future 64 bit versions too 
- renamed WINPOSIX_EXPORT, winposix_export.h to KDEWIN_EXPORT, kdewin_export.h 

-------
version 0.3.9
- fix realpath()

version 0.3.8
- fix unsetenv() return value

version 0.3.7
- add log1p for msvc (needed for koffice)
- some fixes
- update licensing informations to make ebn happy

version 0.3.6
- add a new png2ico which uses QtIcoHandler from Qt4.4 to write .ico files
- add directx headers for mingw
- add kdewin32_signal()
- add inet_ntop/pton from bind 9.4.2

version 0.3.5
- add rand_r for kgoldrunner

version 0.3.4
- add png2ico can now create rc file

version 0.3.3
- add create_hash_table tool

version 0.3.2
- add expm1, erf and erfc for msvc

version 0.3.1
- add preprocess define KDEWIN32_VERSION
- fix/add isnan, isinf, finite and signbit

version 0.3.0
- added tools png2ico and svg2ico for windows icons creating

version 0.2.7
- added (f)truncate
- fix asinh/acosh/atanh for msvc
- add 'extern "C"' for langinfo.h

version 0.2.6
- added utime 

version 0.2.5
- added upload function to build system

version 0.2.4
- added a lot of mathematical functions for msvc to compile kdeedu

version 0.2.3
- fixes for PSDK 6
- fix mmap (handles were not freed on error conditions)
- fix including pwd.h
- added char *strcasestr(const char *big, const char *little)

version 0.2
- fixed mmap and qt.3 QFile handle

