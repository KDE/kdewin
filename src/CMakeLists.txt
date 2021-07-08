if(MINGW)
   set(_incDirPrefix mingw)
else (MINGW)
   # disable msvc callings to use the _s versions
   add_definitions( -D_CRT_SECURE_NO_DEPRECATE
                    -D_CRT_NONSTDC_NO_DEPRECATE
                  )
   set(_incDirPrefix msvc)
endif(MINGW)

add_definitions(-DUNICODE -DWIN32_LEAN_AND_MEAN )

set(win_LIB_SRCS
   dirent.c
   errno.c
#not implemented: fcntl.c
   fsync.c
   getenv.c
   grp.c
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

if(NOT KDEWIN_HAVE_INET_NTOP)
    list(APPEND
        inet.c
        bind/inet_ntop.c
        bind/inet_pton.c
    )
endif()

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

target_link_libraries(kdewin user32 shell32 ws2_32 netapi32 userenv)

target_include_directories(kdewin PUBLIC "$<BUILD_INTERFACE:${kdewin_INCLUDES}>")

if(MINGW)
   # we are using mingw, so do whatever required for mingw
   target_include_directories(kdewin INTERFACE "$<INSTALL_INTERFACE:include/mingw>")
else (MINGW)
   # we are using msvc, so do whatever required for msvc
   target_include_directories(kdewin INTERFACE "$<INSTALL_INTERFACE:include/msvc>")
endif(MINGW)

target_include_directories(kdewin INTERFACE "$<INSTALL_INTERFACE:include>")

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
  EXPORT KDEWin_targets
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
  ARCHIVE DESTINATION lib
)

file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/required_ioctls_test.cpp
"#include <windows.h>
#include <winioctl.h>
#if !defined(IOCTL_STORAGE_QUERY_PROPERTY)
#error 1
#endif

int main() { return 0; }
")
try_compile(HAVE_REQUIRED_IOCTLS ${CMAKE_CURRENT_BINARY_DIR}
                                 ${CMAKE_CURRENT_BINARY_DIR}/required_ioctls_test.cpp)

set(ddk_HDRS
  ../include/ntddcdrm.h
  ../include/ntddcdvd.h
  ../include/ntddmmc.h
  ../include/ntddstor.h
)

install(DIRECTORY ../include/${_incDirPrefix}                  DESTINATION include)
install(FILES ../include/fixwinh.h ../include/kde_file_win.h   DESTINATION include)
install(FILES ${CMAKE_BINARY_DIR}/include/kdewin_export.h      DESTINATION include)

install(FILES ${ddk_HDRS}                                      DESTINATION include/${_incDirPrefix})

if(MINGW AND NOT HAVE_REQUIRED_IOCTLS)
    message(STATUS "you miss the required ioctl definitions. Installing winioctl_backport.h")
    install(FILES ../include/winioctl_backport.h               DESTINATION include/${_incDirPrefix})
endif(MINGW AND NOT HAVE_REQUIRED_IOCTLS)

if(MINGW32 AND NOT MINGW_W32)
    install(DIRECTORY ../include/directx                       DESTINATION include/${_incDirPrefix} PATTERN ".svn" EXCLUDE)
endif(MINGW32 AND NOT MINGW_W32)

