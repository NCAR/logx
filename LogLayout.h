/* -*- C++ -*-
 * LogLayout.hh
 *
 */

#ifndef _logx_LOGLAYOUT_H
#define _logx_LOGLAYOUT_H

#include <log4cpp/Layout.hh>

namespace logx
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

#endif // _logx_LOGLAYOUT_H
