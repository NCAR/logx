


#include "Logging.h"
#include "private/LogLayout.h"
#include <vector>
#include <string>
#include <cstring>  // strcmp()
#include <cstdlib> // exit()

#include <log4cpp/Portability.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/Appender.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/Category.hh>

using namespace log4cpp;
using namespace logx;
using namespace std;

// Make sure the list gets initialized even if no other translation units
// are using it.
LOGGING("logx.Logging");

namespace
{
  int init_count;

  std::vector<std::string>* names;

  Appender*
  AddRootAppender (const std::string& name, std::ostream& out, 
		   Priority::Value p)
  {
    Category& root = Category::getRoot();
    Appender *appender = new OstreamAppender (name, &out);
    appender->setLayout (new LogLayout);
    //appender->setThreshold (p);
    root.addAppender(appender);
    return appender;
  }

  void
  handleOption (const char* cat, Priority::Value p, Appender* appender = 0)
  {
    if (strcmp (cat, "all") == 0)
      Category::getRoot().setPriority(p);
    else
      Category::getInstance(cat).setPriority(p);
    //appender->setThreshold (p);
  }


}


const std::string*
logx::
getLocalCategoryNames(int* n)
{
  *n = names->size();
  return &(*names)[0];
}


Logging_init::
Logging_init (const std::string& name)
{
  if (++init_count == 1)
  {
    names = new std::vector<std::string>;
  }
  names->push_back (name);
}



Logging_init::
~Logging_init()
{
  if (--init_count == 0)
  {
    delete names;
    names = 0;
  }
}


void
logx::
LogUsage()
{
  LogUsage (std::cerr);
}


void
logx::
LogUsage(std::ostream& outs)
{
  outs << "logging options:\n"
       << "  --debug <category>\n"
       << "                Set debug log level for the log category.\n"
       << "  --info <category>\n"
       << "                Set info log level for the log category.\n"
       << "  --notice <category>\n"
       << "                Set notice log level for the log category.\n"
       << "  --fatal <category>\n"
       << "                Limit this log category to fatal messages.\n"
       << "  --categories   List the log categories.\n"
       << "  --logfile <log_file_name>\n"
       << "                Log messages to the given log file.\n";
}



void
logx::
AddVerboseAppender (const std::string& name, std::ostream& out)
{
  AddRootAppender (name, out, Priority::DEBUG);
}


void
logx::
ParseLogArgs (int& argc, char* argv[], int skip_usage)
{
  Category::getRoot().removeAllAppenders();
  Appender* appender = AddRootAppender ("cerr", std::cerr, Priority::ERROR);

  int i = 1;
  int iremain = 1;
  while (i < argc)
  {
    string arg(argv[i]);
    if ((arg == "-debug" || arg == "--debug") && i+1 < argc)
    {
      handleOption (argv[++i], log4cpp::Priority::DEBUG, appender);
    }
    else if ((arg == "-notice" || arg == "--notice") && i+1 < argc)
    {
      handleOption (argv[++i], log4cpp::Priority::NOTICE, appender);
    }
    else if ((arg == "-info" || arg == "--info") && i+1 < argc)
    {
      handleOption (argv[++i], log4cpp::Priority::INFO, appender);
    }
    else if ((arg == "--fatal") && i+1 < argc)
    {
      handleOption (argv[++i], log4cpp::Priority::FATAL, appender);
    }
    else if ((arg == "-logfile" || arg == "--logfile") && i+1 < argc)
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
    else if (arg == "-categories" || arg == "--categories")
    {
      // Define any categories on the global list of names, then query
      // the log4cpp list, in case other categories have been specified
      // outside of the global names.
      std::vector<std::string>::iterator in;
      for (in = names->begin(); in != names->end(); ++in)
      {
	Category::getInstance(*in);
      }
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
