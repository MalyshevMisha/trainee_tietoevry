NetConfAgentInc = include_directories('hpp')

NetConfAgentSource = files('source/NetConfAgent.cpp')

sysrepoDep = dependency('sysrepo-cpp')
doctestDep = dependency('doctest')
libyangDep = dependency('libyang-cpp')
trompeloeilDep = dependency('trompeloeil')

NetConfAgentLib = static_library('NetConfAgent',
     sources : NetConfAgentSource,
     include_directories : NetConfAgentInc,
     dependencies : [sysrepoDep, doctestDep, libyangDep, trompeloeilDep])