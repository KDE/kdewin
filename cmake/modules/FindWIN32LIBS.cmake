# - Try to find the directory in which the win32 related libraries lives
# 
# used environment vars 
#  WIN32LIBS_DIR  - WIN32LIBS root dir 
#
# this will define
#  WIN32LIBS_FOUND - system has WIN32LIBS
#  WIN32LIBS_DIR - the WIN32LIBS root installation dir
#
# Copyright (c) 2007, Ralf Habacker, <ralf.habacker@freenet.de>
#
# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.

if (WIN32)
  IF (NOT WIN32LIBS_DIR)
    # check for enviroment variable
    file(TO_CMAKE_PATH "$ENV{WIN32LIBS_DIR}" WIN32LIBS_DIR)
    if(NOT WIN32LIBS_DIR)
      file(TO_CMAKE_PATH "$ENV{PROGRAMFILES}" _progFiles)
      if (MINGW)
        set (DIR "kdewin-mingw")
      else (MINGW)
        set (DIR "kdewin-msvc")
      endif (MINGW)
      
      # search in the default program install folder
      find_file(WIN32LIBS_DIR_tmp ${DIR} kdewin32 win32libs gnuwin32
      PATHS
        "${_progFiles}"
      )
      set (WIN32LIBS_DIR ${WIN32LIBS_DIR_tmp})
    endif (NOT WIN32LIBS_DIR)
    if (WIN32LIBS_DIR)
      message(STATUS "Found windows supplementary package location: ${WIN32LIBS_DIR}")
    endif (WIN32LIBS_DIR)
  endif (NOT WIN32LIBS_DIR)

  # this must be set every time 
  if (WIN32LIBS_DIR)
    # add include path and library to all targets, this is required because 
    # cmake's 2.4.6 FindZLib.cmake does not use CMAKE_REQUIRED... vars
    set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} ${WIN32LIBS_DIR}/include)
    set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} ${WIN32LIBS_DIR}/lib)
     
    set (WIN32LIBS_FOUND 1)
  else(WIN32LIBS_DIR)
    message(STATUS "Could not find the location of the windows supplementary packages which is \n"
                    "\t\tenvironment variable WIN32LIBS_DIR\n"
                    "\t\t<ProgramFiles>/${DIR}\n"
                    "\t\t<ProgramFiles>/kdewin32\n" 
                    "\t\t<ProgramFiles>/win32libs\n"
                    "\t\t<ProgramFiles>/gnuwin32\n"
    )
   endif(WIN32LIBS_DIR)
  
endif (WIN32)
