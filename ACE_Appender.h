// -*- C++ -*-

#include <string>
#include <log4cpp/LayoutAppender.hh>

namespace logx
{

  log4cpp::Appender*
  Create_ACE_Appender (int& argc, char* argv[]);

  void
  Install_ACE_Appender (int& argc, char* argv[]);

}

