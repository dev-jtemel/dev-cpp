
#ifndef DEVCPP_THREAD_DUMMY_MUTEX_HPP
#define DEVCPP_THREAD_DUMMY_MUTEX_HPP

#include "devcpp/types/class_types.hpp"

namespace devcpp {
namespace thread {

class dummy_mutex : types::non_copyable {
 public:
  dummy_mutex() = default;
  ~dummy_mutex() = default;

  void lock() {}
  void unlock() {}
};

}  // namespace thread
}  // namespace devcpp

#endif  // DEVCPP_THREAD_DUMMY_MUTEX_HPP