
#include "ACE_Appender.h"
#include <string>
#include <iostream>
#include <log4cpp/LayoutAppender.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/Category.hh>
#include <ace/Log_Msg.h>
#include <acex/Log_Setup.h>

using std::string;
using log4cpp::Priority;

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


  /**
   * ACE_Appender appends LoggingEvents using ACE_Log_Msg.
   **/
  class ACE_Appender : public log4cpp::LayoutAppender
  {
  public:

    ACE_Appender() : LayoutAppender ("ACE_Appender")
    {}

    virtual
    ~ACE_Appender()
    {}
        
    virtual void 
    _append (const log4cpp::LoggingEvent& event)
    {
      string msg (_getLayout().format(event));
      ACE_Log_Priority ap = 
	convertPriority (Priority::PriorityLevel(event.priority));
      if (ap >= LM_ERROR)
      {
	ACE_ERROR((ap, "%s", msg.c_str()));
      }
      else
      {
	ACE_DEBUG((ap, "%s", msg.c_str()));
      }
    }

    virtual bool
    reopen()
    {
      return true;
    }

    virtual void
    close()
    {
    }

  };


  void
  Install_ACE_Appender (int& argc, char* argv[])
  {
    acex::SetupLogger (argc, argv);
    log4cpp::Category& root = log4cpp::Category::getRoot();
    root.removeAllAppenders();
    root.addAppender(new ACE_Appender);
  }


  ACE_Appender*
  Create_ACE_Appender (const char* argv0)
  {
    return new ACE_Appender;
  }


}
