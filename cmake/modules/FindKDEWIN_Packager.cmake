#
# find KDEWIN installer. 
# 
# This scripts supports the following options 
# 
#  -  install KDEWIN installer in <default application dir>/kdewin-installer
#  -  set the environment variable KDEWIN_INSTALLER_DIR=<path>
#  -  add -DKDEWIN_INSTALLER_DIR=<path> to the cmake command line 
#
# Copyright (c) 2006, Ralf Habacker
#
# Redistribution and use is allowed according to the terms of the BSD license.
#

if (WIN32)
    if(NOT KDEWIN_PACKAGER_DIR)
        # check for enviroment variable
    	file(TO_CMAKE_PATH "$ENV{KDEWIN_PACKAGER_DIR}" KDEWIN_PACKAGER_DIR)
    	if(NOT KDEWIN_PACKAGER_DIR)
    		# search in the default program install folder
    		file(TO_CMAKE_PATH "$ENV{PROGRAMFILES}" _progFiles)
    		find_file(KDEWIN_PACKAGER_DIR_tmp kdewin-packager kdewin-installer
       			PATHS
       			"${_progFiles}"
    		)
    		set(KDEWIN_PACKAGER_DIR ${KDEWIN_PACKAGER_DIR_tmp})
    	endif(NOT KDEWIN_PACKAGER_DIR)
    endif(NOT KDEWIN_PACKAGER_DIR)
        
    if (KDEWIN_PACKAGER_DIR)
    
        find_program(KDEWIN_PACKAGER_EXECUTABLE kdewin-packager
            PATHS
                ${KDEWIN_PACKAGER_DIR}/bin
        )
        
       set(KDEWIN_PACKAGER_FOUND TRUE)
    else (KDEWIN_PACKAGER_DIR)
       set(KDEWIN_PACKAGER_FOUND)
    endif (KDEWIN_PACKAGER_DIR)
    
    if (KDEWIN_PACKAGER_FOUND)
      if (NOT KDEWIN_PACKAGER_FIND_QUIETLY)
        message(STATUS "Found KDEWIN Packager: ${KDEWIN_PACKAGER_DIR}")
      endif (NOT KDEWIN_PACKAGER_FIND_QUIETLY)
    else (KDEWIN_PACKAGER_FOUND)
      if (KDEWIN_PACKAGER_FIND_REQUIRED)
        message(FATAL_ERROR "Could NOT find KDEWIN PAckager")
      endif (KDEWIN_PACKAGER_FIND_REQUIRED)
    endif (KDEWIN_PACKAGER_FOUND)

endif (WIN32)

MACRO (KDEWIN_PACKAGER _name _version _notes _options)
    if (KDEWIN_PACKAGER_FOUND)
        if (MSVC)
            add_custom_target(kdewin_package
                COMMAND ${CMAKE_COMMAND} 
                    -P ${CMAKE_BINARY_DIR}/cmake_install.cmake -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/temp
                COMMAND ${KDEWIN_PACKAGER_EXECUTABLE} 
                    -name ${_name}
                    -root ${CMAKE_BINARY_DIR}/temp
                    -srcroot ${CMAKE_SOURCE_DIR}
                    -version ${_version} 
                    -notes "${_notes}"
                    -type msvc
                    ${_options}               
                # FIXME: cleanup does not work 
                #COMMAND rmdir /Q /S ${CMAKE_BINARY_DIR}\temp
            )
        else (MSVC)
            add_custom_target(kdewin_package
                COMMAND ${CMAKE_COMMAND} 
                    -P ${CMAKE_BINARY_DIR}/cmake_install.cmake -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/temp
                COMMAND ${KDEWIN_PACKAGER_EXECUTABLE} 
                    -name ${_name}
                    -root ${CMAKE_BINARY_DIR}/temp
                    -srcroot ${CMAKE_SOURCE_DIR}
                    -version ${_version} 
                    -notes "${_notes}"
                    -type mingw
                    ${_options}               
                # FIXME: cleanup does not work 
                #COMMAND rmdir /Q /S ${CMAKE_BINARY_DIR}\temp
            )
        endif (MSVC)
    endif (KDEWIN_PACKAGER_FOUND)
ENDMACRO (KDEWIN_PACKAGER)


