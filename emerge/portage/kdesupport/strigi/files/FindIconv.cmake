# - Try to find Iconv 
# Once done this will define 
# 
#  ICONV_FOUND - system has Iconv 
#  ICONV_INCLUDE_DIR - the Iconv include directory 
#  ICONV_LIBRARY - Link these to use Iconv 
# 
 
FIND_PATH(ICONV_INCLUDE_DIR iconv.h 
  /usr/include 
  /usr/local/include
  ${WIN32LIBS_INSTALL_PREFIX}/include
) 
 
FIND_LIBRARY(ICONV_LIBRARIES NAMES iconv c
  PATHS 
  /usr/lib/
  /usr/local/lib
  ${WIN32LIBS_INSTALL_PREFIX}/bin
) 
 
IF(ICONV_INCLUDE_DIR AND ICONV_LIBRARIES) 
   SET(Iconv_FOUND TRUE) 
ENDIF(ICONV_INCLUDE_DIR AND ICONV_LIBRARIES) 
 
IF(Iconv_FOUND) 
  IF(NOT Iconv_FIND_QUIETLY) 
    MESSAGE(STATUS "Found Iconv: ${ICONV_LIBRARIES}") 
  ENDIF(NOT Iconv_FIND_QUIETLY) 
ELSE(Iconv_FOUND) 
  IF(Iconv_FIND_REQUIRED) 
    MESSAGE(FATAL_ERROR "Could not find Iconv") 
  ENDIF(Iconv_FIND_REQUIRED) 
ENDIF(Iconv_FOUND) 

MARK_AS_ADVANCED(
  ICONV_INCLUDE_DIR
  ICONV_LIBRARIES
)
