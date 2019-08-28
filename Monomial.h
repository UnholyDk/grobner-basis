#include <algorithm>
#include <array>
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <cassert>

namespace detail {
constexpr size_t gDefaultNumberOfVariables = 26;
}

namespace grobner {
using index_type = size_t;
template<class TCoefficient, index_type TNumberOfVariables = detail::gDefaultNumberOfVariables>
class Monomial {

 public:
  using degree_value_type = unsigned int;
  using index_type = grobner::index_type;
  using deg_container_type = std::array<degree_value_type, TNumberOfVariables>;

  Monomial(TCoefficient coefficient) : coefficient_(std::move(coefficient)) {
    degrees_.fill(0);
  };

  Monomial(TCoefficient coefficient, const deg_container_type &degrees) : coefficient_(std::move(coefficient)) {
    degrees_ = degrees;
  };
  TCoefficient &get_coefficient() { return coefficient_; }

  const TCoefficient &get_coefficient() const { return coefficient_; }

  index_type amount_of_variables() const {
    return TNumberOfVariables;
  }

  Monomial operator-() const {
    Monomial tmp = *this;
    tmp.coefficient_ = -coefficient_;
    return tmp;
  }

  degree_value_type operator[](index_type index) const {
    assert(index < degrees_.size());
    return degrees_[index];
  }

  degree_value_type &operator[](index_type index) {
    assert(index < degrees_.size());
    return degrees_[index];
  }

  bool are_variable_parts_same(const Monomial &other) const {
    return degrees_ == other.degrees_;
  }

  bool is_divisible(const Monomial &other) const {
    for (index_type i = 0; i < degrees_.size(); ++i) {
      if (degrees_[i] < other[i]) {
        return false;
      }
    }
    return true;
  }

  Monomial &operator*=(const TCoefficient &x) {
    coefficient_ *= x;
    return *this;
  }

  Monomial operator*(const TCoefficient &x) const {
    Monomial tmp = *this;
    tmp *= x;
    return tmp;
  }

  Monomial &operator*=(const Monomial &other) {
    coefficient_ *= other.get_coefficient();
    for (index_type i = 0; i < TNumberOfVariables; ++i) {
      degrees_[i] += other[i];
    }
    return *this;
  }

  Monomial operator*(const Monomial &other) const {
    Monomial tmp_m = *this;
    tmp_m *= other;
    return tmp_m;
  }

  Monomial &operator/=(const Monomial &other) {
    assert(is_divisible(other));
    for (index_type index = 0; index < degrees_.size(); ++index) {
      if (degrees_[index] < other.degrees_[index])
        throw std::invalid_argument("exception");
      degrees_[index] -= other.degrees_[index];
    }
    coefficient_ /= other.coefficient_;
    return *this;
  }

  Monomial operator/(const Monomial &other) const {
    Monomial monomial = Monomial(coefficient_, degrees_);
    monomial /= other;
    return monomial;
  }

  bool operator==(const Monomial &other) const {
    return coefficient_ == other.coefficient_ == 0 ||
        (are_variable_parts_same(other) && coefficient_ == other.coefficient_);
  }

  bool operator!=(const Monomial &other) const { return !(*this == other); }

  friend inline std::ostream &operator<<(std::ostream &os, const Monomial &monomial) {
    print_coefficient(os, monomial.get_coefficient());
    if (monomial.get_coefficient() != 0)
      print_variables(os, monomial);
    return os;
  }

 private:
  deg_container_type degrees_;

  static void print_variable(std::ostream &os, index_type index, degree_value_type deg) {
    if (deg == 0)
      return;
    os << char('a' + index);
    if (deg != 1)
      os << '^' << deg;
  }

  static void print_variables(std::ostream &os, Monomial const &monomial) {
    for (index_type index = 0; index < monomial.amount_of_variables(); ++index)
      print_variable(os, index, monomial[index]);
  }

  static void print_coefficient(std::ostream &os, TCoefficient coefficient) {
    if (coefficient == 1)
      return;
    if (coefficient == -1)
      os << '-';
    else
      os << coefficient;
  }

  TCoefficient coefficient_;
};

} // namespace grobner

