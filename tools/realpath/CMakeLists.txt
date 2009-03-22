include_directories(${CMAKE_SOURCE_DIR}/include)
add_executable(realpath realpath.cpp)
target_link_libraries(realpath kdewin32)
