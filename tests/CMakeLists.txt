include_directories( ../include/_incDirPrefix  )
link_directories(.. )

add_executable(test_time time.c)
target_link_libraries(test_time kdewin32)

