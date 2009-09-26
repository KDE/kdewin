
add_subdirectory(create_hash_table)

# vc90 does not need this tool
if (NOT MSVC_VERSION EQUAL 1500)
  # the name of the tool clashes with mt.exe from vc80
  # which in the end produces wrong / empty manifests...
  # and since vc80 isn't officially supported anymore we can
  # safely ignore it.
  if (NOT MSVC_VERSION EQUAL 1400)
	  add_subdirectory(mt)
  endif (NOT MSVC_VERSION EQUAL 1400)
endif (NOT MSVC_VERSION EQUAL 1500)
add_subdirectory(png2ico)
add_subdirectory(svg2ico)
add_subdirectory(realpath)
