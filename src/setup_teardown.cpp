#include <benchmark/benchmark.h>
#include <iostream>

static void DoSetup(const benchmark::State &state) {
  std::cout << state.name() << " setup" << std::endl;
}

static void DoTeardown(const benchmark::State &state) {
  std::cout << state.name() << " teardown" << std::endl;
}

static void BM_func(benchmark::State &state) {
  for (auto _ : state) {
    // Do something
  }
}

BENCHMARK(BM_func)
    ->Arg(1)
    ->Arg(3)
    ->Threads(16)
    ->Threads(32)
    ->Setup(DoSetup)
    ->Teardown(DoTeardown);

BENCHMARK_MAIN();