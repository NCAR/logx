
#include "logx/Logging.h"
#include "logx/Checks.h"

LOGGING("tlogx");

extern void tlogx_a();
extern void tlogx_b();


int
main(int argc, char* argv[])
{
  // Make sure the list of categories is as we expect.
  int n;
  const std::string* names = logx::getLocalCategoryNames(&n);

  Check(n == 4); // Includes the "Logging" category.
  Check(std::find (names, names+n, "tlogx") != names+n);
  Check(std::find (names, names+n, "tlogx.a") != names+n);
  Check(std::find (names, names+n, "tlogx.b") != names+n);

  logx::ParseLogArgs (argc, argv);

  DLOG << "running sub-routines";
  tlogx_a();
  tlogx_b();

  CatLog.infoStream() << "sub-routines complete";

  return CheckResult();
}

