project(pcre)

# currently missing:
# process pcre-config.in and libpcre.pc.in
# what about the .def - files?
# create / run tests
# check if all is installed correct

# do config checks
INCLUDE(CheckIncludeFile)
INCLUDE(CheckFunctionExists)
INCLUDE(CheckTypeSize)

SET(PCRE_MAJOR 7)
SET(PCRE_MINOR 0)
SET(PCRE_PRERELEASE 0)
SET(PCRE_DATE 20070919)

CHECK_INCLUDE_FILE(type_traits.h      HAVE_TYPE_TRAITS)
CHECK_INCLUDE_FILE(bits/type_traits.h HAVE_BITS_TYPE_TRAITS)

CHECK_FUNCTION_EXISTS(strerror        HAVE_STRERROR)
CHECK_FUNCTION_EXISTS(memmove         HAVE_MEMMOVE)
CHECK_FUNCTION_EXISTS(bcopy           HAVE_BCOPY)

CHECK_TYPE_SIZE("long long"           LONG_LONG)
CHECK_TYPE_SIZE("unsigned long long"  ULONG_LONG)

# some user defined options
SET(NEWLINE                 \\n      CACHE STRING "The value of NEWLINE determines the newline character.")
SET(LINK_SIZE               2        CACHE STRING "The value of LINK_SIZE determines the number of bytes used to store links as offsets within the compiled regex.")
SET(POSIX_MALLOC_THRESHOLD  10       CACHE STRING "see config.h.cmake")
SET(MATCH_LIMIT             10000000 CACHE STRING "see config.h.cmake")
SET(MATCH_LIMIT_RECURSION   10000000 CACHE STRING "see config.h.cmake")
SET(MAX_NAME_SIZE           32       CACHE STRING "see config.h.cmake")
SET(MAX_NAME_COUNT          10000    CACHE STRING "see config.h.cmake")
SET(MAX_DUPLENGTH           30000    CACHE STRING "see config.h.cmake")
OPTION(NO_RECURSE   "see config.h.cmake" OFF)
OPTION(EBDIC        "Enable if you are compiling for a system that uses EBCDIC instead of ASCII" OFF)

# create pcre.h.h
CONFIGURE_FILE(pcre.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/pcre.h)
# create config.h
CONFIGURE_FILE(config.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/config.h)
# create pcre_stringpiece.h
CONFIGURE_FILE(pcre_stringpiece.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/pcre_stringpiece.h)
# create pcrecpparg.h
CONFIGURE_FILE(pcrecpparg.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/pcrecpparg.h)

# enable/disable pcrecpp
OPTION(PCRECPP "Create pcrecpp library" ON)

# now build the libs
set(dftables_SRCS
    dftables.c
)

add_executable(dftables ${dftables_SRCS})

add_custom_command(
    OUTPUT ${CMAKE_BINARY_DIR}/pcre_chartables.c
    COMMAND dftables ${CMAKE_BINARY_DIR}/pcre_chartables.c
    DEPENDS dftables
)

set(pcre_SRCS
    ${CMAKE_BINARY_DIR}/pcre_chartables.c
    pcre_compile.c
    pcre_config.c
    pcre_dfa_exec.c
    pcre_exec.c
    pcre_fullinfo.c
    pcre_get.c
    pcre_globals.c
    pcre_info.c
    pcre_newline.c
    pcre_maketables.c
    pcre_ord2utf8.c
    pcre_refcount.c
    pcre_study.c
    pcre_tables.c
    pcre_try_flipped.c
    pcre_ucp_searchfuncs.c
    pcre_valid_utf8.c
    pcre_version.c
    pcre_xclass.c
)

set(CMAKE_DEBUG_POSTFIX "d")

add_definitions(-DDLL_EXPORT -D_CRT_SECURE_NO_DEPRECATE)

include_directories(${CMAKE_BINARY_DIR} ${CMAKE_SOURCE_DIR})

add_library(pcre SHARED pcreposix.c ${pcre_SRCS})
set_target_properties(pcre PROPERTIES PREFIX "")

add_library(pcreposix SHARED pcreposix.c)
target_link_libraries(pcreposix pcre)
set_target_properties(pcreposix PROPERTIES PREFIX "")

if(PCRECPP)
    add_library(pcrecpp SHARED pcrecpp.cc pcre_scanner.cc pcre_stringpiece.cc)
    target_link_libraries(pcrecpp pcre)
    if(MINGW)
        set_target_properties(pcrecpp PROPERTIES PREFIX "mingw-")
    endif(MINGW)
endif(PCRECPP)

add_executable(pcretest pcretest.c)
target_link_libraries(pcretest pcreposix)

add_executable(pcregrep pcregrep.c)
target_link_libraries(pcregrep pcreposix)

install_targets(/lib pcre)
install_targets(/lib pcreposix)
install_targets(/bin pcretest)
install_targets(/bin pcregrep)
install(FILES pcre.h pcreposix.h DESTINATION include)

FILE(GLOB html ${CMAKE_SOURCE_DIR}/doc/html/*)
FILE(GLOB man1 ${CMAKE_SOURCE_DIR}/doc/*.1)
FILE(GLOB man3 ${CMAKE_SOURCE_DIR}/doc/*.3)
if(PCRECPP)
    install_targets(/lib pcrecpp)
    install(FILES pcrecpp.h pcre_scanner.h DESTINATION include)
    install(FILES ${CMAKE_BINARY_DIR}/pcrecpparg.h
                  ${CMAKE_BINARY_DIR}/pcre_stringpiece.h
            DESTINATION include)
else(PCRECPP)
    # remove pcrecpp.3
    foreach(man ${man3})
        GET_FILENAME_COMPONENT(man_tmp ${man} NAME)
        if(NOT "man_tmp" STREQUAL "pcrecpp.3")
            set(man3_new ${man3} ${man})
        endif(NOT "man_tmp" STREQUAL "pcrecpp.3")
    endforeach(man ${man3})
    set(man3 ${man3_new})
endif(PCRECPP)

install(FILES ${man1} DESTINATION man/man1)
install(FILES ${man3} DESTINATION man/man3)
install(FILES ${html} DESTINATION doc/html)

# for uninstall target
CONFIGURE_FILE(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
  IMMEDIATE @ONLY)

# uninstall target
ADD_CUSTOM_TARGET(uninstall
  "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake")
