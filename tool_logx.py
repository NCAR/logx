# -*- python -*-

tools = ['doxygen', 'log4cpp']
env = Environment(tools = ['default'] + tools)

logxDir = Dir('.').abspath

def logx(env):
    env.Append(LIBS=[env.GetGlobalTarget('liblogx'),])
    env.AppendUnique(CPPPATH = logxDir)
    env.AppendDoxref('logx')
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
 RecentHistoryAppender.h
 system_error.h
""")

objects = env.SharedObject(sources)
lib = env.Library('logx', objects)
Default(lib)

env.InstallLibrary(lib)
env.InstallHeaders('logx', headers)

env['DOXYFILE_DICT'].update({ "PROJECT_NAME" : "logx library" })
env.Apidocs(sources + headers + ["private/LogLayout.h"])

SConscript("tests/SConscript")
