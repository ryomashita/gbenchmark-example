#include <benchmark/benchmark.h>

class Resource {
public:
  int read_data() { return (good()) ? 42 : -1; }
  bool good() const { return good_; }
  bool good_ = false;
  static void do_stuff(int) {}
};
Resource GetResource() { return {}; }

static void BM_test_ranged_fo(benchmark::State &state) {
  auto resource = GetResource();
  if (!resource.good()) {
    state.SkipWithError("Resource is not good!");
    return; // Early return is allowed when SkipWithError() has been used.
  }
  for (auto _ : state) {
    auto data = resource.read_data();
    if (!resource.good()) {
      state.SkipWithError("Failed to read data!");
      break; // REQUIRED to prevent all further iterations.
    }
    Resource::do_stuff(data);
  }
}

BENCHMARK(BM_test_ranged_fo);

BENCHMARK_MAIN();