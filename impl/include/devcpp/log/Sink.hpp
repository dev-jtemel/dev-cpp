
#ifndef DEVCPP_LOG_SINK_HPP
#define DEVCPP_LOG_SINK_HPP

#include <iostream>
#include <type_traits>

#include "devcpp/types/ClassTypes.hpp"

namespace devcpp {
namespace log {

class Sink : public types::NonCopyable {
 public:
  virtual void write() = 0;
};

template <typename STREAM_TYPE>
class SinkImpl : public Sink {
  using StreamType = STREAM_TYPE;

  static_assert(std::is_base_of_v<StreamType, std::ostream>,
                "STREAM_TYPE must be derived from std::ostream");

 public:
  SinkImpl(StreamType& stream) : m_stream(stream) {}

  void write() override {}

 private:
  StreamType& m_stream;
};

SinkImpl<std::ostream> stream(std::cout);

}  // namespace log
}  // namespace devcpp

#endif  // DEVCPP_LOG_SINK_HPP