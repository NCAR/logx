// $Id$

#include "system_error.h"
#include <string.h>
#include <errno.h>
#include <sstream>
#include <ostream>

using namespace logx;

std::string
system_error::
message (const std::string& action, const std::string& object, int errnum)
{
  std::ostringstream out;
  if (action.length() > 0)
    out << action << ": ";
  if (object.length() > 0)
    out << object << ": ";
  if (errnum == -1)
    errnum = errno;
  out << ::strerror(errnum) << "(" << errnum << ")";
  return out.str();
}


system_error::
system_error(const std::string& action,
	     const std::string object,
	     int errnum) :
  std::runtime_error (message(action, object, errnum))
{
  if (errnum == -1)
    _num = errno;
  else
    _num = errnum;
}


std::ostream&
logx::
operator<< (std::ostream& out, const logx::system_error& se)
{
  out << se.what();
  return out;
}


