add_library(Add add.cpp)
link_gbenchmark(Add)
set_normal_compile_options(Add)
set_warnings_as_errors(Add)

# getting started
# run with `./build/src/GettingStarted` (gcc)
add_executable(GettingStarted getting_started.cpp)
set_normal_compile_options(GettingStarted)
link_gbenchmark(GettingStarted)

add_executable(BasicUsage basic_usage.cpp)
set_normal_compile_options(BasicUsage)
link_gbenchmark(BasicUsage)

add_executable(SetupTeardown setup_teardown.cpp)
set_normal_compile_options(SetupTeardown)
link_gbenchmark(SetupTeardown)

add_executable(PassingArguments pass_arguments.cpp)
set_normal_compile_options(PassingArguments)
link_gbenchmark(PassingArguments)

add_executable(Complexity asymptotic_complexity.cpp)
set_normal_compile_options(Complexity)
link_gbenchmark(Complexity)