/*
 * LogLayout.cc
 */

#include <log4cpp/Portability.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/Appender.hh>
#include <log4cpp/Category.hh>

#include "Logging.h"
#include "private/LogLayout.h"
#include <iostream>
#include <sstream>
#include <string>

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
    std::ostringstream message;

    const std::string& priorityName = 
      Priority::getPriorityName(event.priority);
    message << priorityName << "[" << event.categoryName << "] ";
    message << event.message << std::endl;

    return message.str();
  }


  void
  LogUsage()
  {
    cerr << "-debug <category>\n"
	 << "                Set debug log level for the log category.\n"
	 << "-notice <category>\n"
	 << "                Set notice log level for the log category.\n"
	 << "-categories     List the log categories.\n";
  }


  void
  ParseLogArgs (int& argc, char* argv[])
  {
    log4cpp::Appender *rootAppender = 
      log4cpp::Category::getRoot().getAppender();
    rootAppender->setLayout (new LogLayout);

    int i = 1;
    int iremain = 1;
    while (i < argc)
    {
      string arg(argv[i]);
      if (arg == "-debug" && i+1 < argc)
      {
	char *cat = argv[++i];
	if (strcmp (cat, "all") == 0)
	  Category::getRoot().setPriority(log4cpp::Priority::DEBUG);
	else
	  Category::getInstance(cat).setPriority(log4cpp::Priority::DEBUG);
      }
      else if (arg == "-notice" && i+1 < argc)
      {
	char *cat = argv[++i];
	if (strcmp (cat, "all") == 0)
	  Category::getRoot().setPriority(log4cpp::Priority::NOTICE);
	else
	  Category::getInstance(cat).setPriority(log4cpp::Priority::NOTICE);
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
	  LogUsage();
	++iremain;
      }
      ++i;
    }
    argc = iremain;
    argv[argc] = 0;
  }

}


