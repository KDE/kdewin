# KDEWIN_HAVE_... cmake variables are intended to enable or disable parts 
# in public header files depending on how kdewin is configured. 
# When a HAVE_... ist defined, KDEWIN_HAVE_... has to be set to zero. 
# KDEWIN_HAVE_... definitions have to be added to include/kdewin_export.h.cmake.  

if (MINGW)
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        set (MINGW64 1)
        set (MINGW_W64 1)
    else()
        set (MINGW32 1)
    endif()
endif (MINGW)
    
INCLUDE(CheckTypeSize)
INCLUDE(CheckFunctionExists)
INCLUDE(CheckSymbolExists)
INCLUDE(CheckCSourceCompiles)

SET(CMAKE_EXTRA_INCLUDE_FILES unistd.h)
CHECK_TYPE_SIZE(size_t KDEWIN_HAVE_SIZE_T)

CHECK_FUNCTION_EXISTS(usleep        KDEWIN_HAVE_USLEEP)
CHECK_FUNCTION_EXISTS(sleep         KDEWIN_HAVE_SLEEP)
CHECK_FUNCTION_EXISTS(fork          KDEWIN_HAVE_FORK)
CHECK_FUNCTION_EXISTS(truncate      KDEWIN_HAVE_TRUNCATE)
CHECK_C_SOURCE_COMPILES("#include <time.h>\nint main(int argc, char** argv) { localtime_r(0,0); }" KDEWIN_HAVE_LOCALTIME_R)
CHECK_C_SOURCE_COMPILES("#include <time.h>\nint main(int argc, char** argv) { gmtime_r(0,0); }" KDEWIN_HAVE_GMTIME_R)

# propagate detection into cmake package config file
if(KDEWIN_HAVE_LOCALTIME_R)
    set(KDEWIN_DEFINITIONS "${KDEWIN_DEFINITIONS} -DKDEWIN_NO_LOCALTIME_R")
endif()

if(KDEWIN_HAVE_GMTIME_R)
    set(KDEWIN_DEFINITIONS "${KDEWIN_DEFINITIONS} -DKDEWIN_NO_GMTIME_R")
endif()

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/kdewin_config.h)
install (FILES ${CMAKE_CURRENT_BINARY_DIR}/kdewin_config.h DESTINATION include)


