# stay in sync with kdelibs
cmake_minimum_required(VERSION 2.8.9)
set (NAME kdewin)
set(KDEWin_VERSION_MAJOR 0)
set(KDEWin_VERSION_MINOR 6)
set(KDEWin_VERSION_PATCH 1)

# calculate the version in an ugly way
math(EXPR KDEWIN_VERSION '1000000+${KDEWin_VERSION_MAJOR}*10000+${KDEWin_VERSION_MINOR}*100+${KDEWin_VERSION_PATCH}')
string(SUBSTRING ${KDEWIN_VERSION} 1 6 KDEWIN_VERSION)
set(KDEWIN_VERSION "0x${KDEWIN_VERSION}")
set (KDEWIN_VERSION_STR ${KDEWin_VERSION_MAJOR}.${KDEWin_VERSION_MINOR}.${KDEWin_VERSION_PATCH})
if (POLICY CMP0020)
   cmake_policy(SET CMP0020 NEW)
endif()

project(${NAME})

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/modules")

if (NOT WIN32)
   message(FATAL_ERROR "This directory can only be built under Windows")
endif (NOT WIN32)
OPTION(BUILD_TESTS "build test applications " OFF)
OPTION(BUILD_EXAMPLES "build example applications " OFF)
OPTION(BUILD_QT_LIB "build qt based libraries " ON)
OPTION(BUILD_BASE_LIB "build base libraries " ON)
OPTION(BUILD_BASE_LIB_WITH_QT "build base library with qt part included" ON)
OPTION(STATIC_LIBRARY "Build kdewin as a static library." OFF)

# there are three mingw compilers 
# compiler     cmake variables 
# mingw4      MINGW32
# mingw-w32   MINGW32  MINGW_W32
# mingw-w64   MINGW64  MINGW_W64
# the last one could be detected automatically 
# the second one is selected with the following option 
# the first one is selected by cmake as default
OPTION(MINGW_W32 "build for mingw-w32 " OFF)

find_package(KDEWIN_Packager)
if (BUILD_QT_LIB OR BUILD_BASE_LIB_WITH_QT)
    # used by tools 
    find_package(Qt5Transitional REQUIRED Gui)
endif (BUILD_QT_LIB OR BUILD_BASE_LIB_WITH_QT)

set (EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set (LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

set( kdewin_INCLUDES
    ${kdewin_SOURCE_DIR}
    ${kdewin_SOURCE_DIR}/include
    ${kdewin_SOURCE_DIR}/include/kdewin
    ${kdewin_BINARY_DIR}
    ${kdewin_BINARY_DIR}/include
)

if(MINGW)
   # we are using mingw, so do whatever required for mingw
   set( kdewin_INCLUDES ${kdewin_INCLUDES} ${kdewin_SOURCE_DIR}/include/mingw )
else (MINGW)
   # we are using msvc, so do whatever required for msvc
   set( kdewin_INCLUDES ${kdewin_INCLUDES} ${kdewin_SOURCE_DIR}/include/msvc )
endif(MINGW)

if(WINCE)
    find_package(Wcecompat REQUIRED)
	set( kdewin_INCLUDES ${kdewin_INCLUDES} ${WCECOMPAT_INCLUDE_DIR})
    set(CMAKE_REQUIRED_INCLUDES ${CMAKE_REQUIRED_INCLUDES} ${WCECOMPAT_INCLUDE_DIR})
    set(CMAKE_REQUIRED_LIBRARIES ${CMAKE_REQUIRED_LIBRARIES} ${WCECOMPAT_LIBRARIES})
    set(STATIC_LIBRARY ON)
endif(WINCE)

if(STATIC_LIBRARY)
  set(LIBRARY_TYPE STATIC)
  add_definitions(-DKDEWIN_STATIC_LIBS)
  set(KDEWIN_DEFINITIONS "${KDEWIN_DEFINITIONS} -DKDEWIN_STATIC_LIBS")
  message(STATUS "Building kdewin as a static library")
else(STATIC_LIBRARY)
  set(LIBRARY_TYPE SHARED)
endif(STATIC_LIBRARY)

INCLUDE(ConfigureChecks.cmake)

configure_file(${kdewin_SOURCE_DIR}/include/kdewin_export.h.cmake
               ${kdewin_BINARY_DIR}/include/kdewin_export.h)

               
if (BUILD_QT_LIB OR BUILD_BASE_LIB_WITH_QT)
   add_subdirectory(kde)
endif (BUILD_QT_LIB OR BUILD_BASE_LIB_WITH_QT)

if (BUILD_BASE_LIB OR BUILD_BASE_LIB_WITH_QT)
   add_subdirectory(src)
endif (BUILD_BASE_LIB OR BUILD_BASE_LIB_WITH_QT)

if (BUILD_EXAMPLES AND NOT MSVC)
   add_subdirectory(examples)
endif(BUILD_EXAMPLES AND NOT MSVC)

if (BUILD_TESTS)
    add_subdirectory(tests)
endif(BUILD_TESTS)

if (BUILD_BASE_LIB AND MINGW32 AND NOT MINGW_W32)
    add_subdirectory(dbghelp)
endif (BUILD_BASE_LIB AND MINGW32 AND NOT MINGW_W32)

if (MINGW64 OR MINGW_W32)
    add_subdirectory(wbem)
endif (MINGW64 OR MINGW_W32)

include(Win32Macros)
addExplorerWrapper(${NAME})

if(MSVC)
    set(MSSDK_DIR_CMD "file(TO_CMAKE_PATH \"\$ENV{MSSDK}\" MSSDK_DIR)")
    set(KDEWIN_PLATFORM_INCLUDES "\${KDEWIN_INCLUDE_DIR}/msvc")
else()
    set(KDEWIN_PLATFORM_INCLUDES "\${KDEWIN_INCLUDE_DIR}/mingw")
endif()

if (BUILD_BASE_LIB OR BUILD_BASE_LIB_WITH_QT)
    configure_file(${CMAKE_SOURCE_DIR}/cmake/modules/KDEWinConfig.cmake.in ${CMAKE_BINARY_DIR}/KDEWinConfig.cmake @ONLY)
    configure_file(${CMAKE_SOURCE_DIR}/cmake/modules/KDEWinConfigVersion.cmake.in ${CMAKE_BINARY_DIR}/KDEWinConfigVersion.cmake @ONLY)
    install(FILES ${CMAKE_BINARY_DIR}/KDEWinConfig.cmake ${CMAKE_BINARY_DIR}/KDEWinConfigVersion.cmake DESTINATION lib/cmake/KDEWin)
    install(EXPORT KDEWin_targets FILE KDEWinTargets.cmake DESTINATION lib/cmake/KDEWin)
    install(FILES readme.txt  DESTINATION share/doc/kdewin-${KDEWIN_VERSION_STR})
    install(FILES cmake/modules/FindKDEWin.cmake  DESTINATION share/apps/cmake/modules)
    install(FILES cmake/modules/FindKDEWIN32.cmake  DESTINATION share/apps/cmake/modules)
endif()

# kdewin package support 
if (BUILD_BASE_LIB OR BUILD_BASE_LIB_WITH_QT)
    install(FILES cmake/modules/FindKDEWIN_Packager.cmake       DESTINATION share/apps/cmake/modules)
endif (BUILD_BASE_LIB OR BUILD_BASE_LIB_WITH_QT)

if (KDEWIN_PACKAGER_FOUND)
    KDEWIN_PACKAGER(${NAME} ${KDEWIN_VERSION} "${NAME} supplementary library" "-srcexclude \"emerge unused\"")
endif (KDEWIN_PACKAGER_FOUND)


