
#define DEVCPP_LOG_JOURNAL_HPP
#include "devcpp/log/journal_impl.hpp"
#undef DEVCPP_LOG_JOURNAL_HPP

namespace devcpp {
namespace log {

journal::~journal() {
  if (m_ss.str().empty()) {
    return;
  }

  for (const auto& sink : m_sinks) {
    sink->write(m_ss.str());
    sink->flush();
  }
}

journal& journal::lock() {
  m_mutex.lock();
  return *this;
}

void journal::unlock_and_write() {
  const std::string fs{m_ss.str() + "\n"};
  const auto flush = m_flush.exchange(false, std::memory_order_acquire);
  m_ss.str("");
  m_mutex.unlock();

  for (const auto& sink : m_sinks) {
    sink->write(fs);
    if (flush) {
      sink->flush();
    }
  }
}

journal& operator<<(journal& journal, const journal::severity lvl) {
  auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::time_point_cast<std::chrono::milliseconds>(
                    std::chrono::system_clock::now())
                    .time_since_epoch())
                .count();
  auto tid = std::this_thread::get_id();

  if (lvl >= journal::severity::warn) {
    journal.m_flush.store(true, std::memory_order_release);
  }

  journal.m_ss << "[" << ms << "] [0x" << std::hex << tid << std::dec << "] "
               << journal.severity_string(lvl) << " ";
  return journal;
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