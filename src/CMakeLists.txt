add_library(Add add.cpp)
link_gbenchmark(Add)
set_normal_compile_options(Add)
set_warnings_as_errors(Add)

# getting started
# run with `./build/src/GettingStarted` (gcc)
add_executable(GettingStarted getting_started.cpp)
set_normal_compile_options(GettingStarted)
link_gbenchmark(GettingStarted)