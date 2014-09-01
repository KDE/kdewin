
add_executable(mt mt.cpp xml.cpp)
add_executable(setuac uac.cpp xml.cpp)
install(TARGETS mt setuac EXPORT KDEWin_tools_targets DESTINATION bin)
