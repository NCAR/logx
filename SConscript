# -*- python -*-

Import('env')
my_env = env.Create('logx')
my_tools = my_env.Require(Split('PKG_ACE PKG_LOG4CPP'))

def PKG_LOGX(env):
        env.Append(LIBPATH= ['#/logx',])
        env.Append(LIBS=['logx',])
	env.Apply (my_tools)

Export('PKG_LOGX')

lib = my_env.Library('logx', Split("""
 ACE_Appender.cc LogLayout.cc LogAppender.cc system_error.cc
"""))
Default(lib)
