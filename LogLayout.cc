/*
 * LogLayout.cc
 */

#include <log4cpp/Priority.hh>

#include "Logging.h"
#include "private/LogLayout.h"
#include <iostream>
#include <string>
#include <ctime>

using namespace log4cpp;
using namespace logx;

LogLayout::LogLayout()
{
}
    
LogLayout::~LogLayout() 
{
}

std::string
LogLayout::format(const log4cpp::LoggingEvent& event) 
{
  char buf[32];
  time_t t = event.timeStamp.getSeconds();
  strftime (buf, sizeof(buf), "%Y-%m-%d %H:%M:%S|", gmtime(&t));

  std::ostringstream message;
  const std::string& priorityName = Priority::getPriorityName(event.priority);
  message << buf << priorityName << "[" << event.categoryName << "] ";
  message << event.message << std::endl;

  return message.str();
}
