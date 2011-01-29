project(kdewin-qt)

configure_file(${kdewin_SOURCE_DIR}/include/kdewin_qt_export.h.cmake
               ${kdewin_BINARY_DIR}/include/kdewin_qt_export.h)

set(kdewin_qt_SRCS
    linkfile.cpp
)
include_directories(
    ${QT_INCLUDES}
)

if (BUILD_BASE_LIB_WITH_QT)
    add_library(kdewin-qt-static STATIC ${kdewin_qt_SRCS})
    if(NOT WINCE)
    target_link_libraries(kdewin-qt-static ${QT_QTCORE_LIBRARIES} advapi32 shell32 ws2_32 )
    else(NOT WINCE)
    target_link_libraries(kdewin-qt-static ${QT_QTCORE_LIBRARIES} ws2 )
    endif(NOT WINCE)
    set_target_properties(kdewin-qt-static PROPERTIES DEFINE_SYMBOL MAKE_KDEWIN_QT_LIB )
    set_target_properties(kdewin-qt-static PROPERTIES VERSION ${KDEWIN_VERSION_STR} )
endif (BUILD_BASE_LIB_WITH_QT)

if (BUILD_QT_LIB)
    add_library(kdewin-qt SHARED ${kdewin_qt_SRCS})
    if(NOT WINCE)
        target_link_libraries(kdewin-qt ${QT_QTCORE_LIBRARIES} advapi32 shell32 ws2_32 )
    else(NOT WINCE)
        target_link_libraries(kdewin-qt ${QT_QTCORE_LIBRARIES} ws2 )
    endif(NOT WINCE)
    set_target_properties(kdewin-qt PROPERTIES DEFINE_SYMBOL MAKE_KDEWIN_QT_LIB )
    set_target_properties(kdewin-qt PROPERTIES VERSION ${KDEWIN_VERSION_STR} )

    install(TARGETS kdewin-qt
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib
    )
endif (BUILD_QT_LIB)

if (BUILD_BASE_LIB_WITH_QT OR BUILD_QT_LIB)
    install(DIRECTORY ../include/kdewin   DESTINATION include PATTERN ".svn" EXCLUDE)
    install(DIRECTORY ../include/KDE      DESTINATION include PATTERN ".svn" EXCLUDE)
    install(FILES ${CMAKE_BINARY_DIR}/include/kdewin_qt_export.h      DESTINATION include)
endif (BUILD_BASE_LIB_WITH_QT OR BUILD_QT_LIB)
