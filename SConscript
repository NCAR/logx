# -*- python -*-


Import('env')
env = env.Create('logx',
tools = ['default', 'logx', 'log4cpp'],
toolpath = ['#scons_tools'])
#env.Require (Split('PKG_LOG4CPP'))

sources = Split("""
 Logging.cc LogLayout.cc LogAppender.cc system_error.cc
""")
headers = Split("""
 CaptureStream.h EventSource.h Logging.h Checks.h
 system_error.h
""")

objects = env.SharedObject(sources)
liblogx = env.Library('logx', objects)
Default(liblogx)

env.InstallLibrary(liblogx)
env.InstallHeaders('logx', headers)

env['DOXYFILE_DICT'].update({ "PROJECT_NAME" : "logx library" })
env.Apidocs(sources + headers + ["private/LogLayout.h"])

SConscript("tests/SConscript")
