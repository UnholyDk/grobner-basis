#include <algorithm>
#include <array>
#include <iostream>
#include <string>
#include <vector>


using deg_value_type = int;
using number_of_variables_type = size_t;
const number_of_variables_type numberVariables = 26;
using deg_container_type = std::array<deg_value_type, numberVariables>;

namespace grobner {
template <class TCoefficient, number_of_variables_type TNumberOfVariables>
class Monomial {
  using deg_container_type = std::array<deg_value_type, TNumberOfVariables>;

 public:
  Monomial(TCoefficient coefficient) : coefficient_(std::move(coefficient)){};

  Monomial(TCoefficient coefficient, deg_container_type &degrees)
      : coefficient_(std::move(coefficient)) {
    for (size_t i = 0; i < std::min(degrees.size(), size_t(TNumberOfVariables));
         ++i) {
      degrees_[i] = degrees[i];
    }
  };

  auto begin() const { return degrees_.begin(); }

  auto end() const { return degrees_.end(); }

  auto rbegin() const { return degrees_.rbegin(); }

  auto rend() const { return degrees_.rend(); }

  TCoefficient get_coefficient() const { return coefficient_; }

  int operator[](size_t i) const {
    if (0 <= i && i < TNumberOfVariables) return degrees_[i];
    return 0;
  }

  int &operator[](size_t i) { return degrees_[i]; }

  bool is_equal(const Monomial<TCoefficient, TNumberOfVariables> &other) const {
    for (size_t i = 0; i < TNumberOfVariables; ++i) {
      if (degrees_[i] != other[i]) {
        return 0;
      }
    }
    return 1;
  }

  bool is_div(const Monomial<TCoefficient, TNumberOfVariables> &other) const {
    for (size_t i = 0; i < TNumberOfVariables; ++i) {
      if (degrees_[i] < other[i]) {
        return false;
      }
    }
    return true;
  }

  Monomial<TCoefficient, TNumberOfVariables> &operator*=(
      const TCoefficient &x) {
    coefficient_ *= x;
    return *this;
  }

  Monomial<TCoefficient, TNumberOfVariables> operator*(
      const TCoefficient &x) const {
    Monomial<TCoefficient, TNumberOfVariables> tmp_m = *this;
    return tmp_m *= x;
  }

  Monomial<TCoefficient, TNumberOfVariables> &operator*=(
      const Monomial<TCoefficient, TNumberOfVariables> &other) {
    coefficient_ *= other.get_coefficient();
    for (size_t i = 0; i < TNumberOfVariables; ++i) {
      degrees_[i] += other[i];
    }
    return *this;
  }

  Monomial<TCoefficient, TNumberOfVariables> operator*(
      const Monomial<TCoefficient, TNumberOfVariables> &other) const {
    Monomial<TCoefficient, TNumberOfVariables> tmp_m = *this;
    return tmp_m *= other;
  }

  Monomial<TCoefficient, TNumberOfVariables> &operator+=(
      const Monomial<TCoefficient, TNumberOfVariables> &other) {
    coefficient_ += other.get_coefficient();
    return *this;
  }

  Monomial<TCoefficient, TNumberOfVariables> operator+(
      const Monomial<TCoefficient, TNumberOfVariables> &other) const {
    Monomial<TCoefficient, TNumberOfVariables> tmp_m;
    return tmp_m += other;
  }

  Monomial<TCoefficient, TNumberOfVariables> operator/(
      const Monomial<TCoefficient, TNumberOfVariables> &other) const {
    deg_container_type degrees;
    for (size_t i = 0; i < TNumberOfVariables; ++i) {
      degrees[i] = degrees_[i] - other[i];
    }
    return Monomial(coefficient_ / other.get_coefficient(), degrees);
  }

  bool operator==(
      const Monomial<TCoefficient, TNumberOfVariables> &other) const {
    return is_equal(other);
  }

  bool operator!=(
      const Monomial<TCoefficient, TNumberOfVariables> &other) const {
    return !(is_equal(other));
  }

 private:
  TCoefficient coefficient_;
  deg_container_type degrees_;
};

void print_variable(std::ostream &os, size_t i, deg_value_type deg) {
  os << char('a' + i);
  if (deg != 1) os << '^' << deg;
}

template <class TCoefficient, number_of_variables_type TNumberOfVariables>
void print_variables(std::ostream &os,
                     Monomial<TCoefficient, TNumberOfVariables> const &m) {
  size_t i = 0;
  for (auto &deg : m) {
    if (deg != 0) print_variable(os, i, deg);
    ++i;
  }
}
}  // namespace grobner

template <class TCoefficient, number_of_variables_type TNumberOfVariables>
std::ostream &operator<<(
    std::ostream &os,
    grobner::Monomial<TCoefficient, TNumberOfVariables> const &m) {
  if (m.get_coefficient() <= 0)
    os << m.get_coefficient();
  else
    os << '+' << m.get_coefficient();
  if (m.get_coefficient() != 0) grobner::print_variables(os, m);
  return os;
}
