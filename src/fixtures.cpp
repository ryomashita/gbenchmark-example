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

BENCHMARK_MAIN();