// -*- C++ -*-

#ifndef _logx_system_error_hh_
#define _logx_system_error_hh_

#include <stdexcept>
#include <string>
#include <iosfwd>

namespace logx
{

  /**
   * An object which encapsulates the current @code errno and corresponding
   * error message from @code strerror() into an object which can be
   * written to an ostream.  It inherits from runtime_error so it can be
   * thrown as an exception also.
   **/
  class system_error : public std::runtime_error
  {
  public:

    std::string
    message (const std::string& action = "", 
	     const std::string& object = "", int errnum = -1);

    /**
     * If @p errnum is -1, use the current value of @code errno.
     **/
    system_error(const std::string& action = "", 
		 const std::string object = "",
		 int errnum = -1);

    inline 
    int
    whatErrno()
    {
      return _num;
    }

  private:

    int _num;
    
  };

}    


std::ostream&
operator<< (std::ostream& out, const logx::system_error& se);



#endif
