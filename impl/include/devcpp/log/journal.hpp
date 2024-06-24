
#ifndef DEVCPP_LOG_journal_HPP
#define DEVCPP_LOG_journal_HPP

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

class journal : public types::singleton<journal> {
 public:
  enum class severity : uint16_t {
    trace = 0U,  // Default
    debug = 1U,
    info = 2U,
    warning = 3U,
    error = 4U,
    fatal = 5U,
    max_log_level = 15U
  };

  ~journal();

  void register_sink(std::unique_ptr<sink>&& sink);

  template <typename T>
  friend journal& operator<<(journal& journal, const T& data) {
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                  std::chrono::time_point_cast<std::chrono::milliseconds>(
                      std::chrono::system_clock::now())
                      .time_since_epoch())
                  .count();
    auto tid = std::this_thread::get_id();

    std::lock_guard<std::mutex> guard(journal.m_lock);
    journal.m_ss << "[" << ms << "] [0x" << std::hex << tid << std::dec << "] "
                 << data << '\n';
    return journal;
  }

 private:
  bool should_log(severity lvl) const;
  std::ostringstream& log_prefix(severity lvl);
  std::string severity_string(severity lvl) const;

  /**
   * @brief Flush on kWarning or higher.
   */
  bool should_flush(severity lvl) const;

  std::mutex m_lock{};
  std::ostringstream m_ss{};
  std::vector<std::unique_ptr<sink>> m_sinks{};
  severity m_logLevel{severity::trace};
};

}  // namespace log
}  // namespace devcpp

#endif  // DEVCPP_LOG_journal_HPP