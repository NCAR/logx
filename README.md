# Logx Library

Logx is a library of API extensions to the [log4cpp logging
library](http://log4cpp.sf.net/).  log4cpp is usually available as a standard
package on Linux distributions.

The typical usage is to include the file [logx/Logging.h](logx/Logging.h),
then use a macro to instantiate a logging category for that particular source
module. For example, in `Module.cc`:

```c++
#include "logx/Logging.h"
 
LOGGING("Module");
 
int
do_something()
{
   DLOG << "this is a debug message";
   ELOG << "this is an error message";
}
```

The [example](example.cc) program demonstrates one way to configure the
logging with command-line arguments, using the `logx::ParseLogArgs()` and
`logx::LogUsage()` functions.  Build it like so:

```sh
scons -f SConscript example
```

Then run it to see how the arguments affect the output.

Note `ParseLogArgs()` handles help arguments in a somewhat quirky manner.  If
`-help` or `--help` is detected, then the logging option usage is printed,
unless `skip_usage` is true.  The calling program, however, must still check
for the help argument itself, and if found print it's own usage info.  Most
programs will want to pass `skip_usage` as true, and then incorporate the
logging argument usage in the program usage by calling `logx::LogUsage()`
explicitly.

## Building Logx

Usually `logx` is built with [SCons](https://scons.org/) as a subdirectory of
another source tree.  In that case,
[eol_scons](https://github.com/NCAR/eol_scons) automatically finds and loads
the [tool_logx.py](tool_logx.py) tool file.

Logx can also be built and installed by itself using the
[SConscript](SConscript) file directly:

```sh
scons -f SConscript
```

There is no `SConstruct` file to avoid confusion when logx is a subdirectory
of a parent project with its own `SConstruct` file.

The logx library requires the [log4cpp](https://log4cpp.sourceforge.net/)
library.  To look for the dependencies somewhere besides the standard system
locations, set variable `OPT_PREFIX` on the command line or in a config.py
file:

```sh
scons -f SConscript OPT_PREFIX=/usr/local/logx
```

Set `INSTALL_PREFIX` to install somewhere besides the `/opt/local` default:

```sh
scons -f SConscript INSTALL_PREFIX=/opt/local/logx
```

To see all of the configuration options, use `scons -f SConscript -h`.

## Doxygen docs

Generate HTML API documentation from `doxygen` with `scons -f SConscript apidocs`,
although the documentation in the comments is rather sparse.

## Alternatives

There are other logging alternatives in use in EOL.
[NIDAS](https://github.com/ncareol/nidas) has a logging interface in the
`nidas_util` library; see
[nidas/util/Logger.h](https://github.com/ncareol/nidas/blob/master/src/nidas/util/Logger.h).
Boost also has a logging library,
[boost::log](https://www.boost.org/doc/libs/release/libs/log/).
