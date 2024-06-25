
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

void journal::unlock() {
  if (m_flush_pending) {
    std::string fs{m_ss.str()};
    m_ss.str("");
    m_lock.unlock();
    
    m_flush_pending = false;
    for (const auto& sink : m_sinks) {
      sink->write(fs);
    }
    return;
  }
  m_lock.unlock();
}

void journal::register_sink(std::unique_ptr<sink>&& sink) {
  m_sinks.emplace_back(std::move(sink));
}

journal& operator<<(journal& journal, const journal::severity lvl) {
  auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::time_point_cast<std::chrono::milliseconds>(
                    std::chrono::system_clock::now())
                    .time_since_epoch())
                .count();
  auto tid = std::this_thread::get_id();

  if (lvl >= journal::severity::warn) {
    journal.m_flush_pending = true;
  }

  journal.m_ss << "[" << ms << "] [0x" << std::hex << tid << std::dec << "] "
               << journal.severity_string(lvl) << " ";
  return journal;
}

bool journal::should_log(severity level) const { return level >= m_logLevel; }

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