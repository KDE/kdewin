KDEWin is a supplementary library which are required for compiling 
KDE applications on Windows. 

The library provides posix related definitions and functions which are not 
available on supported windows compilers and SDK's.

history
-------
version 0.6.4
- Add KDEWIN_INCLUDES again, which may be used by client package configure checks
- Add KDEWIN_LIBRARIES again to have a common variable for the library target

version 0.6.3
- Add std::isnan() and std::isinf() for msvc < 2017

version 0.6.2
- Fix bug not been able to compile KDELibs4Support
- Fix cmake 3.5 warning related to target 'kdewin'

version 0.6.1
- Don't set msvc overoads for math functions with msvc2015+
- Port kdewin to using targets, which should hopefully allow us to avoid hardcoding paths
- Fix cross compiling kdelibs4support not finding kdewin provided kill function

version 0.6
- Moved out tool into kdewin-tools git repo
- Fix localtime_r and gmtime_r compile issue in client packages
- Fix build with MSVC 2015
- Include right header for utime.h

version 0.5.11
- Excludes some double definitions in MSVC 2013+.  Header used to successfully compile Krita.
- Set cmake_min_req to match kdelibs, as the comment says; fix build with cmake 2.8.9

version 0.5.10
- Add macro FIXWINH_NO_UNDEF_INTERFACE to let macro 'interface' be defined
  (see include/fixwinh.h for details)

version 0.5.9
- Only add S_I... constants if not present because mingw header 4.0 defines them
- mingw/include/time.h: Add KDEWIN_NO_LOCALTIME_R and KDEWIN_NO_GMTIME_R constants
  to exclude related methods which are already defined in newer mingw versions

version 0.5.8
- update readme
- install readme's in share/doc/kdewin...-<version>, which is the correct location

version 0.5.7
- Add a cmake config file for kdewin-tools.
- fix bug related to urlmon include
- additional compiler support: intel compiler, MSVC x64, 2012 and 2013
- dont build mt on msvc
- add Windows Driver Kit headers

version 0.5.6
- fixes (see git log)

version 0.5.5
- removed obsolate kdewin32 library
- splitted source to be able to build separate binary packages like 
  kdewin (without qt), kdewin-tools and kdewin-qt/kde

version 0.5.4
- use the dirent implementation from dbus which is threadsave for wince and
- uses more native functions on windows.
- remove some warnings in the wince build
- fix gethostname for wince
- fame goes to Marcus Brinkmann, who found it and fixed it
- fix symlink for wince
- use strncpy instead
- fix size_t for win64
- Adding a STATIC_LIBRARY build option to kdewin, akonadi, kdelibs and kdepimlibs
- do not build and install dbghelp for mingw_w32
- fixed the static build
- made it possible to link it staticly
- set wince to standard link static
- Update CMakeLists.txt to reflect the renaming of qt folder to kde.
- tenamed qt to kde to reflect namespace
- add subdirectory dbghelp only if on mingw32
- added MINGW_W32 option for mingw-w32 compiler support
- be more silent
- bug fix: MINGW32/MINGW64 should only be set when using mingw compilers
- fixed mingw header
- fixed some stuff for wince
- add SOL_IPV6 for programs which need it (like libktorrent)
- wince support

version 0.5.3
- added wbemuuid library

version 0.5.2
- added dbghelp library

version 0.5.1
- splitted into kdewin library without qt and kdewin-qt library 
- fixed  x64 mingw compile problems 

version 0.5.1
- splitted into kdewin library without qt and kdewin-qt library 
- fixed  x64 mingw compile problems 

version 0.5.0
- initial x64 support (thanks to Patrick von Reth)

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

