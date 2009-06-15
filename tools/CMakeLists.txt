
add_subdirectory(create_hash_table)

# vc90 does not need this tool
if (NOT MSVC_VERSION EQUAL 1500)
	add_subdirectory(mt)
endif (NOT MSVC_VERSION EQUAL 1500)
add_subdirectory(png2ico)
add_subdirectory(svg2ico)
add_subdirectory(realpath)
