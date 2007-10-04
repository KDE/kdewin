
option(ZLIB_SHARED "Build shared lib" YES)
option(ZLIB_STATIC "Build static library" YES)
option(ZLIB_INSTALL "install libraries" YES)

set (zlib_sources
    adler32.c
    compress.c
    crc32.c
    deflate.c
    gzio.c
    infback.c
    inffast.c
    inflate.c
    inftrees.c
    trees.c
    uncompr.c
    zutil.c
)

if (ZLIB_SHARED)
    add_library(zlib SHARED ${zlib_sources})
    target_link_libraries(zlib)
endif (ZLIB_SHARED)

if (ZLIB_STATIC)
    add_library(zlib_static STATIC ${zlib_sources})
    target_link_libraries(zlib_static)
endif (ZLIB_STATIC)

if (ZLIB_INSTALL)
    if (ZLIB_SHARED)
        install(TARGETS zlib 
            RUNTIME DESTINATION bin
            LIBRARY DESTINATION lib
            ARCHIVE DESTINATION lib
        )
    endif(ZLIB_SHARED)
    if (ZLIB_STATIC)
        install(TARGETS zlib_static
            RUNTIME DESTINATION bin
            LIBRARY DESTINATION lib
            ARCHIVE DESTINATION lib
        )
    endif (ZLIB_STATIC)
endif (ZLIB_INSTALL)
    