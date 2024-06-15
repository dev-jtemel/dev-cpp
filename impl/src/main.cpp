
#include "devcpp/log/Journal.hpp"
#include "devcpp/log/Sink.hpp"

int main() {
  devcpp::log::Journal j;
  j.registerSink(std::make_unique<devcpp::log::SinkImpl<std::ostream>>(
      devcpp::log::SinkImpl<std::ostream>(std::cout)));

  j << "Test log";
  return 0;
}