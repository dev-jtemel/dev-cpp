#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "devcpp/log/journal.hpp"

int main(int argc, char *argv[]) {
  devcpp::log::journal::instance().register_sink(
      std::make_shared<devcpp::log::sink_impl<std::ostream>>(
          devcpp::log::sink_impl<std::ostream>(std::cout)));

  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}