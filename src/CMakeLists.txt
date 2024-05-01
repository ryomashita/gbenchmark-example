add_library(Add add.cpp)
link_gbenchmark(Add)
set_normal_compile_options(Add)
set_warnings_as_errors(Add)

function(register_as_benchmark target)
    set_normal_compile_options(${target})
    link_gbenchmark(${target})
endfunction()

# benchmark examples
# e.g., run with `./build/src/GettingStarted` (gcc)
add_executable(GettingStarted getting_started.cpp)
register_as_benchmark(GettingStarted)

add_executable(BasicUsage basic_usage.cpp)
register_as_benchmark(BasicUsage)

add_executable(SetupTeardown setup_teardown.cpp)
register_as_benchmark(SetupTeardown)

add_executable(PassingArguments pass_arguments.cpp)
register_as_benchmark(PassingArguments)

add_executable(Complexity asymptotic_complexity.cpp)
register_as_benchmark(Complexity)

add_executable(Templated templated.cpp)
register_as_benchmark(Templated)

add_executable(Fixtures fixtures.cpp)
register_as_benchmark(Fixtures)

add_executable(CustomCounters custom_counters.cpp)
register_as_benchmark(CustomCounters)

add_executable(Multithreaded multithreaded.cpp)
register_as_benchmark(Multithreaded)