#include <benchmark/benchmark.h>
#include <cstdint>

// Reference:
// https://github.com/google/benchmark/blob/main/docs/user_guide.md#calculating-asymptotic-complexity-big-o

// Asymptotic complexity : 漸近的計算量 (Big-O)

static void BM_StringCompare(benchmark::State &state) {
  const auto N = static_cast<int64_t>(state.range(0));
  const auto uN = static_cast<uint64_t>(N);

  std::string s1(uN, '-');
  std::string s2(uN, '-');
  for (auto _ : state) {
    auto comparison_result = s1.compare(s2);
    // DoNotOptimize: 変数が最適化で削除されるのを防ぐ (volatile)
    benchmark::DoNotOptimize(comparison_result);
  }
  // このベンチマークの計算量 O(N) をセットする
  state.SetComplexityN(N);
}
BENCHMARK(BM_StringCompare)
    // 2^10 ~ 2^18 の範囲で計測
    ->RangeMultiplier(2)
    ->Range(1 << 10, 1 << 18)
    // oN : 線形計算量 O(N) であることを伝える
    ->Complexity(benchmark::oN);
// Complexity は lambda でも指定可能
// ->Complexity([](benchmark::IterationCount n)->double{return n; });

BENCHMARK_MAIN();

// 実行すると以下のBigO, RMSの行が追加される
/*
...
BM_StringCompare/262144       **** ns         **** ns   105818
BM_StringCompare_BigO         0.0* N          0.0* N
BM_StringCompare_RMS             * %             * %
*/