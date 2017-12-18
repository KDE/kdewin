project(kdewin-qt)

configure_file(${kdewin_SOURCE_DIR}/include/kdewin_qt_export.h.cmake
               ${kdewin_BINARY_DIR}/include/kdewin_qt_export.h)

set( kdewin_qt_SRCS
    linkfile.cpp
)

if (BUILD_BASE_LIB_WITH_QT)
    add_library(kdewin-qt-static STATIC ${kdewin_qt_SRCS})
    if(NOT WINCE)
        target_link_libraries(kdewin-qt-static Qt5::Core advapi32 shell32 ws2_32 )
    else(NOT WINCE)
        target_link_libraries(kdewin-qt-static Qt5::Core ws2 )
    endif(NOT WINCE)

    install(TARGETS kdewin-qt-static EXPORT KDEWin_targets ARCHIVE DESTINATION lib)

    set(KDEWIN_QT_STATIC_LIBRARY "set(KDEWIN_QT_STATIC_LIBRARY kdewin-qt-static)" PARENT_SCOPE)
    set_target_properties(kdewin-qt-static PROPERTIES DEFINE_SYMBOL MAKE_KDEWIN_QT_LIB )
    set_target_properties(kdewin-qt-static PROPERTIES VERSION ${KDEWIN_VERSION_STR} )

    target_include_directories(kdewin-qt-static PUBLIC "$<BUILD_INTERFACE:${kdewin_INCLUDES}>")
    if(MINGW)
         # we are using mingw, so do whatever required for mingw
        target_include_directories(kdewin-qt-static INTERFACE "$<INSTALL_INTERFACE:include/mingw>")
    else (MINGW)
        # we are using msvc, so do whatever required for msvc
        target_include_directories(kdewin-qt-static INTERFACE "$<INSTALL_INTERFACE:include/msvc>")
    endif(MINGW)
    target_include_directories(kdewin-qt-static INTERFACE "$<INSTALL_INTERFACE:include>")
endif (BUILD_BASE_LIB_WITH_QT)

if (BUILD_QT_LIB)
    add_library(kdewin-qt SHARED ${kdewin_qt_SRCS})
    if(NOT WINCE)
        target_link_libraries(kdewin-qt Qt5::Core advapi32 shell32 ws2_32 )
    else(NOT WINCE)
        target_link_libraries(kdewin-qt Qt5::Core ws2 )
    endif(NOT WINCE)
    set_target_properties(kdewin-qt PROPERTIES DEFINE_SYMBOL MAKE_KDEWIN_QT_LIB )
    set_target_properties(kdewin-qt PROPERTIES VERSION ${KDEWIN_VERSION_STR} )
    set(KDEWIN_QT_LIBRARY "set(KDEWIN_QT_LIBRARY kdewin-qt)" PARENT_SCOPE)

    install(TARGETS kdewin-qt
        EXPORT KDEWin_targets
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib
    )

    target_include_directories(kdewin-qt PUBLIC "$<BUILD_INTERFACE:${kdewin_INCLUDES}>")
    if(MINGW)
         # we are using mingw, so do whatever required for mingw
        target_include_directories(kdewin-qt INTERFACE "$<INSTALL_INTERFACE:include/mingw>")
    else (MINGW)
        # we are using msvc, so do whatever required for msvc
        target_include_directories(kdewin-qt INTERFACE "$<INSTALL_INTERFACE:include/msvc>")
    endif(MINGW)
    target_include_directories(kdewin-qt INTERFACE "$<INSTALL_INTERFACE:include>")
endif (BUILD_QT_LIB)

if (BUILD_BASE_LIB_WITH_QT OR BUILD_QT_LIB)
    install(DIRECTORY ../include/kdewin   DESTINATION include PATTERN ".svn" EXCLUDE)
    install(DIRECTORY ../include/KDE      DESTINATION include PATTERN ".svn" EXCLUDE)
    install(FILES ${CMAKE_BINARY_DIR}/include/kdewin_qt_export.h      DESTINATION include)
endif (BUILD_BASE_LIB_WITH_QT OR BUILD_QT_LIB)
