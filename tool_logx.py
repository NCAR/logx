# -*- python -*-

from SCons.Script import Environment, SConscript

env = Environment(tools=['default', 'doxygen', 'log4cpp'])

# includes use the logx/ prefix, so the parent dir will be added to the
# include path
logxdir = env.Dir('..')


def logx(env):
    env.Append(LIBS=[env.GetGlobalTarget('liblogx'),])
    env.AppendUnique(CPPPATH=logxdir)
    env.Require('log4cpp')


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
env.Apidocs(sources + headers + ["private/LogLayout.h"])

SConscript("tests/SConscript")

# When this is the top-level source directory, add help info and install
# targets.
if env.Dir('#') == env.Dir('.'):
    env.Require('prefixoptions')
    env['DEFAULT_INSTALL_PREFIX'] = '/opt/local'
    env['DEFAULT_OPT_PREFIX'] = '$DEFAULT_INSTALL_PREFIX'
    env.InstallLibrary(lib)
    env.InstallHeaders('logx', headers)
    env.SetHelp()
