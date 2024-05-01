#include <benchmark/benchmark.h>
#include <chrono>
#include <thread>

// An example use case for this is benchmarking GPU execution (e.g. OpenCL or
// CUDA kernels, OpenGL or Vulkan or Direct3D draw calls), which cannot be
// accurately measured using CPU time or real-time.
// Instead, they can be measured accurately using a dedicated API, and these
// measurement results can be reported back with SetIterationTime.

static void BM_ManualTiming(benchmark::State &state) {
  int microseconds = static_cast<int>(state.range(0));
  std::chrono::duration<double, std::micro> sleep_duration{
      static_cast<double>(microseconds)};

  for (auto _ : state) {
    auto start = std::chrono::high_resolution_clock::now();
    // Simulate some useful workload with a sleep
    std::this_thread::sleep_for(sleep_duration);
    auto end = std::chrono::high_resolution_clock::now();

    auto elapsed_seconds =
        std::chrono::duration_cast<std::chrono::duration<double>>(end - start);

    // set the iteration time manually
    // When `UseManualTime` is used, the benchmarked code must call
    // `SetIterationTime` once per iteration
    state.SetIterationTime(elapsed_seconds.count());
  }
}
BENCHMARK(BM_ManualTiming)->Range(1, 1 << 17)->UseManualTime();

BENCHMARK_MAIN();