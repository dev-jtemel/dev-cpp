
#include <chrono>
#include <thread>
#include <vector>

#include "devcpp/log/journal.hpp"
#include "devcpp/log/sink.hpp"
#include "devcpp/thread/sync_value.hpp"

const int NUM_THREADS = 100;
const int NUM_ITERATIONS = 100;

void incrementCounter(int& counter) {
  for (int i = 0; i < NUM_ITERATIONS; ++i) {
    int temp = counter;
    std::this_thread::sleep_for(std::chrono::microseconds(5));
    counter = temp + 1;
  }
}

void incrementCounterSyncValue(devcpp::thread::sync_value<int>& counterSync) {
  for (int i = 0; i < NUM_ITERATIONS; ++i) {
    auto counter = counterSync.sync();
    int temp = counter();
    std::this_thread::sleep_for(std::chrono::microseconds(5));
    counter() = temp + 1;
  }
}

struct Test {
  template <typename T, typename V = bool>
  void log(double v) {
    T t{};
    LOG_METHOD_ENTER("Enter " << t << " " << v);

    LOG_METHOD_TRACE("trace " << t << " " << v);
    LOG_METHOD_DEBUG("debug " << t << " " << v);
    LOG_METHOD_INFO("info " << t << " " << v);
    LOG_METHOD_WARN("warn " << t << " " << v);
    LOG_METHOD_ERROR("error " << t << " " << v);
    LOG_METHOD_FATAL("fatal " << t << " " << v);

    LOG_METHOD_EXIT("Exit " << t << " " << v);
  }
};

int main() {
  auto& instance = devcpp::log::journal::instance();
  instance.register_sink(std::make_unique<devcpp::log::sink_impl<std::ostream>>(
      devcpp::log::sink_impl<std::ostream>(std::cout)));

  LOG_TRACE("trace");
  LOG_DEBUG("debug");
  LOG_INFO("info");
  LOG_WARN("warn");
  LOG_ERROR("error");
  LOG_FATAL("fatal");

  Test t;
  t.log<int, std::vector<std::string>>(5.5f);

  int counter = 0;
  devcpp::thread::sync_value<int> counterSync{};
  std::vector<std::thread> threads;
  std::vector<std::thread> threadsSyncValue;
  for (int i = 0; i < NUM_THREADS; ++i) {
    threads.emplace_back(incrementCounter, std::ref(counter));
    threads.emplace_back(incrementCounterSyncValue, std::ref(counterSync));
  }

  // Wait for all threads to finish
  for (auto& thread : threads) {
    thread.join();
  }

  // Print the final value of the counter
  LOG_INFO("Final counter value: " << counter);
  LOG_INFO("Final counter value: " << counterSync.sync()());

  return 0;
}