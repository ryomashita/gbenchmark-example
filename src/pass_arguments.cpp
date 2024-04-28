#include "benchmark/benchmark.h"
#include <cstring>
#include <iostream>

using namespace std;

// Reference:
// https://github.com/google/benchmark/blob/main/docs/user_guide.md#passing-arguments

/* Passing Arguments */
static void BM_memcpy(benchmark::State &state) {
  char *src = new char[state.range(0)];
  char *dst = new char[state.range(0)];
  memset(src, 'x', state.range(0));
  for (auto _ : state)
    memcpy(dst, src, state.range(0));
  state.SetBytesProcessed(int64_t(state.iterations()) *
                          int64_t(state.range(0)));
  delete[] src;
  delete[] dst;
}
BENCHMARK(BM_memcpy)->Arg(8)->Arg(64)->Arg(512)->Arg(4 << 10)->Arg(8 << 10);
// You can use `RangeMultiplier` instead.
// BENCHMARK(BM_memcpy)->RangeMultiplier(2)->Range(8, 8<<10);

/* Generation parameters from a dense range */
static void BM_DenseRange(benchmark::State &state) {
  for (auto _ : state) {
    std::vector<int> v(state.range(0), state.range(0));
    auto data = v.data();
    benchmark::DoNotOptimize(data);
    benchmark::ClobberMemory();
  }
}
// arguments generated are [ 0, 128, 256, 384, 512, 640, 768, 896, 1024 ].
BENCHMARK(BM_DenseRange)->DenseRange(0, 1024, 128);

/* Passing Multiple Arguments */
// このサンプル関数ではプログラムが停止しない
static auto RandomNumber() -> int { return rand() % 2; }
static auto ConstructRandomSet(int size) -> std::set<int> {
  std::set<int> data;
  while (data.size() < size)
    data.insert(RandomNumber());
  return data;
}
static void BM_SetInsert(benchmark::State &state) {
  std::set<int> data;
  for (auto _ : state) {
    state.PauseTiming();
    data = ConstructRandomSet(state.range(0));
    state.ResumeTiming();
    for (int j = 0; j < state.range(1); ++j)
      data.insert(RandomNumber());
  }
}
BENCHMARK(BM_SetInsert)
    ->Args({1 << 10, 128})
    ->Args({2 << 10, 128})
    ->Args({4 << 10, 128})
    ->Args({8 << 10, 128})
    ->Args({1 << 10, 512})
    ->Args({2 << 10, 512})
    ->Args({4 << 10, 512})
    ->Args({8 << 10, 512});
// same arguments are gnerated as above.
// ->ArgsProduct({{1<<10, 3<<10, 8<<10}, {20, 40, 60, 80}})
// BENCHMARK(BM_SetInsert)
// ->ArgsProduct({benchmark::CreateRange(8, 128, /*multi=*/2),
//  benchmark::CreateDenseRange(1, 4, /*step=*/1)})
// would generate the same benchmark arguments as
// ->ArgsProduct({{8, 16, 32, 64, 128}, {1, 2, 3, 4}});

/* Passing Arbitrary Arguments to a Benchmark */
template <class... Args>
void BM_takes_args(benchmark::State &state, Args &&...args) {
  auto args_tuple = std::make_tuple(std::move(args)...);
  for (auto _ : state) {
    std::cout << std::get<0>(args_tuple) << ": " << std::get<1>(args_tuple)
              << '\n';
  }
}
// Registers a benchmark named "BM_takes_args/int_string_test" that passes
// the specified values to `args`.
BENCHMARK_CAPTURE(BM_takes_args, int_string_test, 42, std::string("abc"));

// Registers the same benchmark "BM_takes_args/int_test" that passes
// the specified values to `args`.
BENCHMARK_CAPTURE(BM_takes_args, int_test, 42, 43);

BENCHMARK_MAIN();