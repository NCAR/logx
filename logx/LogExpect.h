// -*- C++ -*-

#ifndef _logx_LogExpect_h_
#define _logx_LogExpect_h_

#include <string>
#include "log4cpp/Category.hh"

namespace logx
{

  /**
   * LogExpect is a simple RAII class which temporarily suppresses logging
   * messages for a given category.  This is useful in unit tests which
   * intentionally generate error messages which would otherwise clutter
   * the test output.  The constructor takes the name of the category
   * for which logging is to be suppressed.  When the LogExpect object
   * goes out of scope, the original logging priority for the category
   * is restored.
   * 
   * This is probably misnamed, since it does not actually check that any
   * messages were logged as expected, it just suppresses them.
   */
  class LogExpect
  {
    log4cpp::Category& category;
    log4cpp::Priority::Value lastPriority;

  public:
    LogExpect(const std::string& catname);
    ~LogExpect();
  };

}

#endif // _logx_LogExpect_h_
