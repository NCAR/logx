Import('*')

my_env = env.Copy()

for t in [PKG_ACE,]:
        t(my_env)
my_env.Library('logx',    Split("ACE_Appender.cc LogLayout.cc LogAppender.cc"))
