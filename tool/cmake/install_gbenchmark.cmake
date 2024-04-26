# install google/benchmark

# options for google/benchmark 
# reference: https://github.com/google/benchmark/blob/main/CMakeLists.txt
set(BENCHMARK_DOWNLOAD_DEPENDENCIES ON CACHE BOOL "" FORCE) # downloading unmet dependencies
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE) # testing of the benchmark library
set(BENCHMARK_ENABLE_GTEST_TESTS OFF CACHE BOOL "" FORCE) # building the unit tests
set(BENCHMARK_ENABLE_LIBPFM ON CACHE BOOL "" FORCE) # using libpfm

include(FetchContent)
FetchContent_Declare(
  gbenchmark
  URL https://github.com/google/benchmark/archive/refs/tags/v1.8.3.zip
      DOWNLOAD_EXTRACT_TIMESTAMP OFF)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt
    ON
    CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(gbenchmark)

# link google-benchmark to target
function(link_gbenchmark target)
  target_link_libraries(${target} benchmark::benchmark)
endfunction()