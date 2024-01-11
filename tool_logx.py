# -*- python -*-

from SCons.Script import Environment, SConscript

tools = ['prefixoptions', 'doxygen', 'log4cpp']
env = Environment(tools=['default'] + tools)

logxDir = env.Dir('..')


def logx(env):
    env.Append(LIBS=[env.GetGlobalTarget('liblogx'),])
    env.AppendUnique(CPPPATH=logxDir)
    env.AppendDoxref(doxref[0])
    env.Require(tools)


env.Export('logx')

sources = env.Split("""
 Logging.cc
 LogLayout.cc
 LogAppender.cc
 RecentHistoryAppender.cc
 system_error.cc
""")

headers = env.Split("""
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
env.Default(lib)


env['DOXYFILE_DICT'].update({"PROJECT_NAME": "Logx"})
doxref = env.Apidocs(sources + headers + ["private/LogLayout.h"])

SConscript("tests/SConscript")

# When this is the top-level source directory, add help info and install
# targets.
if env.Dir('#') == env.Dir('.'):
    env['DEFAULT_INSTALL_PREFIX'] = '/opt/local'
    env['DEFAULT_OPT_PREFIX'] = '$DEFAULT_INSTALL_PREFIX'
    env.InstallLibrary(lib)
    env.InstallHeaders('logx', headers)
    env.SetHelp()
