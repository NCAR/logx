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

namespace logx
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


  void
  LogUsage()
  {
    LogUsage (std::cerr);
  }

  void
  LogUsage(std::ostream& outs)
  {
    outs << "logging options:\n"
	 << "  -debug <category>\n"
	 << "                Set debug log level for the log category.\n"
	 << "  -info <category>\n"
	 << "                Set info log level for the log category.\n"
	 << "  -notice <category>\n"
	 << "                Set notice log level for the log category.\n"
	 << "  -categories   List the log categories.\n"
         << "  -logfile <log_file_name>\n"
	 << "                Log messages to the given log file.\n";
  }


  Appender*
  AddRootAppender (const std::string& name, std::ostream& out, 
		   Priority::Value p)
  {
    Category& root = Category::getRoot();
    Appender *appender = new OstreamAppender (name, &out);
    appender->setLayout (new LogLayout);
    appender->setThreshold (p);
    root.addAppender(appender);
    return appender;
  }


  void
  AddVerboseAppender (const std::string& name, std::ostream& out)
  {
    AddRootAppender (name, out, Priority::DEBUG);
  }


  void
  handleOption (const char* cat, Priority::Value p, Appender* appender = 0)
  {
    if (strcmp (cat, "all") == 0)
      Category::getRoot().setPriority(p);
    else
      Category::getInstance(cat).setPriority(p);
    appender->setThreshold (p);
  }


  void
  ParseLogArgs (int& argc, char* argv[], int skip_usage)
  {
    Category::getRoot().removeAllAppenders();
    Appender* appender = AddRootAppender ("cerr", std::cerr, Priority::ERROR);

    int i = 1;
    int iremain = 1;
    while (i < argc)
    {
      string arg(argv[i]);
      if (arg == "-debug" && i+1 < argc)
      {
	handleOption (argv[++i], log4cpp::Priority::DEBUG, appender);
      }
      else if (arg == "-notice" && i+1 < argc)
      {
	handleOption (argv[++i], log4cpp::Priority::NOTICE, appender);
      }
      else if (arg == "-info" && i+1 < argc)
      {
	handleOption (argv[++i], log4cpp::Priority::INFO, appender);
      }
      else if (arg == "-logfile" && i+1 < argc)
      {
	char *logfile = argv[++i];
	log4cpp::Appender *app =  
	  new log4cpp::FileAppender("FileAppender", logfile);

	std::vector<Category*> *cats = Category::getCurrentCategories();
    
	for (std::vector<Category*>::iterator icat = cats->begin();
	     icat != cats->end(); ++icat)
	{
	  (*icat)->setAppender(app);
	}
    
      }
      else if (arg == "-categories")
      {
	cout << "Log categories: " << endl;
	std::vector<Category*> *cats = Category::getCurrentCategories();
	for (std::vector<Category*>::iterator icat = cats->begin();
	     icat != cats->end(); ++icat)
	{
	  cout << "  ";
	  if ((*icat)->getName().length() == 0)
	    cout << "all";
	  else
	    cout << (*icat)->getName();
	  cout << endl;
	}
	exit (0);
      }
      else
      {
	if (iremain < i)
	  argv[iremain] = argv[i];
	// Check for help request but leave it on the arg list for
	// other option checkers to handle too.
	if (arg == "-help" || arg == "--help")
	{
	  if (! skip_usage)
	    LogUsage();
	}
	++iremain;
      }
      ++i;
    }
    argc = iremain;
    argv[argc] = 0;
  }

}


