#include <benchmark/benchmark.h>

static void BM_StringCreation(benchmark::State &state) {
  for (auto _ : state)
    std::string empty_string;
}
// Register the function as a benchmark
BENCHMARK(BM_StringCreation);

// Define another benchmark
static void BM_StringCopy(benchmark::State &state) {
  std::string x = "hello";
  for (auto _ : state)
    std::string copy(x);
}
BENCHMARK(BM_StringCopy);

BENCHMARK_MAIN();

// `BENCHMARK_MAIN` Expands to
// int main(int argc, char **argv) {
//   char arg0_default[] = "benchmark";
//   char *args_default = arg0_default;
//   if (!argv) {
//     argc = 1;
//     argv = &args_default;
//   }
//   ::benchmark ::Initialize(&argc, argv);
//   if (::benchmark ::ReportUnrecognizedArguments(argc, argv))
//     return 1;
//   ::benchmark ::RunSpecifiedBenchmarks();
//   ::benchmark ::Shutdown();
//   return 0;
// }

// To register benchmarks, use `RegisterBenchmark(name, func, args...)`
// alternatively.
// Unlike the macros, `RegisterBenchmark` can be called anywhere.