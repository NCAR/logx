// -*- C++ -*-

#ifndef _logx_Logging_H
#define _logx_Logging_H

#include <log4cpp/Category.hh>

namespace logx
{
  void
  LogUsage();

  void
  ParseLogArgs (int& argc, char* argv[]);
}

#define LOGGING(name) \
namespace { \
log4cpp::Category &CatLog = log4cpp::Category::getInstance(name); \
log4cpp::CategoryStream::Separator endlog = log4cpp::CategoryStream::ENDLINE;\
}

#define DLOG CatLog.debugStream()
#define ELOG CatLog.errorStream()
#define ILOG CatLog.infoStream()

#endif // _logx_Logging_H

