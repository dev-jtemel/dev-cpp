
#include "devcpp/log/Journal.hpp"

namespace devcpp {
namespace log {

bool Journal::shouldLog(LogLevel level) const { return level >= m_logLevel; }

bool Journal::shouldFlush(LogLevel level) const {
  return level >= LogLevel::kWarning;
}

}  // namespace log
}  // namespace devcpp