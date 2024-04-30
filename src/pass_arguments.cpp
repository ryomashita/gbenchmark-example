#include "benchmark/benchmark.h"
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <sstream>
#include <sys/types.h>

// Reference:
// https://github.com/google/benchmark/blob/main/docs/user_guide.md#passing-arguments

/* Passing Arguments */
static void BM_memcpy(benchmark::State &state) {
  auto array_size = static_cast<uint64_t>(state.range(0));
  char *src = new char[array_size];
  char *dst = new char[array_size];
  memset(src, 'x', array_size);
  for (auto _ : state)
    memcpy(dst, src, array_size);

  // set UserCounters
  // SetBytesProcessed : give the number of bytes processed by the benchmark.
  state.SetBytesProcessed(int64_t(state.iterations()) *
                          int64_t(state.range(0)));
  delete[] src;
  delete[] dst;
}
BENCHMARK(BM_memcpy)
    ->Name("BM_memcpy_base") // custom name
    ->Arg(2 << 3)
    ->Arg(2 << 6)
    ->Arg(2 << 9)
    ->Arg(2 << 12)
    ->Arg(2 << 15);
// You can use `RangeMultiplier` instead.
// BENCHMARK(BM_memcpy)->RangeMultiplier(2)->Range(8, 8<<5);

/* Generation parameters from a dense range */
static void BM_DenseRange(benchmark::State &state) {
  auto array_size = static_cast<uint64_t>(state.range(0));
  const auto elem_default = static_cast<int32_t>(state.range(0));
  for (auto _ : state) {
    std::vector<int32_t> v(array_size, elem_default);
    auto data = v.data();
    benchmark::DoNotOptimize(data);
    benchmark::ClobberMemory();
  }
}
// arguments generated are [ 0, 128, 256, 384, 512, 640, 768, 896, 1024 ].
BENCHMARK(BM_DenseRange)->DenseRange(0, 1024, 128);

/* Passing Multiple Arguments */
static auto RandomNumber() -> int { return rand(); }
static auto ConstructRandomSet(std::size_t size) -> std::set<int> {
  std::set<int> data;
  while (data.size() < size)
    data.insert(RandomNumber());
  return data;
}
static void BM_SetInsert(benchmark::State &state) {
  auto set_size = static_cast<std::size_t>(state.range(0));
  auto insertions = static_cast<int32_t>(state.range(1));
  std::set<int> data;
  for (auto _ : state) {
    state.PauseTiming();
    data = ConstructRandomSet(set_size);
    state.ResumeTiming();
    for (int j = 0; j < insertions; ++j)
      data.insert(RandomNumber());
  }
}
BENCHMARK(BM_SetInsert)
    ->Args({1, 10})
    ->Args({2, 10})
    ->Args({4, 10})
    ->Args({8, 10});
// 実行時間が長すぎるので省略
// ->Args({1 << 10, 512})
// ->Args({2 << 10, 512})
// ->Args({4 << 10, 512})
// ->Args({8 << 10, 512});
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
  auto arg0 = std::get<0>(args_tuple);
  auto arg1 = std::get<1>(args_tuple);
  for (auto _ : state) {
    std::stringstream ss;
    ss << arg0 << ": " << arg1 << '\n';
    benchmark::DoNotOptimize(ss);
  }
}
// Registers a benchmark named "BM_takes_args/int_string_test" that passes
// the specified values to `args`.
BENCHMARK_CAPTURE(BM_takes_args, int_string_test, 42, std::string("abc"));

// Registers the same benchmark "BM_takes_args/int_test" that passes
// the specified values to `args`.
BENCHMARK_CAPTURE(BM_takes_args, int_test, 42, 43);

BENCHMARK_MAIN();