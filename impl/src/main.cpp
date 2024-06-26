
#include "devcpp/log/journal.hpp"
#include "devcpp/log/sink.hpp"

struct Test {
  template <typename T, typename V = bool>
  void log(double v) {
    T t{};
    LOG_METHOD_ENTER("Enter " << t << " " << v);

    LOG_METHOD_TRACE("trace " << t << " " << v);
    LOG_METHOD_DEBUG("debug " << t << " " << v);
    LOG_METHOD_INFO("info " << t << " " << v);
    LOG_METHOD_WARN("warn " << t << " " << v);
    LOG_METHOD_ERROR("error " << t << " " << v);
    LOG_METHOD_FATAL("fatal " << t << " " << v);

    LOG_METHOD_EXIT("Exit " << t << " " << v);
  }
};

int main() {
  auto& instance = devcpp::log::journal::instance();
  instance.register_sink(std::make_unique<devcpp::log::sink_impl<std::ostream>>(
      devcpp::log::sink_impl<std::ostream>(std::cout)));

  LOG_TRACE("trace");
  LOG_DEBUG("debug");
  LOG_INFO("info");
  LOG_WARN("warn");
  LOG_ERROR("error");
  LOG_FATAL("fatal");

  Test t;
  t.log<int, std::vector<std::string>>(5.5f);

  return 0;
}