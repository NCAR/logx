
#include "ACE_Appender.h"
#include <string>
#include <iostream>
#include <log4cpp/LayoutAppender.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/Category.hh>
#include <ace/Log_Msg.h>
#include <acex/Log_Setup.h>

using std::string;
using log4cpp::Priority;
using log4cpp::PatternLayout;

namespace logx
{


  Priority::PriorityLevel
  convert_ACE_Priority (ACE_Log_Priority ap)
  {
    switch (ap)
    {
    case LM_SHUTDOWN:
      return Priority::NOTICE;
    case LM_TRACE:
    case LM_DEBUG:
      return Priority::DEBUG;
    case LM_INFO:
      return Priority::INFO;
    case LM_NOTICE:
      return Priority::NOTICE;
    case LM_WARNING:
      return Priority::WARN;
    case LM_STARTUP:
      return Priority::NOTICE;
    case LM_ERROR:
      return Priority::ERROR;
    case LM_CRITICAL:
      return Priority::CRIT;
    case LM_ALERT:
      return Priority::ALERT;
    case LM_EMERGENCY:
      return Priority::EMERG;
    default:
      break;
    }
    return Priority::ERROR;
  }


  ACE_Log_Priority
  convertPriority (log4cpp::Priority::PriorityLevel lp)
  {
    switch (lp)
    {
    case Priority::DEBUG:
      return LM_DEBUG;
    case Priority::INFO:
      return LM_INFO;
    case Priority::NOTICE:
      return LM_NOTICE;
    case Priority::WARN:
      return LM_WARNING;
    case Priority::ERROR:
      return LM_ERROR;
    case Priority::CRIT:
      return LM_CRITICAL;
    case Priority::ALERT:
      return LM_ALERT;
    case Priority::EMERG:
      return LM_EMERGENCY;
    default:
      break;
    }
    return LM_ERROR;
  }


  ACE_Appender::
  ACE_Appender() : LayoutAppender ("ACE_Appender")
  {
    set_ACE_Format ("%D %M %n: %s");
    set_Pattern_Layout ("%m%n");
  }


  ACE_Appender::
  ACE_Appender (const std::string& pattern, 
		const std::string& ace_format) : 
    LayoutAppender ("ACE_Appender")
  {
    set_Pattern_Layout (pattern);
    set_ACE_Format (ace_format);
  }


  void
  ACE_Appender::
  set_Pattern_Layout (const std::string& pattern)
  {
    PatternLayout* layout = new PatternLayout();
    layout->setConversionPattern (pattern);
    setLayout (layout);
  }


  void
  ACE_Appender::
  set_ACE_Format (const std::string& ace_format)
  {
    _ace_format = ace_format;
  }


  ACE_Appender::
  ~ACE_Appender()
  {}
  
      
  void 
  ACE_Appender::
  _append (const log4cpp::LoggingEvent& event)
  {
    string msg (_getLayout().format(event));
    ACE_Log_Priority ap = 
      convertPriority (Priority::PriorityLevel(event.priority));
    int __ace_error = ACE_Log_Msg::last_error_adapter ();
    ACE_Log_Msg *ace___ = ACE_Log_Msg::instance ();
    ace___->conditional_set ("unknown", -1,
			     (ap >= LM_ERROR) ? -1 : 0, __ace_error);
    ace___->log (ap, _ace_format.c_str(), msg.c_str());
  }

  
  bool
  ACE_Appender::
  reopen()
  {
    return true;
  }

  
  void
  ACE_Appender::
  close()
  {
  }


  void
  ACE_Appender::
  Install (ACE_Appender* aa)
  {
    if (! aa) 
    {
      aa = new ACE_Appender;
      // Include categories in the log messages by default.
      aa->set_Pattern_Layout ("%c: %m%n");
    }
    log4cpp::Category& root = log4cpp::Category::getRoot();
    root.addAppender(aa);
  }


}
