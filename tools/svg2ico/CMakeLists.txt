
find_package(ZLIB)

add_definitions(${QT_DEFINITIONS} )

include_directories(
    ${QT_INCLUDES} 
    ${CMAKE_SOURCE_DIR}/include  
    ${CMAKE_CURRENT_BINARY_DIR} 
    ${ZLIB_INCLUDE_DIR}
)
if (MINGW)
    include_directories(${CMAKE_SOURCE_DIR}/include/mingw)
else (MINGW)
    include_directories(${CMAKE_SOURCE_DIR}/include/msvc)
endif(MINGW)

add_executable(svg2ico svg2ico.cpp )
target_link_libraries(svg2ico ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${QT_QTSVG_LIBRARY} ${ZLIB_LIBRARY})

install(TARGETS svg2ico DESTINATION bin)
