set (NAME kdewin32)
set (KDEWIN32_VERSION 0x000309)
set (KDEWIN32_VERSION_STR 0.3.9)
# stay in sync with kdelibs
cmake_minimum_required(VERSION 2.6.2)

project(${NAME})

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/modules")

if (NOT WIN32)
   message(FATAL_ERROR "This directory can only be built under Windows")
endif (NOT WIN32)
OPTION(BUILD_TESTS "build test applications " OFF)
OPTION(BUILD_EXAMPLES "build example applications " OFF)
OPTION(BUILD_TOOLS "build tools" ON)

find_package(WIN32LIBS)
find_package(KDEWIN_Packager)
find_package(WinSCP)

set (EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set (LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

include_directories(${kdewin32_SOURCE_DIR}
                    ${kdewin32_SOURCE_DIR}/include
                    ${kdewin32_BINARY_DIR}
                    ${kdewin32_BINARY_DIR}/include
                    )

if(MINGW)
   # we are using mingw, so do whatever required for mingw
   include_directories(${kdewin32_SOURCE_DIR}/include/mingw )
   set(_incDirPrefix mingw)
else (MINGW)
   # we are using msvc, so do whatever required for msvc
   include_directories(${kdewin32_SOURCE_DIR}/include/msvc )
   # disable msvc callings to use the _s versions
   add_definitions( -D_CRT_SECURE_NO_DEPRECATE
                    -D_CRT_NONSTDC_NO_DEPRECATE
                  )
   set(_incDirPrefix msvc)
endif(MINGW)

if (BUILD_EXAMPLES AND NOT MSVC)
   add_subdirectory( examples)
endif(BUILD_EXAMPLES AND NOT MSVC)

add_subdirectory(3rdparty)
if (BUILD_TOOLS)
    add_subdirectory(tools)
endif(BUILD_TOOLS)
if (BUILD_TESTS)
    add_subdirectory(tests)
endif(BUILD_TESTS)

configure_file(${kdewin32_SOURCE_DIR}/include/winposix_export.h.cmake
               ${kdewin32_BINARY_DIR}/include/winposix_export.h)

add_definitions(-DUNICODE -DWIN32_LEAN_AND_MEAN )

set(win_LIB_SRCS
   src/bind/inet_ntop.c
   src/bind/inet_pton.c
   src/dirent.c
   src/errno.c
#not implemented: src/fcntl.c
   src/fsync.c
   src/getenv.c
   src/grp.c
   src/inet.c
   src/kde_file_win.c
   src/mmap.c
   src/nl_langinfo.c
   src/net.c
   src/pwd.c
   src/realpath.c
   src/resource.c
   src/signal.c
   src/stdlib.c
   src/string.c
   src/strptime.c
   src/syslog.c
   src/time.c
   src/uname.c
   src/unistd.c
#   src/io.c
   src/dummy.c
   )
if(MSVC)
  set(win_LIB_SRCS ${win_LIB_SRCS}
      src/stdio.c
      src/math/tgamma.c
      src/math/tgammaf.c
      src/math/lgamma.c
      src/math/lgammaf.c
      src/math/math.c
      src/math/expm1.c
      src/math/erfl.c
      src/math/s_erf.c
      src/math/sf_erf.c
      src/math/e_remainder.c
  )
endif(MSVC)

set(CMAKE_DEBUG_POSTFIX "d")
add_library(kdewin32 SHARED ${win_LIB_SRCS})
target_link_libraries(kdewin32 advapi32 shell32 ws2_32 )
set_target_properties(kdewin32 PROPERTIES DEFINE_SYMBOL MAKE_KDEWIN32_LIB )
set_target_properties(kdewin32 PROPERTIES VERSION ${KDEWIN32_VERSION_STR} )

if(MSVC)
  # 4244: 'argument' : conversion from 'type1' to 'type2', possible loss of data
  # 4305: 'identifier' : truncation from 'type1' to 'type2'
  set_target_properties(kdewin32 PROPERTIES
      COMPILE_FLAGS "-wd4244 -wd4305"
  )
endif(MSVC)

install(TARGETS kdewin32
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
  ARCHIVE DESTINATION lib
)

install(DIRECTORY include/${_incDirPrefix}                  DESTINATION /include PATTERN ".svn" EXCLUDE)
install(FILES include/fixwinh.h include/kde_file_win.h      DESTINATION /include)
install(FILES ${CMAKE_BINARY_DIR}/include/winposix_export.h DESTINATION /include)
install(FILES readme.txt                                    DESTINATION /doc/${NAME}-${KDEWIN32_VERSION_STR})
if(MINGW)
    install(DIRECTORY include/directx                       DESTINATION /include/${_incDirPrefix} PATTERN ".svn" EXCLUDE)
endif(MINGW)

include(Win32Macros)
addExplorerWrapper(${NAME})

# kdewin package support 
install(FILES cmake/modules/FindKDEWIN_Packager.cmake       DESTINATION /share/apps/cmake/modules)
if (KDEWIN_PACKAGER_FOUND)
    KDEWIN_PACKAGER(${NAME} ${VERSION} "${NAME} supplementary library" "-srcexclude \"emerge unused\"")
endif (KDEWIN_PACKAGER_FOUND)

if (WINSCP_FOUND)
    KDEWIN_UPLOAD("${NAME}-*-${VERSION}*.zip" kde-windows download.cegit.de /home/kde-windows/kde-windows/kdesupport/single/)
endif (WINSCP_FOUND)
