
lib_LIBRARIES = liblogx.a

liblogx_a_SOURCES = \
   LogLayout.cc private/LogLayout.h \
   ACE_Appender.cc 

logxincludedir = $(includedir)/logx

logxinclude_HEADERS = Logging.h ACE_Appender.h

AM_CPPFLAGS = $(LOG4CPP_CFLAGS) $(ACEX_INCLUDES)

DOXYGEN_REFERENCES = $(LOG4CPP_DOXREF) $(ACEX_DOXREF)

include ../config/Doxyfile.am

