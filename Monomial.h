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
template<class TCoefficient, number_of_variables_type TNumberOfVariables>
class Monomial {
  using deg_container_type = std::array<deg_value_type, TNumberOfVariables>;

 public:
  Monomial(TCoefficient coefficient) : coefficient_(std::move(coefficient)) {};

  Monomial(TCoefficient coefficient, deg_container_type &degrees) : coefficient_(std::move(coefficient)) {
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

  bool equal_of_variables(const Monomial &other) const {
    for (size_t i = 0; i < TNumberOfVariables; ++i) {
      if (degrees_[i]!=other[i]) {
        return false;
      }
    }
    return true;
  }

  bool is_div(const Monomial &other) const {
    for (size_t i = 0; i < TNumberOfVariables; ++i) {
      if (degrees_[i] < other[i]) {
        return false;
      }
    }
    return true;
  }

  Monomial &merge_monomial(const Monomial &other) {
    coefficient_ += other.coefficient_;
    return *this;
  }

  Monomial &operator*=(const TCoefficient &x) {
    coefficient_ *= x;
    return *this;
  }

  Monomial operator*(const TCoefficient &x) const {
    Monomial tmp_m = *this;
    return std::move(tmp_m *= x);
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
        (equal_of_variables(other) && coefficient_==other.coefficient_);
  }

  bool operator!=(const Monomial &other) const { return !(*this==other); }

  friend std::ostream & operator<<(std::ostream &os, Monomial const &m) {
    if (m.get_coefficient()!=1 && m.get_coefficient()!=-1)
      os << m.get_coefficient();
    if (m.get_coefficient()==-1)
      os << "-";
    if (m.get_coefficient()!=0)
      print_variables(os, m);
    return os;
  }

 private:
  TCoefficient coefficient_;
  deg_container_type degrees_;

  static void print_variable(std::ostream &os, number_of_variables_type variable_index, deg_value_type deg) {
    if (deg == 0)
      return;
    os << char('a' + variable_index);
    if (deg!=1)
      os << '^' << deg;
  }

   static void print_variables(std::ostream &os, Monomial const &monomial) {
    number_of_variables_type variable_index = 0;
    for (auto &deg : monomial) {
      print_variable(os, variable_index, deg);
      ++variable_index;
    }
  }
};
} // namespace grobner


