/*
 * LogLayout.cc
 */

#include <log4cpp/Portability.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/Appender.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/Category.hh>

#include "Logging.h"
#include "private/LogLayout.h"
#include <iostream>
#include <sstream>
#include <string>
#include <time.h>

using namespace log4cpp;
using std::cout;
using std::cerr;
using std::endl;
using std::string;

using namespace logx;

LogLayout::LogLayout()
{
}
    
LogLayout::~LogLayout() 
{
}

std::string
LogLayout::format(const LoggingEvent& event) 
{
  char buf[32];
  time_t t = event.timeStamp.getSeconds();
  strftime (buf, sizeof(buf), "%Y-%m-%d %H:%M:%S|", gmtime(&t));

  std::ostringstream message;
  const std::string& priorityName = 
    Priority::getPriorityName(event.priority);
  message << buf << priorityName << "[" << event.categoryName << "] ";
  message << event.message << std::endl;

  return message.str();
}

