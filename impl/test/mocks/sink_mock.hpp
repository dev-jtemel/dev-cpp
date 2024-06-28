
#include <gmock/gmock.h>
#include "devcpp/log/sink.hpp"

namespace devcpp {
namespace log {
namespace test {

class sink_mock : public sink {
 public:
  MOCK_METHOD(void, write, (const std::string& message), (override));
  MOCK_METHOD(void, flush, (), (override));
};

}  // namespace test
}  // namespace log
}  // namespace devcpp