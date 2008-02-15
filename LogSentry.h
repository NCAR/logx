// -*- C++ -*-

#ifndef _logx_LogSentry_h_
#define _logx_LogSentry_h_


#include <log4cpp/Category.hh>
#include <log4cpp/CategoryStream.hh>

namespace logx
{

class LogSentry
{
  log4cpp::CategoryStream _stream;
  std::string _msg;

public:
  /**
   * Construct a logging sentry that will log @p msg with the given @p
   * category and @p priority.  A log message is generated when this object
   * is constructed and destroyed, so it can be used to delimit entering
   * and leaving a certain scope, especially functions.
   **/
  LogSentry(log4cpp::Category& category, 
	    log4cpp::Priority::Value priority,
	    const std::string& msg) :
    _stream(category, priority),
    _msg(msg)
  {
    enter();
  }

  /**
   * A convenience constructor which uses the same category and priority of
   * the given @p stream.  This allows for code to use logx macros like
   * DLOG and ELOG create a log sentry on the local category:
   *
   * @code
   * LogSentry ls(DLOG, __PRETTY_FUNCTION__);
   * @endcode
   **/
  LogSentry(const log4cpp::CategoryStream& stream, 
	    const std::string& msg) :
    _stream(stream.getCategory(), stream.getPriority()),
    _msg(msg)
  {
    enter();
  }

  void 
  enter()
  {
    _stream << "entering: " << _msg;
    _stream.flush();
  }

  ~LogSentry()
  {
    _stream << "leaving: " << _msg;
    _stream.flush();
  }
};

/**
 * Macro for creating a LogSentry which logs the current function name
 * using the GCC __PRETTY_FUNCTION__ symbol.
 **/
#define SLOG(LOGSTREAM) \
  logx::LogSentry __logging_sentry(LOGSTREAM, __PRETTY_FUNCTION__)

}
// namespace logx

#endif // _logx_LogSentry_h_
