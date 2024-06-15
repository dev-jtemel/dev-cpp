
#ifndef DEVCPP_LOG_JOURNAL_HPP
#define DEVCPP_LOG_JOURNAL_HPP

#include <cstdint>
#include <memory>
#include <vector>

#include "devcpp/log/Sink.hpp"
#include "devcpp/types/ClassTypes.hpp"

namespace devcpp {
namespace log {

constexpr size_t kBufferSize = 255UL;

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
  void registerSink(std::unique_ptr<ISink>&& sink);

 private:
  bool shouldLog(LogLevel lvl) const;

  /**
   * @brief Flush on kWarning or higher.
   */
  bool shouldFlush(LogLevel lvl) const;

  std::vector<std::string> m_buffer{kBufferSize};
  std::vector<std::unique_ptr<ISink>> m_sinks{};
  LogLevel m_logLevel{LogLevel::kTrace};
};

}  // namespace log
}  // namespace devcpp

#endif  // DEVCPP_LOG_JOURNAL_HPP