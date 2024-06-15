
#include "devcpp/log/Journal.hpp"

namespace devcpp {
namespace log {

void Journal::registerSink(std::unique_ptr<ISink>&& sink) {
  m_sinks.emplace_back(std::move(sink));
}

bool Journal::shouldLog(LogLevel level) const { return level >= m_logLevel; }

bool Journal::shouldFlush(LogLevel level) const {
  return level >= LogLevel::kWarning;
}

}  // namespace log
}  // namespace devcpp