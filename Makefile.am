
lib_LIBRARIES = liblogx.a

if LOGX_ENABLE_ACE_APPENDER
ace_srcs = ACE_Appender.cc 
ace_cppflags = $(ACEX_INCLUDES)
else
ace_srcs =
ace_cppflags =
endif

liblogx_a_SOURCES = \
   LogLayout.cc private/LogLayout.h $(ace_srcs)

logxincludedir = $(includedir)/logx

logxinclude_HEADERS = Logging.h ACE_Appender.h

AM_CPPFLAGS = $(LOG4CPP_CFLAGS) $(ace_cppflags)

DOXYGEN_REFERENCES = $(LOG4CPP_DOXREF) $(ACEX_DOXREF)

include ../config/Doxyfile.am

