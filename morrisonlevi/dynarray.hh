#ifndef MORRISONLEVI_DYNARRAY_HH
#define MORRISONLEVI_DYNARRAY_HH

#include <algorithm>
#include <cstddef>
#include <iterator>
#include <memory>
#include <stdexcept>

namespace morrisonlevi {

template <typename T> struct dynarray {
  using value_type = T;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;
  using reference = T &;
  using const_reference = T const &;
  using pointer = T *;
  using const_pointer = T const *;
  using iterator = pointer;
  using const_iterator = const_pointer;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

  explicit dynarray(size_t count)
      : data_(std::make_unique<T[]>(count)), size_{count} {}

  template <typename InputIt>
  dynarray(InputIt first, InputIt last) : dynarray(std::distance(first, last)) {
    std::copy_n(first, size(), begin());
  }

  dynarray(std::initializer_list<T> init) : dynarray(init.size()) {
    std::copy_n(init.begin(), size(), begin());
  }

  dynarray(const dynarray<T> &other) : dynarray(other.size()) {
    std::copy_n(other.begin(), size(), begin());
  }

  dynarray(dynarray<T> &&other) noexcept = default;

  dynarray<T> &operator=(const dynarray<T> &) = delete;
  dynarray<T> &operator=(dynarray<T> &&) = delete;

  reference at(size_type pos) {
    if (pos < size()) {
      return (*this)[pos];
    }
    throw std::out_of_range{};
  }

  const_reference at(size_type pos) const {
    if (pos < size()) {
      return (*this)[pos];
    }
    throw std::out_of_range{};
  }

  reference operator[](size_type pos) { return data_[pos]; }

  constexpr const_reference operator[](size_type pos) const {
    return data_[pos];
  }

  reference front() { return *begin(); }
  const_reference front() const { return *cbegin(); }

  reference back() { return data_[size() - 1]; }
  const_reference back() const { return data_[size() - 1]; }

  pointer data() noexcept { return data_.get(); }
  const_pointer data() const noexcept { return data_.get(); }

  iterator begin() noexcept { return data_.get(); }
  const_iterator begin() const noexcept { return data_.get(); }
  const_iterator cbegin() const noexcept { return data_.get(); }

  iterator end() noexcept { return data_.get() + size(); }
  const_iterator end() const noexcept { return data_.get() + size(); }
  const_iterator cend() const noexcept { return data_.get() + size(); }

  reverse_iterator rbegin() noexcept { return {end() - 1}; }
  const_reverse_iterator rbegin() const noexcept { return {end() - 1}; }
  const_reverse_iterator crbegin() const noexcept { return {end() - 1}; }

  reverse_iterator rend() noexcept { return {begin() - 1}; }
  const_reverse_iterator rend() const noexcept { return {begin() - 1}; }
  const_reverse_iterator crend() const noexcept { return {begin() - 1}; }

  bool empty() const noexcept { return size() == 0; }

  size_type size() const noexcept { return size_; }

  // is this tied to this specific object or any object of this type?
  size_type max_size() const noexcept { return size(); }

  void fill(const_reference value) { std::fill(begin(), end(), value); }

private:
  std::unique_ptr<T[]> data_;
  std::size_t size_;
};

template <typename T>
bool operator==(const dynarray<T> &lhs, const dynarray<T> &rhs) {
  return std::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <typename T>
bool operator!=(const dynarray<T> &lhs, const dynarray<T> &rhs) {
  return !(lhs == rhs);
}

template <typename T>
bool operator<(const dynarray<T> &lhs, const dynarray<T> &rhs) {
  return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
                                      rhs.end());
}

template <typename T>
bool operator<=(const dynarray<T> &lhs, const dynarray<T> &rhs) {
  return lhs < rhs || lhs == rhs;
}

template <typename T>
bool operator>(const dynarray<T> &lhs, const dynarray<T> &rhs) {
  return !(lhs <= rhs);
}

template <typename T>
bool operator>=(const dynarray<T> &lhs, const dynarray<T> &rhs) {
  return !(lhs < rhs);
}
}

#endif
