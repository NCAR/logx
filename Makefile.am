
lib_LIBRARIES = liblogx.a

liblogx_a_SOURCES = LogLayout.cc private/LogLayout.h

logxincludedir = $(includedir)/logx

logxinclude_HEADERS = Logging.h

AM_CPPFLAGS = $(LOG4CPP_CFLAGS)

DOXYGEN_REFERENCES = log4cpp:$(LOG4CPP_DOCDIR)

include ../config/Doxyfile.am

