
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

add_executable(create_hash_table create_hash_table.cpp lookup.cpp)
target_link_libraries(create_hash_table ${QT_QTCORE_LIBRARY} )

install(TARGETS create_hash_table DESTINATION bin)