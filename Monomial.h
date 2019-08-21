#include <algorithm>
#include <array>
#include <iostream>
#include <string>
#include <vector>


namespace detail {
constexpr size_t gDefaultNumberOfVariables = 26;
}

namespace grobner {
using number_of_variables_type = size_t;
template<class TCoefficient, number_of_variables_type TNumberOfVariables = detail::gDefaultNumberOfVariables>
class Monomial {

 public:
  using number_of_variables_type = grobner::number_of_variables_type;
  using deg_value_type = int;
  using index_type = size_t;
  using deg_container_type = std::array<deg_value_type, TNumberOfVariables>;

  Monomial(TCoefficient coefficient) : coefficient_(std::move(coefficient)) {
    degrees_.fill(0);
  };

  Monomial(TCoefficient coefficient, deg_container_type &degrees) : coefficient_(std::move(coefficient)) {
    degrees_.fill(0);
    for (size_t i = 0; i < std::min(degrees.size(), size_t(TNumberOfVariables));
         ++i) {
      degrees_[i] = degrees[i];
    }
  };

  TCoefficient& get_coefficient() { return coefficient_; }

  const TCoefficient& get_coefficient() const { return coefficient_; }

  index_type amount_of_variables() const {
    return TNumberOfVariables;
  }

  Monomial operator-() const {
    Monomial tmp = *this;
    tmp.coefficient_ = -coefficient_;
    return tmp;
  }

  int operator[](size_t i) const {
    if (0 <= i && i < TNumberOfVariables)
      return degrees_[i];
    return 0;
  }

  int &operator[](size_t i) { return degrees_[i]; }

  bool are_variable_parts_same(const Monomial &other) const {
    return degrees_ == other.degrees_;
  }

  bool is_div(const Monomial &other) const {
    for (size_t i = 0; i < TNumberOfVariables; ++i) {
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
    for (size_t i = 0; i < TNumberOfVariables; ++i) {
      degrees_[i] += other[i];
    }
    return *this;
  }

  Monomial operator*(const Monomial &other) const {
    Monomial tmp_m = *this;
    return std::move(tmp_m *= other);
  }

  Monomial operator/(const Monomial &other) const {
    deg_container_type degrees;
    for (size_t i = 0; i < TNumberOfVariables; ++i) {
      degrees[i] = degrees_[i] - other[i];
    }
    return Monomial(coefficient_/other.get_coefficient(), degrees);
  }

  bool operator==(const Monomial &other) const {
    return coefficient_==other.coefficient_==0 ||
        (are_variable_parts_same(other) && coefficient_==other.coefficient_);
  }

  bool operator!=(const Monomial &other) const { return !(*this==other); }

  friend inline std::ostream & operator<<(std::ostream &os, const Monomial &monomial) {
    print_coefficient(os, monomial.get_coefficient());
    if (monomial.get_coefficient() != 0)
      print_variables(os, monomial);
    return os;
  }

 private:
  TCoefficient coefficient_;
  deg_container_type degrees_;

  static void print_variable(std::ostream &os, index_type index, deg_value_type deg) {
    if (deg == 0)
      return;
    os << char('a' + index);
    if (deg!=1)
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
};

} // namespace grobner

