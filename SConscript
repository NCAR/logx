# -*- python -*-
#
# Just load the logx tool directly as a SConscript.  See tool_logx.py for
# the meat.  This avoids loading the tool as a tool, ie, searching the
# source tree for tool_logx.py and applying the module as a tool to modify
# an Environment.  That way any variant dirs in effect for this SConscript
# will also be in effect for the logx build.

SConscript('tool_logx.py')
