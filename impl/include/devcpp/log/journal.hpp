
#ifndef DEVCPP_LOG_JOURNAL_HPP
#define DEVCPP_LOG_JOURNAL_HPP

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

namespace devcpp {
namespace log {

#define DEVCPP_LOG(SEVERITY, EXPR)                                          \
  do {                                                                      \
    (devcpp::log::journal::instance().lock() << SEVERITY << EXPR).unlock(); \
  } while (0);

#define DEVCPP_LOG_TRACE(EXPR) \
  DEVCPP_LOG(devcpp::log::journal::severity::trace, EXPR)
#define DEVCPP_LOG_DEBUG(EXPR) \
  DEVCPP_LOG(devcpp::log::journal::severity::debug, EXPR)
#define DEVCPP_LOG_INFO(EXPR) \
  DEVCPP_LOG(devcpp::log::journal::severity::info, EXPR)
#define DEVCPP_LOG_WARN(EXPR) \
  DEVCPP_LOG(devcpp::log::journal::severity::warn, EXPR)
#define DEVCPP_LOG_ERROR(EXPR) \
  DEVCPP_LOG(devcpp::log::journal::severity::error, EXPR)
#define DEVCPP_LOG_FATAL(EXPR) \
  DEVCPP_LOG(devcpp::log::journal::severity::fatal, EXPR)

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

  void register_sink(std::unique_ptr<sink>&& sink);

  journal& lock();
  void unlock();

  friend journal& operator<<(journal& journal, const severity lvl) {
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                  std::chrono::time_point_cast<std::chrono::milliseconds>(
                      std::chrono::system_clock::now())
                      .time_since_epoch())
                  .count();
    auto tid = std::this_thread::get_id();

    journal.m_ss << "[" << ms << "] [0x" << std::hex << tid << std::dec << "] "
                 << journal.severity_string(lvl) << " ";
    return journal;
  }

  template <typename T>
  friend journal& operator<<(journal& journal, const T& data) {
    journal.m_ss << data << '\n';
    return journal;
  }

 private:
  journal() = default;
  bool should_log(severity lvl) const;

  std::string severity_string(severity lvl) const;

  /**
   * @brief Flush on kWarning or higher.
   */
  bool should_flush(severity lvl) const;

  std::mutex m_lock{};
  std::ostringstream m_ss;
  std::vector<std::unique_ptr<sink>> m_sinks{};
  severity m_logLevel{severity::trace};
};

}  // namespace log
}  // namespace devcpp

#endif  // DEVCPP_LOG_JOURNAL_HPP