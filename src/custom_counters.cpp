#include <benchmark/benchmark.h>

static void UserCountersExample1(benchmark::State &state) {
  double numFoos = 0, numBars = 0, numBazs = 0;
  for (auto _ : state) {
    numFoos += 1.0;
    numBars += 2.0;
    numBazs += 3.0;
    // ... count Foo,Bar,Baz events
  }

  // use insert() to add multiple counters at once
  state.counters.insert({{"Foo", numFoos}, {"Bar", numBars}, {"Baz", numBazs}});
  // sets a simple counter
  //   state.counters["Foo"] = numFoos;
  //   state.counters["Bar"] = numBars;
  //   state.counters["Baz"] = numBazs;

  // Set the counter as a rate. It will be presented divided
  // by the duration of the benchmark.
  // Meaning: per one second, how many 'foo's are processed?
  state.counters["FooRate"] =
      benchmark::Counter(numFoos, benchmark::Counter::kIsRate);

  // Set the counter as a rate. It will be presented divided
  // by the duration of the benchmark, and the result inverted.
  // Meaning: how many seconds it takes to process one 'foo'?
  state.counters["FooInvRate"] = benchmark::Counter(
      numFoos, benchmark::Counter::kIsRate | benchmark::Counter::kInvert);

  // Set the counter as a thread-average quantity. It will
  // be presented divided by the number of threads.
  state.counters["FooAvg"] =
      benchmark::Counter(numFoos, benchmark::Counter::kAvgThreads);

  // There's also a combined flag:
  state.counters["FooAvgRate"] =
      benchmark::Counter(numFoos, benchmark::Counter::kAvgThreadsRate);

  // This says that we process with the rate of state.range(0) bytes every
  // iteration:
  state.counters["BytesProcessed"] =
      benchmark::Counter(static_cast<double>(state.range(0)),
                         benchmark::Counter::kIsIterationInvariantRate,
                         benchmark::Counter::OneK::kIs1024);
}

BENCHMARK(UserCountersExample1)->Arg(1024);

BENCHMARK_MAIN();

//  `--benchmark_counters_tabular=true` option to print the counters in a
//  tabular format (separate columns for each counter).