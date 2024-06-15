
#ifndef DEVCPP_TYPES_CLASS_TYPES_HPP
#define DEVCPP_TYPES_CLASS_TYPES_HPP

namespace devcpp {
namespace types {

class NonCopyable {
 public:
  NonCopyable() = default;
  ~NonCopyable() = default;

  NonCopyable(const NonCopyable&) = delete;
  NonCopyable& operator=(const NonCopyable&) = delete;

  NonCopyable(NonCopyable&&) = default;
  NonCopyable& operator=(NonCopyable&&) = default;
};

}  // namespace types
}  // namespace devcpp

#endif  // DEVCPP_TYPES_CLASS_TYPES_HPP