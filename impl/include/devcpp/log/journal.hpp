
#ifndef DEVCPP_LOG_JOURNAL_HPP
#define DEVCPP_LOG_JOURNAL_HPP

#include <source_location>

#include "devcpp/log/journal_impl.hpp"

namespace devcpp {
namespace log {

#define LOG_TRACE(expr) \
  DEVCPP_INTERNAL_LOG(devcpp::log::journal::severity::trace, expr)
#define LOG_DEBUG(expr) \
  DEVCPP_INTERNAL_LOG(devcpp::log::journal::severity::debug, expr)
#define LOG_INFO(expr) \
  DEVCPP_INTERNAL_LOG(devcpp::log::journal::severity::info, expr)
#define LOG_WARN(expr) \
  DEVCPP_INTERNAL_LOG(devcpp::log::journal::severity::warn, expr)
#define LOG_ERROR(expr) \
  DEVCPP_INTERNAL_LOG(devcpp::log::journal::severity::error, expr)
#define LOG_FATAL(expr) \
  DEVCPP_INTERNAL_LOG(devcpp::log::journal::severity::fatal, expr)

#define LOG_METHOD_ENTER(...) \
  LOG_TRACE(__PRETTY_FUNCTION__ << " :: enter " __VA_ARGS__)
#define LOG_METHOD_EXIT(...) \
  LOG_TRACE(__PRETTY_FUNCTION__ << " :: exit " __VA_ARGS__)
#define LOG_METHOD_TRACE(...) \
  LOG_TRACE(__PRETTY_FUNCTION__ << " :: " __VA_ARGS__)
#define LOG_METHOD_DEBUG(...) \
  LOG_DEBUG(__PRETTY_FUNCTION__ << " :: " __VA_ARGS__)
#define LOG_METHOD_INFO(...) LOG_INFO(__PRETTY_FUNCTION__ << " :: " __VA_ARGS__)
#define LOG_METHOD_WARN(...) LOG_WARN(__PRETTY_FUNCTION__ << " :: " __VA_ARGS__)
#define LOG_METHOD_ERROR(...) \
  LOG_ERROR(__PRETTY_FUNCTION__ << " :: " __VA_ARGS__)
#define LOG_METHOD_FATAL(...) \
  LOG_FATAL(__PRETTY_FUNCTION__ << " :: " __VA_ARGS__)

}  // namespace log
}  // namespace devcpp

#endif  // DEVCPP_LOG_JOURNAL_HPP