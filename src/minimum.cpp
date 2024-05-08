#include <benchmark/benchmark.h>

auto SomeFunction() -> void {}

// No requirements on the benchmark name (BM_SomeFunction)
static void BM_SomeFunction(benchmark::State &state) {
  for (auto _ : state)
    SomeFunction();
}
// Register the function as a benchmark
BENCHMARK(BM_SomeFunction);
// Run the benchmark
BENCHMARK_MAIN();