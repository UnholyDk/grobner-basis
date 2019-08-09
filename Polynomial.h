#include <algorithm>
#include "MonomialOrder.h"

namespace grobner {
template <class T, number_of_variables_type TNumberOfVariables>
class Polynomial {
  using container_type = std::vector<Monomial<T, TNumberOfVariables>>;

 public:
  Polynomial() {}

  Polynomial(const Monomial<T, TNumberOfVariables>& other_mon) {
    monoms_.push_back(other_mon);
  }

  auto begin() const { return monoms_.begin(); }

  auto end() const { return monoms_.end(); }

  auto rbegin() const { return monoms_.rbegin(); }

  auto rend() const { return monoms_.rend(); }

  size_t size() const { return monoms_.size(); }

  void dell_0() {
    for (size_t i = 0; i < size();) {
      if (monoms_[i].get_coefficient() == 0 && monoms_.size() > 1) {
        monoms_.erase(monoms_.begin() + i);
      } else {
        ++i;
      }
    }
  }

  void dell_same_monoms_or_add(const Monomial<T, TNumberOfVariables>& other) {
    for (auto& monom : monoms_) {
      if (monom.equal_of_variables(other)) {
        monom.merge(other);
        return;
      }
    }
    monoms_.push_back(other);
  }

  Polynomial& operator+=(const Monomial<T, TNumberOfVariables>& other) {
    bool diff = true;
    for (size_t i = 0; i < monoms_.size(); ++i) {
      if (monoms_[i].equal_of_variables(other)) {
        monoms_[i].merge(other);
        diff = false;
      }
    }
    if (diff) {
      monoms_.push_back(other);
    }
    dell_0();
    return *this;
  }

  Polynomial operator+(const Monomial<T, TNumberOfVariables>& other) const {
    Polynomial tmp_p = *this;
    return tmp_p += other;
  }

  Monomial<T, TNumberOfVariables> operator[](size_t i) const {
    return monoms_[i];
  }

  Monomial<T, TNumberOfVariables>& operator[](size_t i) { return monoms_[i]; }

  Polynomial& operator+=(const Polynomial& other) {
    for (const auto& mon_from_other : other.monoms_) {
      *this += mon_from_other;
    }
    dell_0();
    return *this;
  }

  Polynomial operator+(const Polynomial& other) const {
    Polynomial tmp_pol = *this;
    return tmp_pol += other;
  }

  Polynomial& operator*=(const T& x) {
    for (auto& mon : monoms_) {
      mon *= x;
    }
    dell_0();
    return *this;
  }

  Polynomial operator*(const T& x) const {
    Polynomial tmp_p = *this;
    return tmp_p *= x;
  }

  Polynomial& operator*=(const Polynomial& other) {
    Polynomial tmp_p = *this;
    monoms_.clear();
    for (const auto& mon_from_this : tmp_p.monoms_) {
      for (const auto& mon_from_other : other.monoms_) {
        *this += mon_from_this * mon_from_other;
      }
    }
    dell_0();
    return *this;
  }

  Polynomial operator*(const Polynomial& other) const {
    Polynomial tmp_p = *this;
    return tmp_p *= other;
  }

  Polynomial& operator-=(const Polynomial& other) {
    *this *= -1;
    *this += other;
    *this *= -1;
    dell_0();
    return *this;
  }

  Polynomial operator-(const Polynomial& other) const {
    Polynomial tmp_p = *this;
    return tmp_p -= other;
  }

  Polynomial sort_pol(const MonomialOrder<T, TNumberOfVariables>& ord) {
    std::sort(monoms_.begin(), monoms_.end(),
              [&ord](Monomial<T, TNumberOfVariables> const& mon1,
                     Monomial<T, TNumberOfVariables> const& mon2) {
                return ord.is_less(mon1, mon2);
              });
    return *this;
  }

  size_t size() { return monoms_.size(); }

 private:
  container_type monoms_;
};
}  // namespace grobner

template <class T, number_of_variables_type TNumberOfVariables>
std::ostream& operator<<(
    std::ostream& os, grobner::Polynomial<T, TNumberOfVariables> const& pol) {
  for (auto& mon : pol) {
    os << "+(" << mon << ')';
  }
  return os;
}
