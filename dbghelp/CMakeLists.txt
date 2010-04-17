if (MINGW32)
	install(FILES dbghelp.h DESTINATION include/mingw)
	install(FILES libdbghelp.a DESTINATION lib)
endif (MINGw32)