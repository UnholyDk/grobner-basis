#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using deg_value_type = int;
using deg_container_type = std::vector<deg_value_type>;

namespace grobner {
template <typename T>
class Monomial {
 public:
  Monomial(T coefficient) : coefficient_(std::move(coefficient)) {
    degrees_.resize(26);
  };

  Monomial(T coefficient, deg_container_type &degrees)
      : coefficient_(std::move(coefficient)) {
    degrees_.resize(26);
    for (size_t i = 0; i < std::min(degrees.size(), size_t(26)); ++i) {
      degrees_[i] = degrees[i];
    }
  };

  auto begin() const { return degrees_.begin(); }

  auto end() const { return degrees_.end(); }

  auto rbegin() const { return degrees_.rbegin(); }

  auto rend() const { return degrees_.rend(); }

  T get_coefficient() const { return coefficient_; }

  int operator[](size_t i) const { return degrees_[i]; }

  int &operator[](size_t i) { return degrees_[i]; }

  bool is_equal(const Monomial<T> &other) const {
    for (size_t i = 0; i < 26; ++i) {
      if (degrees_[i] != other[i]) {
        return 0;
      }
    }
    return 1;
  }

  bool is_div(const Monomial<T> &other) const {
    for (size_t i = 0; i < 26; ++i) {
      if (degrees_[i] < other[i]) {
        return false;
      }
    }
    return true;
  }

  Monomial<T> &operator*=(const T &x) {
    coefficient_ *= x;
    return *this;
  }

  Monomial<T> operator*(const T &x) const {
    Monomial<T> tmp_m = *this;
    return tmp_m *= x;
  }

  Monomial<T> &operator*=(const Monomial<T> &other) {
    coefficient_ *= other.get_coefficient();
    for (size_t i = 0; i < 26; ++i) {
      degrees_[i] += other[i];
    }
    return *this;
  }

  Monomial<T> operator*(const Monomial<T> &other) const {
    Monomial<T> tmp_m = *this;
    return tmp_m *= other;
  }

  Monomial<T> &operator+=(const Monomial<T> &other) {
    coefficient_ += other.get_coefficient();
    return *this;
  }

  Monomial<T> operator+(const Monomial<T> &other) const {
    Monomial<T> tmp_m;
    return tmp_m += other;
  }

  Monomial<T> operator/(const Monomial<T> &other) const {
    std::vector<int> degrees(26);
    for (size_t i = 0; i < 26; ++i) {
      degrees[i] = degrees_[i] - other[i];
    }
    return Monomial(coefficient_ / other.get_coefficient(), degrees);
  }

  bool operator==(const Monomial<T> &other) const { return is_equal(other); }

  bool operator!=(const Monomial<T> &other) const { return !(is_equal(other)); }

 private:
  T coefficient_;
  deg_container_type degrees_;
};

void print_variable(std::ostream &os, size_t i, deg_value_type deg) {
  os << char('a' + i);
  if (deg != 1) os << '^' << deg;
}

template <typename T>
void print_variables(std::ostream &os, Monomial<T> const &m) {
  size_t i = 0;
  for (auto &x : m) {
    if (x != 0) print_variable(os, i, x);
    ++i;
  }
}
}  // namespace grobner

template <typename T>
std::ostream &operator<<(std::ostream &os, grobner::Monomial<T> const &m) {
  if (m.get_coefficient() <= 0)
    os << m.get_coefficient();
  else
    os << '+' << m.get_coefficient();
  if (m.get_coefficient() != 0) grobner::print_variables(os, m);
  return os;
}
