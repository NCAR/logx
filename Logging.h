// For internal implementation only and not meant to be included by
// any public interface files.

#ifndef _Logging_H
#define _Logging_H

#include <log4cpp/Category.hh>

#define LOGGING(name) \
namespace { \
log4cpp::Category &CatLog = log4cpp::Category::getInstance(name); \
log4cpp::CategoryStream::Separator endlog = log4cpp::CategoryStream::ENDLINE;\
}

#define DLOG CatLog.debugStream()
#define ELOG CatLog.errorStream()

#endif // _Logging_H

