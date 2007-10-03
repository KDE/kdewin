set (EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

configure_file(png2ico/png2ico.exe ${CMAKE_BINARY_DIR}/bin/png2ico.exe COPY_ONLY)
install(FILES png2ico/png2ico.exe DESTINATION bin)

