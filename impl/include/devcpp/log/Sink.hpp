
#ifndef DEVCPP_LOG_SINK_HPP
#define DEVCPP_LOG_SINK_HPP

#include <iostream>
#include <type_traits>

#include "devcpp/types/ClassTypes.hpp"

namespace devcpp {
namespace log {

class ISink : public types::NonCopyable {
 public:
  virtual void write(const std::string&) {
  };
  virtual void flush() {};
};

template <typename STREAM_TYPE>
class SinkImpl : public ISink {
  using StreamType = STREAM_TYPE;

  static_assert(std::is_base_of_v<StreamType, std::ostream>,
                "STREAM_TYPE must be derived from std::ostream");

 public:
  SinkImpl(StreamType& stream) : m_stream(stream) {}

  void write(const std::string& msg) override { m_stream << msg; }
  void flush() override { m_stream.flush(); }

 private:
  StreamType& m_stream;
};

}  // namespace log
}  // namespace devcpp

#endif  // DEVCPP_LOG_SINK_HPP