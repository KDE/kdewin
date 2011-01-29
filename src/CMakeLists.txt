configure_file(${kdewin_SOURCE_DIR}/include/kdewin_export.h.cmake
               ${kdewin_BINARY_DIR}/include/kdewin_export.h)

if(MINGW)
   set(_incDirPrefix mingw)
else (MINGW)
   # disable msvc callings to use the _s versions
   add_definitions( -D_CRT_SECURE_NO_DEPRECATE
                    -D_CRT_NONSTDC_NO_DEPRECATE
                  )
   set(_incDirPrefix msvc)
endif(MINGW)

include_directories(${target_include_directories})

add_definitions(-DUNICODE -DWIN32_LEAN_AND_MEAN )

set(win_LIB_SRCS
   bind/inet_ntop.c
   bind/inet_pton.c
   dirent.c
   errno.c
#not implemented: fcntl.c
   fsync.c
   getenv.c
   grp.c
   inet.c
   kde_file_win.c
   mmap.c
   nl_langinfo.c
   net.c
   pwd.c
   realpath.c
   resource.c
   signal.c
   stdlib.c
   string.c
   strptime.c
   syslog.c
   time.c
   uname.c
   unistd.c
#   io.c
   dummy.c
   )
if(MSVC)
  set(win_LIB_SRCS ${win_LIB_SRCS}
      stdio.c
      math/tgamma.c
      math/tgammaf.c
      math/lgamma.c
      math/lgammaf.c
      math/math.c
      math/expm1.c
      math/erfl.c
      math/s_erf.c
      math/sf_erf.c
      math/e_remainder.c
  )
endif(MSVC)

set(CMAKE_DEBUG_POSTFIX "d")

add_library(kdewin ${LIBRARY_TYPE} ${win_LIB_SRCS} ${kdewin_SRCS})
if(NOT WINCE)
    target_link_libraries(kdewin advapi32 shell32 ws2_32 uuid ole32 ${QT_QTCORE_LIBRARIES})
else(NOT WINCE)
    target_link_libraries(kdewin ws2 ${QT_QTCORE_LIBRARIES} ${WCECOMPAT_LIBRARIES} toolhelp )
endif(NOT WINCE)
set_target_properties(kdewin PROPERTIES DEFINE_SYMBOL MAKE_KDEWIN_LIB )
set_target_properties(kdewin PROPERTIES VERSION ${KDEWIN_VERSION_STR} )

if (BUILD_BASE_LIB_WITH_QT)
    target_link_libraries(kdewin kdewin-qt-static)
endif (BUILD_BASE_LIB_WITH_QT)

if(MSVC)
  # 4244: 'argument' : conversion from 'type1' to 'type2', possible loss of data
  # 4305: 'identifier' : truncation from 'type1' to 'type2'
  set_target_properties(kdewin PROPERTIES
      COMPILE_FLAGS "-wd4244 -wd4305"
  )
endif(MSVC)

install(TARGETS kdewin
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
  ARCHIVE DESTINATION lib
)

install(DIRECTORY ../include/${_incDirPrefix}                  DESTINATION include PATTERN ".svn" EXCLUDE)
install(FILES ../include/fixwinh.h ../include/kde_file_win.h   DESTINATION include)
install(FILES ${CMAKE_BINARY_DIR}/include/kdewin_export.h      DESTINATION include)

if(MINGW32 AND NOT MINGW_W32)
    install(DIRECTORY ../include/directx                       DESTINATION include/${_incDirPrefix} PATTERN ".svn" EXCLUDE)
endif(MINGW32 AND NOT MINGW_W32)

