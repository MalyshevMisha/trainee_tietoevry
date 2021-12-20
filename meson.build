project('trainee_project', 'cpp',
     default_options : ('cpp_std=c++2a'))

project_sources = []
test_sources = []

inc = include_directories('Header', 'NetConfAgent/hpp', 'NetConfAgent/API')

subdir('Source')
subdir('NetConfAgent')
#subdir('Test')

executable('trainee_task', sources : [project_sources, 'main.cpp'],
     include_directories : inc, link_with : NetConfAgentLib)
