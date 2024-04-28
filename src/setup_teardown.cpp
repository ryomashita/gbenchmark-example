#include <benchmark/benchmark.h>

static void DoSetup(const benchmark::State &state) {}

static void DoTeardown(const benchmark::State &state) {}

static void BM_func(benchmark::State &state) {}

BENCHMARK(BM_func)
    ->Arg(1)
    ->Arg(3)
    ->Threads(16)
    ->Threads(32)
    ->Setup(DoSetup)
    ->Teardown(DoTeardown);

BENCHMARK_MAIN();