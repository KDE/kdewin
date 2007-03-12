if(MINGW)
   set(_incDirPrefix mingw)
else (MINGW)
   set(_incDirPrefix msvc)
endif(MINGW)


include_directories( ../include ../include/${_incDirPrefix}  )
link_directories(.. )

add_executable(test_time time.c)
target_link_libraries(test_time kdewin32)

add_executable(test_byteswap byteswap.c)
target_link_libraries(test_byteswap kdewin32)
