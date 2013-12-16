
if(NOT WINCE)
 add_subdirectory(create_hash_table)
endif(NOT WINCE)


if (MINGW)
  add_subdirectory(mt)
endif()
add_subdirectory(png2ico)
add_subdirectory(svg2ico)
add_subdirectory(realpath)
