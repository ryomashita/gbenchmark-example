#include <benchmark/benchmark.h>
#include <condition_variable>
#include <mutex>
#include <queue>

template <typename T> class WaitQueue {
private:
  std::queue<T> queue_{};
  std::mutex mutex_{};
  std::condition_variable cv_{};

public:
  using value_type = T;

  void push(const T &value) {
    std::lock_guard<std::mutex> lock(mutex_);
    queue_.push(value);
    cv_.notify_one(); // データが追加されたことを通知
  }

  T pop() {
    std::unique_lock<std::mutex> lock(mutex_);
    // データがない場合は待機
    cv_.wait(lock, [this] { return !queue_.empty(); });
    T value = queue_.front();
    queue_.pop();
    return value;
  }

  void Wait(T *v) {
    std::unique_lock<std::mutex> lock(mutex_);
    cv_.wait(lock, [this] { return !queue_.empty(); });
    *v = queue_.front();
    queue_.pop();
  }
};

template <class Q> void BM_Sequential(benchmark::State &state) {
  auto query_size = static_cast<int>(state.range(0));
  Q q;
  typename Q::value_type v{};
  for (auto _ : state) {
    for (int i = query_size; i--;)
      q.push(v);
    for (int e = query_size; e--;)
      q.Wait(&v);
  }
  // actually messages, not bytes:
  state.SetBytesProcessed(static_cast<int64_t>(state.iterations()) *
                          state.range(0));
}
// C++03
// BENCHMARK_TEMPLATE(BM_Sequential, WaitQueue<int>)->Range(1 << 0, 1 << 10);

// C++11 or newer, you can use the BENCHMARK macro with template parameters:
BENCHMARK(BM_Sequential<WaitQueue<int>>)->Range(1 << 0, 1 << 10);

template <class Q>
void BM_Sequential_With_Step(benchmark::State &state, int step) {
  auto query_size = static_cast<int>(state.range(0));
  Q q;
  typename Q::value_type v{};
  for (auto _ : state) {
    for (int i = query_size; i -= step;)
      q.push(v);
    for (int e = query_size; e -= step;)
      q.Wait(&v);
  }
  // actually messages, not bytes:
  state.SetBytesProcessed(static_cast<int64_t>(state.iterations()) *
                          state.range(0));
}

// User Guide のコードでは動作しない
// BENCHMARK_CAPTURE(BM_Sequential_With_Step<WaitQueue<int>>, Step1, 1)
//     ->RangeMultiplier(2)
//     ->Range(1 << 0, 1 << 10);

BENCHMARK_MAIN();