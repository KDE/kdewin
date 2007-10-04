include_directories(${PNG_INCLUDE_DIR})

add_executable(png2ico png2ico.cpp)
target_link_libraries(png2ico ${PNG_LIBRARIES} )

install(TARGETS png2ico DESTINATION bin)
