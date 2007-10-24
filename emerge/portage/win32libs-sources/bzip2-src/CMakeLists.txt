project(bzip2)

set(bzip2_lib_SRCS
    blocksort.c
    huffman.c
    crctable.c
    randtable.c
    compress.c
    decompress.c
    bzlib.c
    libbz2.def
)

set(CMAKE_DEBUG_POSTFIX "d")
add_definitions(-D_CRT_SECURE_NO_DEPRECATE -D_CRT_NONSTDC_NO_DEPRECATE)

add_library(bzip2 SHARED ${bzip2_lib_SRCS})
set_target_properties(bzip2 PROPERTIES PREFIX "")

add_executable(bzip2recover bzip2recover.c)
target_link_libraries(bzip2recover bzip2)

set(bzip2_scripts
    bzdiff
    bzgrep
    bzmore
)
set(bzip2_docs
    bzip2.txt
    manual.pdf
)
set(bzip2_html
    manual.html
)

FILE(GLOB man1 ${bzip2_SOURCE_DIR}/*.1)

install_targets(/lib bzip2)
install_targets(/bin bzip2recover)
install(FILES ${bzip2_scripts} DESTINATION bin)
install(FILES ${man1}          DESTINATION man/man1)
install(FILES ${bzip2_docs}    DESTINATION doc)
install(FILES ${bzip2_html}    DESTINATION doc/html)
install(FILES ${bzip2_scripts} DESTINATION bin)
install(FILES bzlib.h          DESTINATION include)

# echo EXPORTS > bzip2.def
# nm bzip2.dll | grep ' T _' | sed 's/.* T _//' >> bzip2.def
# pexports bzip2.dll > bzip2.def
# lib /def:bzip2.def /machine:x86
