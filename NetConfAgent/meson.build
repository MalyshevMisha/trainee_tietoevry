NetConfAgentInc = include_directories('hpp', 'API')

NetConfAgentSource = files('source/NetConfAgent.cpp', 
                         'source/MobileClient.cpp', 
                         'source/PathGenerator.cpp')

sysrepoDep = dependency('sysrepo-cpp')
doctestDep = dependency('doctest')
libyangDep = dependency('libyang-cpp')
trompeloeilDep = dependency('trompeloeil')

NetConfAgentLib = static_library('NetConfAgent',
     sources : NetConfAgentSource,
     include_directories : NetConfAgentInc,
     dependencies : [sysrepoDep, doctestDep, 
                    libyangDep, trompeloeilDep])

MobileClient_lib_dep = [
    declare_dependency(
        link_with : [NetConfAgentLib],
        include_directories : [NetConfAgentInc]
    )
]