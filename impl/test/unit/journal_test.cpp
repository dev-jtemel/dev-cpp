
#include "devcpp/log/journal.hpp"

#include <gtest/gtest.h>

#include "devcpp/types/common.hpp"
#include "mocks/sink_mock.hpp"

namespace devcpp {
namespace log {
namespace test {

class journal_test : public ::testing::Test {
 protected:
  void SetUp() override {
    m_sink = std::make_shared<sink_mock>();
    journal::instance().register_sink(m_sink);
    ASSERT_EQ(journal::instance().m_sinks.size(), 2);
  }

  void TearDown() override {
    journal::instance().m_sinks.pop_back();
    ASSERT_EQ(journal::instance().m_sinks.size(), 1);
  }

  std::shared_ptr<sink_mock> m_sink;
};

// Test the singleton instance
TEST_F(journal_test, singletonInstance) {
  journal& instance1 = journal::instance();
  journal& instance2 = journal::instance();
  EXPECT_EQ(&instance1, &instance2);
}

// Test logging with different severity levels
TEST_F(journal_test, logging) {
  EXPECT_CALL(*m_sink, write(testing::HasSubstr("Test message"))).Times(6);
  EXPECT_CALL(*m_sink, flush()).Times(3);
  LOG_TRACE("Test message");
  LOG_DEBUG("Test message");
  LOG_INFO("Test message");
  LOG_WARN("Test message");
  LOG_ERROR("Test message");
  LOG_FATAL("Test message");
}

// Test locking and unlocking
TEST_F(journal_test, lockAndUnlock) {
  EXPECT_CALL(*m_sink, write(testing::HasSubstr("Test message"))).Times(1);
  journal::instance().lock() << "Test message";
  journal::instance().unlock_and_write();

  // No specific assert, just ensure no deadlock or crash
}

// Test severity string conversion
TEST_F(journal_test, severityString) {
  journal& log = journal::instance();
  EXPECT_EQ(log.severity_string(journal::severity::trace), "[trace]");
  EXPECT_EQ(log.severity_string(journal::severity::debug), "[debug]");
  EXPECT_EQ(log.severity_string(journal::severity::info), "[info ]");
  EXPECT_EQ(log.severity_string(journal::severity::warn), "[warn ]");
  EXPECT_EQ(log.severity_string(journal::severity::error), "[error]");
  EXPECT_EQ(log.severity_string(journal::severity::fatal), "[fatal]");
  EXPECT_EQ(log.severity_string(static_cast<journal::severity>(12U)), "[?????]");
}

// Test clearing the stream after write
TEST_F(journal_test, clearStreamAfterWrite) {
  EXPECT_CALL(*m_sink, write(testing::HasSubstr("message"))).Times(2);
  EXPECT_CALL(*m_sink, flush()).Times(1);
  LOG_TRACE("First message");
  LOG_WARN("Second message");
  ASSERT_EQ(journal::instance().m_ss.str(), "");
}

// Test thread safety
TEST_F(journal_test, threadSafety) {
  constexpr std::size_t k_times = 10U;
  constexpr std::size_t k_fatal = 1U;
  constexpr std::size_t k_nthread = 2U;
  EXPECT_CALL(*m_sink, write(testing::HasSubstr("thread")))
      .Times((k_times + k_fatal) * k_nthread);
  EXPECT_CALL(*m_sink, flush()).Times(k_nthread);

  auto logging_function = [k_times]() {
    for (int i = 0; i < k_times; ++i) {
      LOG_INFO("Logging from thread");
    }
    LOG_FATAL("Logging from thread");
  };

  std::thread t1(logging_function);
  std::thread t2(logging_function);

  t1.join();
  t2.join();
}

// Test large messages
TEST_F(journal_test, largeMessages) {
  // Avoid spam
  journal::instance().m_sinks.erase(journal::instance().m_sinks.begin());
  ASSERT_EQ(journal::instance().m_sinks.size(), 1);

  std::string large_message(10000, 'A');
  EXPECT_CALL(*m_sink, write(testing::_)).Times(1);

  journal::instance().lock() << large_message;
  journal::instance().unlock_and_write();

  // Reinstate the console
  journal::instance().m_sinks.insert(
      journal::instance().m_sinks.begin(),
      std::make_shared<devcpp::log::sink_impl<std::ostream>>(
          devcpp::log::sink_impl<std::ostream>(std::cout)));
}

// Test empty messages
TEST_F(journal_test, emptyMessages) {
  EXPECT_CALL(*m_sink, write(testing::HasSubstr(""))).Times(1);

  journal::instance().lock() << "";
  journal::instance().unlock_and_write();
}

// Test registering null sink
TEST_F(journal_test, registerNullSink) {
  journal::instance().register_sink(nullptr);
  ASSERT_EQ(journal::instance().m_sinks.size(), 2);
}


}  // namespace test
}  // namespace log
}  // namespace devcpp