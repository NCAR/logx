/*
 * LogLayout.cc
 */

#include <log4cpp/Portability.hh>
#include <log4cpp/Priority.hh>

#include "LogLayout.h"
#include <sstream>

using namespace log4cpp;

namespace xlog4cpp
{

  LogLayout::LogLayout()
  {
  }
    
  LogLayout::~LogLayout() 
  {
  }

  std::string
  LogLayout::format(const LoggingEvent& event) 
  {
    std::ostringstream message;

    const std::string& priorityName = 
      Priority::getPriorityName(event.priority);
    message << priorityName << "[" << event.categoryName << "] ";
    message << event.message << std::endl;

    return message.str();
  }

}
