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
    

  /**
   * Simple class to collect the logging category names specified across
   * translation units into a singe global list, so that all of the
   * categories are known up front and can be configured with command-line
   * options.
   **/
  class Logging_init
  {
  public:
    Logging_init (const std::string& name);
    ~Logging_init();
  };


  /**
   * Return the array of logging category names specified for individual
   * compilation modules with the LOGGGING macro.  These category names
   * have not necessarily been instantiated yet with
   * log4cpp::getInstance().  That is deferred until they are actually
   * needed, such as when the category appenders and threshold levels are
   * configured with command-line options.
   **/
  const std::string*
  getLocalCategoryNames(int* n);

}

/**
 * Create a log category with the given @p name with static file scope.
 * Logging streams for this category can be created with the DLOG, ELOG,
 * and ILOG macros.  This also defines a convenient copy @p endlog of the
 * ENDLINE CategoryStream::Separator.  The category is not actually created
 * here until used, to avoid issues of initialization order between other
 * translation units.  Instead, category names are collected by the
 * Logging_init() constructors, and those names can be accessed through the
 * getLocalCategoryNames() function.
 **/
#define LOGGING(name) \
namespace { \
logx::Logging_init _logging_init(name); \
inline log4cpp::Category &localCategory() \
{ \
  static log4cpp::Category& log = log4cpp::Category::getInstance(name); \
  return log; \
} \
log4cpp::CategoryStream::Separator endlog = log4cpp::CategoryStream::ENDLINE;\
}

/*
 * For backwards compatibility with older code which used the CatLog
 * symbol directly.
 */
#define CatLog localCategory()

#define DLOG localCategory().debugStream()
#define ELOG localCategory().errorStream()
#define ILOG localCategory().infoStream()

#endif // _logx_Logging_H

