
#include "devcpp/log/journal.hpp"

namespace devcpp {
namespace log {

journal::~journal() {
  for (const auto& sink : m_sinks) {
    sink->write(m_ss.str());
    sink->flush();
  }
}

journal& journal::lock() {
  m_lock.lock();
  return *this;
}

void journal::unlock() { m_lock.unlock(); }

void journal::register_sink(std::unique_ptr<sink>&& sink) {
  m_sinks.emplace_back(std::move(sink));
}

bool journal::should_log(severity level) const { return level >= m_logLevel; }

bool journal::should_flush(severity level) const {
  return level >= severity::warn;
}

std::string journal::severity_string(severity lvl) const {
  switch (lvl) {
    case severity::trace:
      return "[trace]";
    case severity::debug:
      return "[debug]";
    case severity::info:
      return "[info ]";
    case severity::warn:
      return "[warn ]";
    case severity::error:
      return "[error]";
    case severity::fatal:
      return "[fatal]";
    default:
      return "[?????]";
  }
}

}  // namespace log
}  // namespace devcpp