# -*- python -*-

from SCons.Script import Environment, SConscript

env = Environment(tools=['default', 'doxygen', 'log4cpp'])
build = env


def logx(env):
    env.Append(LIBS=[build['LOGX_LIB']])
    env.AppendUnique(CPPPATH=[build['LOGX_CPPPATH']])
    env.Require('log4cpp')


toolname = env.get('LOGX_TOOL_NAME', 'logx')
env.Export({toolname: logx})

sources = env.Split("""
 Logging.cc
 LogLayout.cc
 LogAppender.cc
 LogExpect.cc
 RecentHistoryAppender.cc
 system_error.cc
""")

headers = env.Split("""
 logx/CaptureStream.h
 logx/EventSource.h
 logx/Logging.h
 logx/Checks.h
 logx/LogSentry.h
 logx/LogExpect.h
 logx/RecentHistoryAppender.h
 logx/system_error.h
""")

objects = env.SharedObject(sources)
lib = env.Library('logx', objects)
env.Default(lib)
build['LOGX_CPPPATH'] = env.Dir('.')
build['LOGX_LIB'] = lib

if toolname == 'logx':
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
