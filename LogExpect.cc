

#include "LogExpect.h"

namespace logx
{

LogExpect::
LogExpect(const std::string& catname) :
  category(log4cpp::Category::getInstance(catname))

{
  // Turn off error logging temporarily.
  lastPriority = category.getPriority();
  category.setPriority(log4cpp::Priority::EMERG);
}


LogExpect::
~LogExpect()
{
  category.setPriority(lastPriority);
}

}
