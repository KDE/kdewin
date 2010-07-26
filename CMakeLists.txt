set (NAME kdewin)
set (KDEWIN_VERSION 0x000503)
set (KDEWIN_VERSION_STR 0.5.3)
# stay in sync with kdelibs
cmake_minimum_required(VERSION 2.6.2)

project(${NAME})

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/modules")

if (NOT WIN32)
   message(FATAL_ERROR "This directory can only be built under Windows")
endif (NOT WIN32)
OPTION(BUILD_TESTS "build test applications " OFF)
OPTION(BUILD_EXAMPLES "build example applications " OFF)
OPTION(BUILD_TOOLS "build tools" OFF)
OPTION(BUILD_QT_LIB "build qt based libraries " ON)
OPTION(BUILD_BASE_LIB "build base libraries " ON)
OPTION(BUILD_BASE_LIB_WITH_QT "build base library with qt part included" ON)

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
if (BUILD_QT_LIB OR BUILD_BASE_LIB_WITH_QT OR BUILD_TOOLS)
    # used by tools 
    find_package(Qt4 REQUIRED)
endif (BUILD_QT_LIB OR BUILD_BASE_LIB_WITH_QT OR BUILD_TOOLS)

message(STATUS ${test_INCLUDE_DIRS} ${test_LIBRARY})

set (EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set (LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

include_directories(
    ${kdewin_SOURCE_DIR}
    ${kdewin_SOURCE_DIR}/include
    ${kdewin_SOURCE_DIR}/include/kdewin
    ${kdewin_BINARY_DIR}
    ${kdewin_BINARY_DIR}/include
)

if(MINGW)
   # we are using mingw, so do whatever required for mingw
   set (target_include_directories ${kdewin_SOURCE_DIR}/include/mingw )
else (MINGW)
   # we are using msvc, so do whatever required for msvc
   set (target_include_directories ${kdewin_SOURCE_DIR}/include/msvc )
endif(MINGW)

if(WINCE)
    find_package(Wcecompat REQUIRED)
	set (target_include_directories ${target_include_directories} ${WCECOMPAT_INCLUDE_DIR})
    set(CMAKE_REQUIRED_INCLUDES ${CMAKE_REQUIRED_INCLUDES} ${WCECOMPAT_INCLUDE_DIR})
    set(CMAKE_REQUIRED_LIBRARIES ${CMAKE_REQUIRED_LIBRARIES} ${WCECOMPAT_LIBRARIES})
endif(WINCE)

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
   add_subdirectory( examples)
endif(BUILD_EXAMPLES AND NOT MSVC)

add_subdirectory(3rdparty)

if (BUILD_TOOLS)
    add_subdirectory(tools)
endif(BUILD_TOOLS)

if (BUILD_TESTS)
    add_subdirectory(tests)
endif(BUILD_TESTS)

if (BUILD_BASE_LIB AND MINGW32)
    add_subdirectory(dbghelp)
endif (BUILD_BASE_LIB AND MINGW32)

if (MINGW64 OR MINGW_W32)
    add_subdirectory(wbem)
endif (MINGW64 OR MINGW_W32)

include(Win32Macros)
addExplorerWrapper(${NAME})

install(FILES readme.txt  DESTINATION doc/${NAME}-${KDEWIN_VERSION_STR})

# kdewin package support 
install(FILES cmake/modules/FindKDEWIN_Packager.cmake       DESTINATION share/apps/cmake/modules)
if (KDEWIN_PACKAGER_FOUND)
    KDEWIN_PACKAGER(${NAME} ${VERSION} "${NAME} supplementary library" "-srcexclude \"emerge unused\"")
endif (KDEWIN_PACKAGER_FOUND)


