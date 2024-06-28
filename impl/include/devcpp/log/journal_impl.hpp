
#ifndef DEVCPP_LOG_JOURNAL_IMPL_HPP
#define DEVCPP_LOG_JOURNAL_IMPL_HPP

#ifndef DEVCPP_LOG_JOURNAL_HPP
#error "Do not include this file directly. Use <devcpp/log/journal.hpp>"
#endif

#include <atomic>
#include <chrono>
#include <cstdint>
#include <iomanip>
#include <memory>
#include <mutex>
#include <sstream>
#include <thread>
#include <vector>

#include "devcpp/log/sink.hpp"
#include "devcpp/types/class_types.hpp"
#include "devcpp/types/common.hpp"

namespace devcpp {
namespace log {

#define DEVCPP_INTERNAL_LOG(severity, expr)                     \
  (devcpp::log::journal::instance().lock() << severity << expr) \
      .unlock_and_write()

class journal {
 public:
  enum class severity : uint16_t {
    trace = 0U,  // Default
    debug = 1U,
    info = 2U,
    warn = 3U,
    error = 4U,
    fatal = 5U,
    max_log_level = 15U
  };

  static journal& instance() {
    static journal instance;
    return instance;
  }

  ~journal();

  template <typename F>
  void register_sink(F&& sink) {
    if (sink) {
      m_sinks.emplace_back(std::forward<F>(sink));
    }
  }

  journal& lock();
  void unlock_and_write();

  template <typename T>
  friend journal& operator<<(journal& journal, const T& data) {
    journal.m_ss << data;
    return journal;
  }
  friend journal& operator<<(journal& journal, const severity lvl);

  DEVCPP_PRIVATE
  journal() = default;

  std::string severity_string(severity lvl) const;

  std::atomic<bool> m_flush{false};
  std::mutex m_mutex{};
  std::ostringstream m_ss;
  std::vector<std::shared_ptr<sink>> m_sinks{};
  severity m_logLevel{severity::trace};
};

}  // namespace log
}  // namespace devcpp

#endif  // DEVCPP_LOG_JOURNAL_IMPL_HPP