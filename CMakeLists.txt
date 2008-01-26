set (NAME kdewin32)
set (KDEWIN32_VERSION 0x000305)

project(${NAME})

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/modules")

if (NOT WIN32)
   message(FATAL_ERROR "This directory can only be built under Windows")
endif (NOT WIN32)

find_package(WIN32LIBS)
find_package(KDEWIN_Packager)
find_package(WinScp)

set (EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set (LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

include_directories(${CMAKE_SOURCE_DIR}
                    ${CMAKE_BINARY_DIR}
                    ${CMAKE_BINARY_DIR}/include
                    )

if(MINGW)
   # we are using mingw, so do whatever required for mingw
   include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/include/mingw )
   set(_incDirPrefix mingw)
else (MINGW)
   # we are using msvc, so do whatever required for msvc
   include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/include/msvc )
   # disable msvc callings to use the _s versions
   add_definitions( -D_CRT_SECURE_NO_DEPRECATE
                    -D_CRT_NONSTDC_NO_DEPRECATE
                  )
   set(_incDirPrefix msvc)
endif(MINGW)

if(NOT MSVC)
   add_subdirectory( examples)
endif(NOT MSVC)

add_subdirectory(3rdparty)
add_subdirectory(tools)
add_subdirectory(tests)
configure_file(${CMAKE_SOURCE_DIR}/include/winposix_export.h.cmake ${CMAKE_BINARY_DIR}/include/winposix_export.h)

# find the headers
file(GLOB _source_headers  include/*.h)
file(GLOB _bin_headers     ${CMAKE_BINARY_DIR}/include/*.h)
file(GLOB _arpa_headers    include/${_incDirPrefix}/arpa/*.h)
file(GLOB _asm_headers     include/${_incDirPrefix}/asm/*.h)
file(GLOB _gl_headers      include/${_incDirPrefix}/GL/*.h)
file(GLOB _machine_headers include/${_incDirPrefix}/machine/*.h)
file(GLOB _net_headers     include/${_incDirPrefix}/net/*.h)
file(GLOB _netinet_headers include/${_incDirPrefix}/netinet/*.h)
file(GLOB _sys_headers     include/${_incDirPrefix}/sys/*.h)
file(GLOB _headers         include/${_incDirPrefix}/*.h)
file(GLOB _directx_headers include/directx/*.h)
file(GLOB _directx_idls    include/directx/*.idl)

add_definitions(-DUNICODE -DWIN32_LEAN_AND_MEAN )

set(win_LIB_SRCS
   src/bind/inet_ntop.c
   src/bind/inet_pton.c
   src/dirent.c
   src/errno.c
   src/fcntl.c
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
   )
if(MSVC)
  set(win_LIB_SRCS ${win_LIB_SRCS}
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
add_library(kdewin32 SHARED ${win_LIB_SRCS}
                            ${_arpa_headers}
                            ${_asm_headers}
                            ${_gl_headers}
                            ${_machine_headers}
                            ${_net_headers}
                            ${_netinet_headers}
                            ${_sys_headers}
                            ${_headers}
                            ${_bin_headers}
                            ${_source_headers}
                            )
target_link_libraries(kdewin32 advapi32 shell32 ws2_32 )
set_target_properties(kdewin32 PROPERTIES DEFINE_SYMBOL MAKE_KDEWIN32_LIB )
# which version number should kdewin32 get ? Does version numbers for libs actually exist on windows ? Alex
set_target_properties(kdewin32 PROPERTIES
    VERSION 5.0.0
    SOVERSION 5
)
if(MSVC)
  # 4244: 'argument' : conversion from 'type1' to 'type2', possible loss of data
  # 4305: 'identifier' : truncation from 'type1' to 'type2'
  set_target_properties(kdewin32 PROPERTIES
      COMPILE_FLAGS "-wd4244 -wd4305"
  )
endif(MSVC)

install_targets(/lib kdewin32 )

install_files(/include/${_incDirPrefix}/arpa    FILES ${_arpa_headers} )
install_files(/include/${_incDirPrefix}/asm     FILES ${_asm_headers} )
install_files(/include/${_incDirPrefix}/machine FILES ${_machine_headers} )
install_files(/include/${_incDirPrefix}/netinet FILES ${_netinet_headers} )
install_files(/include/${_incDirPrefix}/sys     FILES ${_sys_headers} )
install_files(/include/${_incDirPrefix}         FILES ${_headers} )
install_files(/include                          FILES ${_bin_headers} )
install_files(/include                          FILES ${_source_headers} )
install_files(/doc/${NAME}-${VERSION}           FILES readme.txt )
if(MINGW)
  install_files(/include/${_incDirPrefix}/directx FILES ${_directx_headers} ${_directx_idls} )
  install_files(/include/${_incDirPrefix}/net     FILES ${_net_headers} )
endif(MINGW)
if(MSVC)
  install_files(/include/${_incDirPrefix}/GL      FILES ${_gl_headers} )
endif(MSVC)

include(Win32Macros)
addExplorerWrapper(${NAME})

# kdewin package support 
install_files(/share/apps/cmake/modules FILES cmake/modules/FindKDEWIN_Packager.cmake)
if (KDEWIN_PACKAGER_FOUND)
    KDEWIN_PACKAGER(${NAME} ${VERSION} "${NAME} supplementary library" "-srcexclude \"emerge unused\"")
endif (KDEWIN_PACKAGER_FOUND)

if (WINSCP_FOUND)
    KDEWIN_UPLOAD("${NAME}-*-${VERSION}*.zip" kde-windows download.cegit.de /home/kde-windows/kde-windows/kdesupport/single/)
endif (WINSCP_FOUND)
