// -*- C++ -*-

#ifndef _logx_Logging_H
#define _logx_Logging_H

#include <log4cpp/Category.hh>
#include <iosfwd>

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
   * Print usage info for the logging command line options to the
   * given output stream.
   **/
  void
  LogUsage(std::ostream& out);

  /**
   * Parse and remove logging options in the command-line argument list.
   * This also sets up an ostream appender for the root category with a
   * basic logging layout and a threshold of ERROR.  The categories can be
   * listed with the -categories option, but only the categories created
   * statically with file scope (ie, before main() is entered) will be
   * known at this point.  However, that includes all categories created
   * with the LOGGING macro.  If @p skip_usage is nonzero, then the
   * logging options will not be printed if the -help option is detected.
   *
   * @see LOGGING
   * @see LogUsage()
   **/
  void
  ParseLogArgs (int& argc, char* argv[], int skip_usage = 0);

  /**
   * Add an appender to the root category which will log messages of all
   * priorities to the given output stream.  Since ParseLogArgs() only
   * installs an appender with a threshold of ERROR, this function is can
   * be used to direct debug messages as well.
   **/
  void
  AddVerboseAppender (const std::string& name, std::ostream& out);

  /**
   * install a FileAppender for all categories that opens the specified
   * file.
   * set additivity false to only log to this FileAppender
   **/
  void
  LogToFile(std::string logFile,  bool additivity = true);
    
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

