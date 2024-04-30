#include <benchmark/benchmark.h>
#include <iostream>

// Reference:
// https://github.com/google/benchmark/blob/main/docs/user_guide.md#setupteardown

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

// Arg{1, 3} と Threads{16, 32} の直積で計 4 回実行される
BENCHMARK(BM_func)
    ->Arg(1)
    ->Arg(3)
    ->Threads(16)
    ->Threads(32)
    ->Setup(DoSetup)
    ->Teardown(DoTeardown);

BENCHMARK_MAIN();