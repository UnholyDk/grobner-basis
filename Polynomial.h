#include <algorithm>
#include "MonomialOrder.h"

namespace grobner {
template <class T, number_of_variables_type TNumberOfVariables>
class Polynomial {
  using container_type = std::vector<Monomial<T, TNumberOfVariables>>;

 public:
  Polynomial() {}

  Polynomial(Monomial<T, TNumberOfVariables>& monomial) {
    monomials_.emplace_back(std::move(monomial));
    dell_all_zero();
  }

  auto begin() const { return monomials_.begin(); }

  auto end() const { return monomials_.end(); }

  auto rbegin() const { return monomials_.rbegin(); }

  auto rend() const { return monomials_.rend(); }

  size_t size() const { return monomials_.size(); }

  Polynomial& operator+=(const Monomial<T, TNumberOfVariables>& monomial) {
    bool diff = true;
    for (auto& my_monomial : monomials_) {
      if (my_monomial.equal_of_variables(monomial)) {
        my_monomial.merge_monomial(monomial);
        diff = false;
        break;
      }
    }
    if (diff) {
      monomials_.push_back(monomial);
    }
    dell_all_zero();
    return *this;
  }

  Polynomial operator+(const Monomial<T, TNumberOfVariables>& other) const {
    Polynomial tmp_p = *this;
    return std::move(tmp_p += other);
  }

  Monomial<T, TNumberOfVariables> operator[](size_t i) const {
    return monomials_[i];
  }

  Monomial<T, TNumberOfVariables>& operator[](size_t i) { return monomials_[i]; }

  Polynomial& operator+=(const Polynomial& other) {
    for (const auto& mon_from_other : other.monomials_) {
      *this += mon_from_other;
    }
    dell_all_zero();
    return *this;
  }

  Polynomial operator+(const Polynomial& other) const {
    Polynomial tmp_pol = *this;
    return std::move(tmp_pol += other);
  }

  Polynomial& operator*=(const T& x) {
    for (auto& mon : monomials_) {
      mon *= x;
    }
    dell_all_zero();
    return *this;
  }

  Polynomial operator*(const T& x) const {
    Polynomial tmp_p = *this;
    return std::move(tmp_p *= x);
  }

  Polynomial& operator*=(const Polynomial& other) {
    Polynomial tmp_p = *this;
    monomials_.clear();
    for (const auto& mon_from_this : tmp_p.monomials_) {
      for (const auto& mon_from_other : other.monomials_) {
        *this += mon_from_this * mon_from_other;
      }
    }
    dell_all_zero();
    return *this;
  }

  Polynomial operator*(const Polynomial& other) const {
    Polynomial tmp_p = *this;
    return std::move(tmp_p *= other);
  }

  Polynomial& operator-=(const Polynomial& other) {
    *this *= -1;
    *this += other;
    *this *= -1;
    dell_all_zero();
    return *this;
  }

  Polynomial operator-(const Polynomial& other) const {
    Polynomial tmp_p = *this;
    return std::move(tmp_p -= other);
  }

  Polynomial sort_pol(const MonomialOrder<T, TNumberOfVariables>& ord) {
    std::sort(monomials_.begin(), monomials_.end(),
              [&ord](Monomial<T, TNumberOfVariables> const& mon1,
                     Monomial<T, TNumberOfVariables> const& mon2) {
                return ord.is_less(mon1, mon2);
              });
    return *this;
  }

  size_t size() { return monomials_.size(); }

 private:
  container_type monomials_;
  void dell_all_zero() {
    for (size_t i = 0; i < size();) {
      if (monomials_[i].get_coefficient() == 0 && monomials_.size() > 1) {
        monomials_.erase(monomials_.begin() + i);
      } else {
        ++i;
      }
    }
  }
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
