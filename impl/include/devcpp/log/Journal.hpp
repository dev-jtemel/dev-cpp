
#ifndef DEVCPP_LOG_JOURNAL_HPP
#define DEVCPP_LOG_JOURNAL_HPP

#include <cstdint>
#include <memory>
#include <sstream>
#include <vector>

#include "devcpp/log/Sink.hpp"
#include "devcpp/types/ClassTypes.hpp"

namespace devcpp {
namespace log {

enum class LogLevel : uint16_t {
  kTrace = 0U,  // Default
  kDebug = 1U,
  kInfo = 2U,
  kWarning = 3U,
  kError = 4U,
  kFatal = 5U,
  kMaxLogLevel = 15U
};

class Journal : public types::NonCopyable {
 public:
  ~Journal() {
    for (const auto& sink : m_sinks) {
      sink->write(m_ss.str());
      sink->flush();
    }
  }
  void registerSink(std::unique_ptr<ISink>&& sink);

  template <typename T>
  friend Journal& operator<<(Journal& journal, const T& data) {
    journal.m_ss << data << '\n';
    return journal;
  }

 private:
  bool shouldLog(LogLevel lvl) const;

  /**
   * @brief Flush on kWarning or higher.
   */
  bool shouldFlush(LogLevel lvl) const;

  std::ostringstream m_ss{};
  std::vector<std::unique_ptr<ISink>> m_sinks{};
  LogLevel m_logLevel{LogLevel::kTrace};
};

}  // namespace log
}  // namespace devcpp

#endif  // DEVCPP_LOG_JOURNAL_HPP