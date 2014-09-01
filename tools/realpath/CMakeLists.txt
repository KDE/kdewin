include_directories(${target_include_directories})

add_executable(realpath realpath.cpp)
target_link_libraries(realpath)

install(TARGETS realpath EXPORT KDEWin_tools_targets DESTINATION bin)
