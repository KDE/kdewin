
add_executable(mt mt.cpp xml.cpp)
target_link_libraries(mt)
install(TARGETS mt DESTINATION bin)
