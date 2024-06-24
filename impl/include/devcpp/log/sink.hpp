
#ifndef DEVCPP_LOG_SINK_HPP
#define DEVCPP_LOG_SINK_HPP

#include <iostream>
#include <type_traits>

#include "devcpp/types/class_types.hpp"

namespace devcpp {
namespace log {

class sink : public types::non_copyable {
 public:
  virtual void write(const std::string&) {
  };
  virtual void flush() {};
};

template <typename STREAM_TYPE>
class sink_impl : public sink {
  using stream_type = STREAM_TYPE;

  static_assert(std::is_base_of_v<stream_type, std::ostream>,
                "STREAM_TYPE must be derived from std::ostream");

 public:
  sink_impl(stream_type& stream) : m_stream(stream) {}

  void write(const std::string& msg) override { m_stream << msg; }
  void flush() override { m_stream.flush(); }

 private:
  stream_type& m_stream;
};

}  // namespace log
}  // namespace devcpp

#endif  // DEVCPP_LOG_SINK_HPP