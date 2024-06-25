
#include "devcpp/log/journal.hpp"
#include "devcpp/log/sink.hpp"

int main() {
  auto& instance = devcpp::log::journal::instance();
  instance.register_sink(std::make_unique<devcpp::log::sink_impl<std::ostream>>(
      devcpp::log::sink_impl<std::ostream>(std::cout)));

  DEVCPP_LOG_TRACE("trace");
  DEVCPP_LOG_DEBUG("debug");
  DEVCPP_LOG_INFO("info");
  DEVCPP_LOG_WARN("warn");
  DEVCPP_LOG_ERROR("error");
  DEVCPP_LOG_FATAL("fatal");
  
  return 0;
}