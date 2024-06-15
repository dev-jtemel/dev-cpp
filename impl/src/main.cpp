
#include "devcpp/log/Journal.hpp"
#include "devcpp/log/Sink.hpp"

int main() {
  devcpp::log::Journal j;
  j.registerSink(std::make_unique<devcpp::log::ISink>(
      devcpp::log::SinkImpl<std::ostream>(std::cout)));
  return 0;
}