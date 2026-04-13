// -*- C++ -*-

#include <sstream>
#include <iostream>

class Context
{
public:
  Context(const std::string& cond, const std::string& file, int line) :
    _cond(cond),
    _file(file),
    _line(line)
  {}

  inline std::string 
  condition() const
  {
    return _cond;
  }


  inline std::string
  location() const
  {
    std::ostringstream oss;
    oss << file() << ":" << line();
    return oss.str();
  }

private:

  inline std::string 
  file() const
  {
    return _file;
  }

  inline int
  line() const
  {
    return _line;
  }

  std::string _cond;
  std::string _file;
  int _line;
};


namespace
{
  int nchecks = 0;
  int errors = 0;

  const int DEBUG_CHECKS = 0;

  inline int
  doCheck (const Context& context, int& errors, int result)
  {
    ++nchecks;
    if (DEBUG_CHECKS || !result)
    {
      std::cerr << context.location() << " [" << context.condition() << "]: ";
    }
    if (!result)
    {
      ++errors;
      std::cerr << "*** FAILED ***" << std::endl;
    }
    else if (DEBUG_CHECKS)
    {
      std::cerr << "ok." << std::endl;
    }
    return result;
  }

  inline int
  CheckResult()
  {
    std::cerr << nchecks << " checks.\n"
	      << errors << " failures.\n";
    return errors;
  }

}

#define CONTEXT(cond) Context(#cond,__FILE__,__LINE__)

#define Check(cond) doCheck(CONTEXT(cond), errors, cond)
