// -*- C++ -*-

#ifndef _logx_Logging_H
#define _logx_Logging_H

#include <log4cpp/Category.hh>

/**
 * Useful extensions to the log4cpp library, including a basic log layout 
 * class and some command-line argument handling for setting log levels
 * of known categories.
 **/
namespace logx
{
  /**
   * Print to standard error the command line options recognized by
   * ParseLogArgs().
   **/
  void
  LogUsage();

  /**
   * Parse and remove logging options in the command-line argument list.
   * This also sets up a default, basic logging layout and adds it as the
   * appender for the root category.  The categories can be listed with 
   * the -categories option, but only the categories created statically with
   * file scope (ie, before main() is entered) will be known at this point.
   * However, that includes all categories created with the LOGGING macro.
   *
   * @see LOGGING
   * @see LogUsage()
   **/
  void
  ParseLogArgs (int& argc, char* argv[]);
}

/**
 * Create a log category with the given @p name with static file scope.
 * Logging streams for this category can be created with the DLOG, ELOG,
 * and ILOG macros.
 **/
#define LOGGING(name) \
namespace { \
log4cpp::Category &CatLog = log4cpp::Category::getInstance(name); \
log4cpp::CategoryStream::Separator endlog = log4cpp::CategoryStream::ENDLINE;\
}

#define DLOG CatLog.debugStream()
#define ELOG CatLog.errorStream()
#define ILOG CatLog.infoStream()

#endif // _logx_Logging_H

