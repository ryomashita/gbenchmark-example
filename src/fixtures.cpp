#include <benchmark/benchmark.h>

// Reference:
// https://github.com/google/benchmark/blob/main/docs/user_guide.md#fixtures

// Fixtures = Define reusable SetUp() and TearDown().

class MyFixture : public benchmark::Fixture {
public:
  void SetUp(::benchmark::State &state) {
    benchmark::DoNotOptimize(state.name());
  }

  void TearDown(::benchmark::State &state) {
    benchmark::DoNotOptimize(state.name());
  }
};

/* BENCHMARK_F */
BENCHMARK_F(MyFixture, FooTest)(benchmark::State &st) {
  for (auto _ : st) {
    benchmark::DoNotOptimize(st.name());
  }
}

/* BENCHMARK_DEFINE_F + BENCHMARK_REGISTER_F */
BENCHMARK_DEFINE_F(MyFixture, BarTest)(benchmark::State &st) {
  for (auto _ : st) {
    benchmark::DoNotOptimize(st.name());
  }
}
BENCHMARK_REGISTER_F(MyFixture, BarTest)->Threads(2);

/* Templated Fixture */
template <typename T> class MyFixtureTemplated : public benchmark::Fixture {};

/* BENCHMARK_TEMPLATE_F */
BENCHMARK_TEMPLATE_F(MyFixtureTemplated, IntTest, int)(benchmark::State &st) {
  for (auto _ : st) {
    benchmark::DoNotOptimize(st.name());
  }
}

/* BENCHMARK_TEMPLATE_DEFINE_F + BENCHMARK_REGISTER_F */
BENCHMARK_TEMPLATE_DEFINE_F(MyFixtureTemplated, DoubleTest, double)
(benchmark::State &st) {
  for (auto _ : st) {
    benchmark::DoNotOptimize(st.name());
  }
}
BENCHMARK_REGISTER_F(MyFixtureTemplated, DoubleTest)->Threads(2);

static void BM_vector_push_back(benchmark::State &state) {
  for (auto _ : state) {
    std::vector<int> v;
    v.reserve(1);
    // Allow v.data() to be clobbered. Pass as non-const
    auto data = v.data();
    // lvalue to avoid undesired compiler optimizations
    benchmark::DoNotOptimize(data);
    v.push_back(42);
    // Force the compiler to write 42 to memory.
    benchmark::ClobberMemory();
  }
}
BENCHMARK(BM_vector_push_back);

BENCHMARK_MAIN();