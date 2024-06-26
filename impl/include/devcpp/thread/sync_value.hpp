
#ifndef DEVCPP_THREAD_SYNC_VALUE_HPP
#define DEVCPP_THREAD_SYNC_VALUE_HPP

#include <mutex>

#include "devcpp/log/journal.hpp"

namespace devcpp {
namespace thread {

template <typename VALUE, typename MUTEX = std::mutex>
class sync_ptr {
 public:
  using mutex_type = MUTEX;
  using value_type = VALUE;

  sync_ptr(value_type& v, mutex_type& m) : m_mutex{m}, m_value{v} {
    m_mutex.lock();
  }
  ~sync_ptr() { m_mutex.unlock(); }

  value_type& operator()() { return m_value; }
  value_type& operator*() { return m_value; }
  value_type* operator->() { return &m_value; }

 private:
  mutex_type& m_mutex;
  value_type& m_value;
};

template <typename VALUE, typename MUTEX = std::mutex>
class sync_value {
 public:
  using mutex_type = MUTEX;
  using value_type = VALUE;

  sync_value() = default;
  ~sync_value() = default;

  sync_value(const sync_value& other) {
    std::lock_guard<mutex_type> lock(other.m_mutex);
    m_value = other.m_value;
  }
  sync_value(sync_value&& other) {
    std::lock_guard<mutex_type> lock(other.m_mutex);
    m_value = std::move(other.m_value);
  }

  sync_value(value_type& v) : m_value{v} {}
  sync_value(value_type&& v) : m_value{std::move(v)} {}

  sync_value& operator=(const sync_value& other) {
    if (this != &other) {
      std::lock_guard<mutex_type> lock_this(m_mutex, std::defer_lock);
      std::lock_guard<mutex_type> lock_other(other.m_mutex, std::defer_lock);
      std::lock(lock_this, lock_other);
      m_value = other.m_value;
    }
    return *this;
  }

  sync_value& operator=(sync_value&& other) noexcept {
    if (this != &other) {
      std::lock_guard<mutex_type> lock_this(m_mutex, std::defer_lock);
      std::lock_guard<mutex_type> lock_other(other.m_mutex, std::defer_lock);
      std::lock(lock_this, lock_other);
      m_value = std::move(other.m_value);
    }
    return *this;
  }

  sync_ptr<value_type, mutex_type> sync() {
    return sync_ptr<value_type, mutex_type>(m_value, m_mutex);
  }

  sync_ptr<value_type, mutex_type> operator->() {
    return sync();
  }

 private:
  value_type m_value{};
  mutex_type m_mutex{};
};

}  // namespace thread
}  // namespace devcpp

#endif  // DEVCPP_THREAD_SYNC_VALUE_HPP