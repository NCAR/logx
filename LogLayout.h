/*
 * LogLayout.hh
 *
 */

#ifndef _xlog4cpp_LOGLAYOUT_H
#define _xlog4cpp_LOGLAYOUT_H

#include <log4cpp/Layout.hh>

namespace xlog4cpp
{

  /**
   * A simple fixed format Layout implementation.
   **/
  class LogLayout : public log4cpp::Layout 
    {
    public:
      LogLayout();
      virtual ~LogLayout();

      /**
       * Formats the LoggingEvent including file name and line number.
       **/
      virtual std::string format(const log4cpp::LoggingEvent& event);
    };        

}

#endif // _xlog4cpp_LOGLAYOUT_H
