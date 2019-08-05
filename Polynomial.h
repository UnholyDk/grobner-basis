#include <algorithm>
#include "MonomialOrder.h"

namespace grobner {
template <class T, number_of_variables_type TNumberOfVariables>
class Polynomial {
  using container_type = std::vector<Monomial<T, TNumberOfVariables>>;

 public:
  Polynomial() {}

  Polynomial(const Monomial<T, TNumberOfVariables>& other_mon) {
    monoms.push_back(other_mon);
  }

  auto begin() const { return monoms.begin(); }

  auto end() const { return monoms.end(); }

  auto rbegin() const { return monoms.rbegin(); }

  auto rend() const { return monoms.rend(); }

  size_t size() const { return monoms.size(); }

  void dell_0() {
    for (size_t i = 0; i < size();) {
      if (monoms[i].get_coefficient() == 0) {
        monoms.erase(monoms.begin() + i);
      } else {
        ++i;
      }
    }
  }

  void dell_same_monoms_or_add(const Monomial<T, TNumberOfVariables>& other) {
    for (auto& monom : monoms) {
      if (monom.is_equal(other)) {
        monom += other;
        return;
      }
    }
    monoms.push_back(other);
  }

  Polynomial& operator+=(const Monomial<T, TNumberOfVariables>& other) {
    bool diff = true;
    for (size_t i = 0; i < monoms.size(); ++i) {
      if (monoms[i].is_equal(other)) {
        monoms[i] += other.get_coefficient();
        diff = false;
      }
    }
    if (diff) {
      monoms.push_back(other);
    }
    dell_0();
    return *this;
  }

  Polynomial operator+(const Monomial<T, TNumberOfVariables>& other) const {
    Polynomial<T, TNumberOfVariables> tmp_p = *this;
    return tmp_p += other;
  }

  Monomial<T, TNumberOfVariables> operator[](size_t i) const {
    return monoms[i];
  }

  Monomial<T, TNumberOfVariables>& operator[](size_t i) { return monoms[i]; }

  Polynomial& operator+=(const Polynomial& other) {
    for (const auto& mon_from_other : other.monoms) {
      *this += mon_from_other;
    }
    dell_0();
    return *this;
  }

  Polynomial operator+(const Polynomial& other) const {
    Polynomial<T, TNumberOfVariables> tmp_pol = *this;
    return tmp_pol += other;
  }

  Polynomial& operator*=(const T& x) {
    for (auto& mon : monoms) {
      mon *= x;
    }
    dell_0();
    return *this;
  }

  Polynomial operator*(const T& x) const {
    Polynomial<T, TNumberOfVariables> tmp_p = *this;
    return tmp_p *= x;
  }

  Polynomial& operator*=(const Polynomial& other) {
    Polynomial<T, TNumberOfVariables> tmp_p = *this;
    monoms.clear();
    for (const auto& mon_from_this : tmp_p.monoms) {
      for (const auto& mon_from_other : other.monoms) {
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
    std::sort(monoms.begin(), monoms.end(),
              [&ord](Monomial<T, TNumberOfVariables> const& mon1,
                     Monomial<T, TNumberOfVariables> const& mon2) {
                return ord.compair_less(mon1, mon2);
              });
    return *this;
  }

  size_t size() { return monoms.size(); }

 private:
  container_type monoms;
};
}  // namespace grobner

template <class T, number_of_variables_type TNumberOfVariables>
std::ostream& operator<<(
    std::ostream& os, grobner::Polynomial<T, TNumberOfVariables> const& pol) {
  for (auto& mon : pol) {
    os << mon;
  }
  return os;
}
