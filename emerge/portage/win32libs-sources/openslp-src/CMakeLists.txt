project(openslp)

#find_package(OpenSSL REQUIRED)

set(slp_headers
    ${CMAKE_SOURCE_DIR}/libslp/slp.h
)

set(common_SRCS
#    ${CMAKE_SOURCE_DIR}/common/slp_attr_l.c
#    ${CMAKE_SOURCE_DIR}/common/slp_attr_y.c
    ${CMAKE_SOURCE_DIR}/common/slp_buffer.c
    ${CMAKE_SOURCE_DIR}/common/slp_compare.c
    ${CMAKE_SOURCE_DIR}/common/slp_database.c
    ${CMAKE_SOURCE_DIR}/common/slp_dhcp.c
#    ${CMAKE_SOURCE_DIR}/common/slp_filter_l.c
#    ${CMAKE_SOURCE_DIR}/common/slp_filter_y.c
    ${CMAKE_SOURCE_DIR}/common/slp_iface.c
    ${CMAKE_SOURCE_DIR}/common/slp_linkedlist.c
    ${CMAKE_SOURCE_DIR}/common/slp_message.c
    ${CMAKE_SOURCE_DIR}/common/slp_net.c
    ${CMAKE_SOURCE_DIR}/common/slp_network.c
    ${CMAKE_SOURCE_DIR}/common/slp_parse.c
    ${CMAKE_SOURCE_DIR}/common/slp_pid.c
    ${CMAKE_SOURCE_DIR}/common/slp_property.c
    ${CMAKE_SOURCE_DIR}/common/slp_utf8.c
    ${CMAKE_SOURCE_DIR}/common/slp_v1message.c
    ${CMAKE_SOURCE_DIR}/common/slp_xcast.c
    ${CMAKE_SOURCE_DIR}/common/slp_xid.c
    ${CMAKE_SOURCE_DIR}/common/slp_xmalloc.c
)
# better : if have_fnmatch_h
if(NOT WIN32)
set(common_SRCS
    ${common_SRCS}
    ${CMAKE_SOURCE_DIR}/common/slp_predicate.c
)
endif(NOT WIN32)

set(common_crypt_SRCS
    ${CMAKE_SOURCE_DIR}/common/slp_auth.c
    ${CMAKE_SOURCE_DIR}/common/slp_crypto.c
    ${CMAKE_SOURCE_DIR}/common/slp_spi.c
)
if(OPENSSL_FOUND)
    set(common_SRCS
        ${common_SRCS}
        ${common_crypt_SRCS}
    )
endif(OPENSSL_FOUND)

set(libslp_SRCS
    ${CMAKE_SOURCE_DIR}/libslp/libslp_delattrs.c
    ${CMAKE_SOURCE_DIR}/libslp/libslp_dereg.c
    ${CMAKE_SOURCE_DIR}/libslp/libslp_findattrs.c
    ${CMAKE_SOURCE_DIR}/libslp/libslp_findscopes.c
    ${CMAKE_SOURCE_DIR}/libslp/libslp_findsrvs.c
    ${CMAKE_SOURCE_DIR}/libslp/libslp_findsrvtypes.c
    ${CMAKE_SOURCE_DIR}/libslp/libslp_handle.c
    ${CMAKE_SOURCE_DIR}/libslp/libslp_knownda.c
    ${CMAKE_SOURCE_DIR}/libslp/libslp_network.c
    ${CMAKE_SOURCE_DIR}/libslp/libslp_parse.c
    ${CMAKE_SOURCE_DIR}/libslp/libslp_property.c
    ${CMAKE_SOURCE_DIR}/libslp/libslp_reg.c
    ${CMAKE_SOURCE_DIR}/libslp/libslp_thread.c
    ${common_SRCS}
)
set(slpd_SRCS
    ${CMAKE_SOURCE_DIR}/slpd/slpd_cmdline.c
    ${CMAKE_SOURCE_DIR}/slpd/slpd_database.c
    ${CMAKE_SOURCE_DIR}/slpd/slpd_incoming.c
    ${CMAKE_SOURCE_DIR}/slpd/slpd_knownda.c
    ${CMAKE_SOURCE_DIR}/slpd/slpd_log.c
    ${CMAKE_SOURCE_DIR}/slpd/slpd_main.c
    ${CMAKE_SOURCE_DIR}/slpd/slpd_outgoing.c
    ${CMAKE_SOURCE_DIR}/slpd/slpd_process.c
    ${CMAKE_SOURCE_DIR}/slpd/slpd_property.c
    ${CMAKE_SOURCE_DIR}/slpd/slpd_regfile.c
    ${CMAKE_SOURCE_DIR}/slpd/slpd_socket.c
    ${CMAKE_SOURCE_DIR}/slpd/slpd_v1process.c
)
if(WIN32)
  set(slpd_SRCS
      ${slpd_SRCS}
      ${CMAKE_SOURCE_DIR}/slpd/slpd_win32.c
      ${CMAKE_SOURCE_DIR}/libslpattr/libslpattr.c
  )
  add_definitions(-DUSE_PREDICATES -D_WIN32_WINNT=0x0500)
else(WIN32)
  set(slpd_SRCS
      ${slpd_SRCS}
      ${CMAKE_SOURCE_DIR}/slpd/slpd_predicate.c
      ${CMAKE_SOURCE_DIR}/slpd/slpd_spi.c
  )
endif(WIN32)

set(slptool_SRCS
    ${CMAKE_SOURCE_DIR}/slptool/slptool.c
)

add_library(slp SHARED ${libslp_SRCS})
add_executable(slpd ${common_SRCS} ${slpd_SRCS})
add_executable(slptool ${slptool_SRCS})
add_definitions(-DENABLE_SLPv1 -DSLP_VERSION=\\"1.2.1\\")
include_directories(${CMAKE_SOURCE_DIR}
                    ${CMAKE_SOURCE_DIR}/common
                    ${CMAKE_SOURCE_DIR}/libslp
                    ${OPENSSL_INCLUDE_DIR}
)
set_target_properties(slp PROPERTIES DEFINE_SYMBOL LIBSLP_EXPORTS)
target_link_libraries(slp ws2_32 ${OPENSSL_LIBRARIES})
target_link_libraries(slpd slp)
target_link_libraries(slptool slp)

install(TARGETS slp
                RUNTIME DESTINATION bin
                LIBRARY DESTINATION lib
                ARCHIVE DESTINATION lib
)
install(FILES ${slp_headers} DESTINATION include)
