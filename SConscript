# -*- python -*-

Import('env')
my_env = env.Create('logx')
my_tools = my_env.Require('PKG_LOGX')

lib = my_env.Library('logx', Split("""
 ACE_Appender.cc LogLayout.cc LogAppender.cc system_error.cc
"""))
Default(lib)
