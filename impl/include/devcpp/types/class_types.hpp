
#ifndef DEVCPP_TYPES_CLASS_TYPES_HPP
#define DEVCPP_TYPES_CLASS_TYPES_HPP

namespace devcpp {
namespace types {

class non_copyable {
 public:
  non_copyable() = default;
  ~non_copyable() = default;

  non_copyable(const non_copyable&) = delete;
  non_copyable& operator=(const non_copyable&) = delete;

  non_copyable(non_copyable&&) = default;
  non_copyable& operator=(non_copyable&&) = default;
};

template <class C>
class singleton : public non_copyable {
 public:
  static C& instance() {
    static C instance;
    return instance;
  }

 protected:
  singleton() = default;
  virtual ~singleton() = default;
};

}  // namespace types
}  // namespace devcpp

#endif  // DEVCPP_TYPES_CLASS_TYPES_HPP