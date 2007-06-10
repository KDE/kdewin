set (NAME kdewin32)
set (VERSION 0.2.4)

project(${NAME})

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")

find_package(KDEWIN_INSTALLER)

if (NOT WIN32)
   message(FATAL_ERROR "This directory can only be built under Windows")
endif (NOT WIN32)

# where to look first for cmake modules, before ${CMAKE_ROOT}/Modules/ is checked
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/../cmake/modules")

if(NOT MSVC)
   add_subdirectory( examples)
endif(NOT MSVC)

add_subdirectory( tests)

include_directories(${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR})

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

# find the headers
file(GLOB _win_headers     include/*.h)
file(GLOB _arpa_headers    include/${_incDirPrefix}/arpa/*.h)
file(GLOB _asm_headers     include/${_incDirPrefix}/asm/*.h)
file(GLOB _net_headers     include/${_incDirPrefix}/net/*.h)
file(GLOB _netinet_headers include/${_incDirPrefix}/netinet/*.h)
file(GLOB _sys_headers     include/${_incDirPrefix}/sys/*.h)
file(GLOB _headers         include/${_incDirPrefix}/*.h)

add_definitions(-DUNICODE -DWIN32_LEAN_AND_MEAN )

set(win_LIB_SRCS
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
  )
endif(MSVC)

set(CMAKE_DEBUG_POSTFIX "d")
add_library(kdewin32 SHARED ${win_LIB_SRCS}
                            ${_arpa_headers}
                            ${_asm_headers}
                            ${_machine_headers}
                            ${_netinet_headers}
                            ${_net_headers}
                            ${_sys_headers}
                            ${_headers}
                            ${_win_headers}
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

install_files(/include/${_incDirPrefix}/arpa FILES ${_arpa_headers} )
install_files(/include/${_incDirPrefix}/asm FILES ${_asm_headers} )
install_files(/include/${_incDirPrefix}/machine FILES ${_machine_headers} )
install_files(/include/${_incDirPrefix}/netinet FILES ${_netinet_headers} )
install_files(/include/${_incDirPrefix}/net FILES ${_net_headers} )
install_files(/include/${_incDirPrefix}/sys FILES ${_sys_headers} )
install_files(/include/${_incDirPrefix} FILES ${_headers} )
install_files(/include FILES ${_win_headers} )
install_files(/doc/${NAME}-${VERSION} FILES readme.txt )

# write explorer wrappers
get_filename_component(CMAKE_BIN_PATH ${CMAKE_COMMAND} PATH)
if (MINGW)
    get_filename_component(MINGW_BIN_PATH ${CMAKE_CXX_COMPILER} PATH)
    write_file (${CMAKE_BINARY_DIR}/kdewin32-shell.bat "set PATH=${MINGW_BIN_PATH};${CMAKE_BIN_PATH};%PATH%\ncmd.exe")
else (MINGW)
    if (CMAKE_BUILD_TOOL STREQUAL  "nmake")
        get_filename_component(VC_BIN_PATH ${CMAKE_CXX_COMPILER} PATH)
        write_file (${CMAKE_BINARY_DIR}/kdewin32-shell.bat "set PATH=${CMAKE_BIN_PATH};%PATH%\ncall \"${VC_BIN_PATH}\\vcvars32.bat\"\ncmd.exe")
    else (CMAKE_BUILD_TOOL STREQUAL  "nmake")
        write_file (${CMAKE_BINARY_DIR}/kdewin32-sln.bat "set PATH=${CMAKE_BIN_PATH};%PATH%\nstart kdewin32.sln")
    endif (CMAKE_BUILD_TOOL STREQUAL  "nmake")
endif (MINGW)

#
# kdewin installer integration 
#
# @TODO: use temporay installation root 
# 
if (KDEWIN_INSTALLER_FOUND)
    if (MINGW)
        # wrapper to make package from explorer
        write_file(${CMAKE_BINARY_DIR}/make-kdewin-package.bat "rmdir /Q /S %CD%\\temp\n${CMAKE_COMMAND} -G \"MinGW Makefiles\" ${CMAKE_SOURCE_DIR} -DCMAKE_INSTALL_PREFIX=%CD%\\temp -DCMAKE_BUILD_TYPE=Debug\n${CMAKE_BUILD_TOOL} install\n${CMAKE_COMMAND} -G \"MinGW Makefiles\" ${CMAKE_SOURCE_DIR} -DCMAKE_INSTALL_PREFIX=%CD%\\temp -DCMAKE_BUILD_TYPE=Release\n${CMAKE_BUILD_TOOL} install\n${CMAKE_BUILD_TOOL} kdewinpackage\n")
        set (INSTALL_TYPE "mingw")
    else (MINGW)
        set (INSTALL_TYPE "msvc")
    endif (MINGW)
    add_custom_target(kdewinpackage
        COMMAND ${KDEWIN_PACKAGER} 
            -name ${NAME}
            -root ${CMAKE_INSTALL_PREFIX} 
            -srcroot ${CMAKE_SOURCE_DIR} 
            -srcexclude "emerge unused"
            -version ${VERSION} 
            -type ${INSTALL_TYPE}
            -notes "description"
#        DEPENDS install
    )
endif (KDEWIN_INSTALLER_FOUND)
