
include_directories( ${CMAKE_SOURCE_DIR}/include/directx )

remove_definitions(-DUNICODE -DWIN32_LEAN_AND_MEAN)

if (CMAKE_COMPILER_IS_GNUCXX)
   add_definitions(-g)
endif (CMAKE_COMPILER_IS_GNUCXX)

add_executable(dmusic dmusic.c )
target_link_libraries(dmusic ole32 gdi32)

add_executable(dshow dshow.cpp)
target_link_libraries(dshow ole32 gdi32)
