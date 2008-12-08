TEMPLATE = vclib

HEADERS += CaptureStream.h
HEADERS += EventSource.h
HEADERS += Logging.h
HEADERS += system_error.h

SOURCES += LogAppender.cc
SOURCES += Logging.cc
SOURCES += LogLayout.cc
SOURCES += system_error.cc

DEFINES +=

CONFIG += build_all
CONFIG += warn_on 
CONFIG += staticlib
config += exceptions

INCLUDEPATH += c:/Projects/log4cpp-0.3.4b/include

