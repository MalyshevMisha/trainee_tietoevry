test_sources += files('Source/MobileClientTest.cpp')

gtest_dep = dependency('gtest', main : true, required : false)
gmock_dep = dependency('gmock')


test_incl_dirs = include_directories('Mock')
mobCli_test = executable('trainee_task', 
                        sources : [project_sources, test_sources],
                        dependencies : [gtest_dep, 
                                        gmock_dep, 
                                        MobileClient_lib_dep], 
                        include_directories :  [test_incl_dirs, inc])
test('mobCli_test', mobCli_test)


