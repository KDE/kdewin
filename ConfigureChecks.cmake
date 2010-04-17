# KDEWIN_HAVE_... cmake variables are intended to enable or disable parts 
# in public header files depending on how kdewin is configured. 
# When a HAVE_... ist defined, KDEWIN_HAVE_... has to be set to zero. 
# KDEWIN_HAVE_... definitions have to be added to include/kdewin_export.h.cmake.  

if(MINGW)
	# set MINGW32 or MINGW64
	INCLUDE(CheckMingwVersion)
endif(MINGW)

INCLUDE(CheckTypeSize)
INCLUDE(CheckFunctionExists)
CHECK_TYPE_SIZE(size_t HAVE_SIZE_T)

if(HAVE_SIZE_T)
  add_definitions(-DHAVE_SIZE_T)
endif(HAVE_SIZE_T)

CHECK_FUNCTION_EXISTS(usleep      HAVE_USLEEP)
set (KDEWIN_HAVE_USLEEP 1)
if(HAVE_USLEEP)
  set (KDEWIN_HAVE_USLEEP)
  add_definitions(-DHAVE_USLEEP)
endif(HAVE_USLEEP)
