#include <benchmark/benchmark.h>

static void BM_MultiThreaded(benchmark::State &state) {
  if (state.thread_index() == 0) {
    // Setup code here.
  }
  // it is guaranteed that none of the threads will start until all have reached
  // the start of the benchmark loop,
  for (auto _ : state) {
    // Run the test as normal.
    state.PauseTiming();  // Stop timers.
    state.ResumeTiming(); // And resume timers.
  }
  // ... and all will have finished before any
  // thread exits the benchmark loop
  if (state.thread_index() == 0) {
    // Teardown code here.
  }
}

BENCHMARK(BM_MultiThreaded)
    ->ThreadRange(1, 8)
    ->MeasureProcessCPUTime() // the total CPU time cosumption
    ->UseRealTime();          // use real time instead of (default) CPU time

// ベンチマーク自体がマルチスレッドの場合は Range(1, 8)
// など通常のパラメタとしてスレッド数を渡す

BENCHMARK_MAIN();