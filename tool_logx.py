# -*- python -*-

tools = ['prefixoptions', 'doxygen', 'log4cpp']
env = Environment(tools = ['default'] + tools)

logxDir = Dir('..')

def logx(env):
    env.Append(LIBS=[env.GetGlobalTarget('liblogx'),])
    env.AppendUnique(CPPPATH=logxDir)
    env.AppendDoxref(doxref[0])
    env.Require(tools)

Export('logx')

sources = Split("""
 Logging.cc
 LogLayout.cc
 LogAppender.cc
 RecentHistoryAppender.cc
 system_error.cc
""")
headers = Split("""
 CaptureStream.h
 EventSource.h
 Logging.h
 Checks.h
 LogSentry.h
 RecentHistoryAppender.h
 system_error.h
""")

objects = env.SharedObject(sources)
lib = env.Library('logx', objects)
Default(lib)

# Install targets commented out.  Shouldn't be needed.

# Create install targets if INSTALL_PREFIX is defined
#if 'INSTALL_PREFIX' in env:
#    env.InstallLibrary(lib)
#    env.InstallHeaders('logx', headers)

env['DOXYFILE_DICT'].update({ "PROJECT_NAME" : "Logx" })
doxref = env.Apidocs(sources + headers + ["private/LogLayout.h"])

SConscript("tests/SConscript")
