
#ifndef DEVCPP_LOG_JOURNAL_HPP
#define DEVCPP_LOG_JOURNAL_HPP

#include "devcpp/log/journal_impl.hpp"

namespace devcpp {
namespace log {

#define DEVCPP_LOG_TRACE(expr) \
  DEVCPP_INTERNAL_LOG(devcpp::log::journal::severity::trace, expr)
#define DEVCPP_LOG_DEBUG(expr) \
  DEVCPP_INTERNAL_LOG(devcpp::log::journal::severity::debug, expr)
#define DEVCPP_LOG_INFO(expr) \
  DEVCPP_INTERNAL_LOG(devcpp::log::journal::severity::info, expr)
#define DEVCPP_LOG_WARN(expr) \
  DEVCPP_INTERNAL_LOG(devcpp::log::journal::severity::warn, expr)
#define DEVCPP_LOG_ERROR(expr) \
  DEVCPP_INTERNAL_LOG(devcpp::log::journal::severity::error, expr)
#define DEVCPP_LOG_FATAL(expr) \
  DEVCPP_INTERNAL_LOG(devcpp::log::journal::severity::fatal, expr)

}  // namespace log
}  // namespace devcpp

#endif  // DEVCPP_LOG_JOURNAL_HPP