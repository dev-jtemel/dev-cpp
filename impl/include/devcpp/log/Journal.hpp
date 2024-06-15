
#ifndef DEVCPP_LOG_JOURNAL_HPP
#define DEVCPP_LOG_JOURNAL_HPP

#include <cstdint>
#include <memory>
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
  void registerSink(const std::unique_ptr<Sink>&& sink);

 private:
  bool shouldLog(LogLevel lvl) const;

  /**
   * @brief Flush on kWarning or higher.
   */
  bool shouldFlush(LogLevel lvl) const;

  std::vector<std::unique_ptr<Sink>> m_sinks{};
  LogLevel m_logLevel{LogLevel::kTrace};
};

}  // namespace log
}  // namespace devcpp

#endif  // DEVCPP_LOG_JOURNAL_HPP