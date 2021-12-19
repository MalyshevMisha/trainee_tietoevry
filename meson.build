project('trainee_project', 'cpp',
     default_options : ('cpp_std=c++2a'))

project_sources = []
test_sources = []

inc = include_directories('Header', 'NetConfAgent/hpp', 'Test/Mock', 'NetConfAgent/API')

gtest_dep = dependency('gtest', main : true, required : false)
gmock_dep = dependency('gmock')

subdir('Source')
subdir('NetConfAgent')
subdir('Test')

#executable('trainee_task', sources : [project_sources, 'main.cpp'],
#     include_directories : inc, link_with : NetConfAgentLib)

executable('trainee_task', sources : [project_sources, test_sources],
     dependencies : [gtest_dep, gmock_dep], include_directories : inc, link_with : NetConfAgentLib)