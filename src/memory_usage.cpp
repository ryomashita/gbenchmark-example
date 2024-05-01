#include <memory>

#include "benchmark/benchmark.h"

// This memory-usage data will be reported currently only JSON output.

class TestMemoryManager : public benchmark::MemoryManager {
  void Start() override {}
  void Stop(Result &result) override {
    // number of allocation sizes
    result.num_allocs = 42;
    result.max_bytes_used = 42000;
  }
};

void BM_empty(benchmark::State &state) {
  for (auto _ : state) {
    auto iterations = double(state.iterations()) * double(state.iterations());
    benchmark::DoNotOptimize(iterations);
  }
}
BENCHMARK(BM_empty);

// call `RegisterMemoryManager` in `main` function manually
int main(int argc, char **argv) {
  char arg0_default[] = "benchmark";
  char *args_default = arg0_default;
  if (!argv) {
    argc = 1;
    argv = &args_default;
  }

  std::unique_ptr<benchmark::MemoryManager> mm(new TestMemoryManager());
  benchmark::RegisterMemoryManager(mm.get());

  ::benchmark ::Initialize(&argc, argv);
  if (::benchmark ::ReportUnrecognizedArguments(argc, argv))
    return 1;
  ::benchmark ::RunSpecifiedBenchmarks();

  benchmark::RegisterMemoryManager(nullptr);

  ::benchmark ::Shutdown();
  return 0;
}