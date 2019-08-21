#include <algorithm>
#include "MonomialOrder.h"

namespace grobner {
template<class T, number_of_variables_type TNumberOfVariables>
class Polynomial {
  using container_type = std::vector<Monomial<T, TNumberOfVariables>>;

 public:
  Polynomial() {}

  Polynomial(Monomial<T, TNumberOfVariables> &monomial) {
    monomials_.emplace_back(std::move(monomial));
  }

  auto begin() const { return monomials_.begin(); }

  auto end() const { return monomials_.end(); }

  auto rbegin() const { return monomials_.rbegin(); }

  auto rend() const { return monomials_.rend(); }

  container_type &get_monomials() {
    return monomials_;
  }

  size_t size() const { return monomials_.size(); }

  Polynomial &operator+=(const Monomial<T, TNumberOfVariables> &monomial) {
    for (size_t i = 0; i < monomials_.size(); ++i) {
      if (monomials_[i].are_variable_parts_same(monomial)) {
        if (monomials_[i].get_coefficient()==-monomial.get_coefficient()) {
          monomials_.erase(monomials_.begin() + i);
        } else {
          monomials_[i].merge_monomial(monomial);
        }
        return *this;
      }
    }
    monomials_.push_back(monomial);
    return *this;
  }

  Polynomial operator+(const Monomial<T, TNumberOfVariables> &other) const {
    Polynomial tmp_p = *this;
    return std::move(tmp_p += other);
  }

  Monomial<T, TNumberOfVariables> operator[](size_t i) const {
    return monomials_[i];
  }

  Monomial<T, TNumberOfVariables> &operator[](size_t i) { return monomials_[i]; }

  Polynomial operator-() const {
    Polynomial tmp = *this;
    for (auto &mon : tmp.get_monomials()) {
      mon = -mon;
    }
    return tmp;
  }

  Polynomial &operator+=(const Polynomial &other) {
    for (const auto &mon_from_other : other.monomials_) {
      *this += mon_from_other;
    }
    return *this;
  }

  Polynomial operator+(const Polynomial &other) const {
    Polynomial tmp_pol = *this;
    return std::move(tmp_pol += other);
  }

  Polynomial &operator*=(const T &coefficient) {
    if (coefficient==0) {
      monomials_.clear();
      return *this;
    } else {
      for (auto &mon : monomials_) {
        mon *= coefficient;
      }
      return *this;
    }
  }

  Polynomial operator*(const T &x) const {
    Polynomial tmp_p = *this;
    return std::move(tmp_p *= x);
  }

  Polynomial &operator*=(const Polynomial &other) {
    Polynomial tmp_p = *this;
    monomials_.clear();
    for (const auto &mon_from_this : tmp_p.monomials_) {
      for (const auto &mon_from_other : other.monomials_) {
        *this += mon_from_this*mon_from_other;
      }
    }
    return *this;
  }

  Polynomial operator*(const Polynomial &other) const {
    Polynomial tmp_p = *this;
    return std::move(tmp_p *= other);
  }

  Polynomial &operator-=(const Polynomial &other) {
    *this += -other;
    return *this;
  }

  Polynomial operator-(const Polynomial &other) const {
    Polynomial tmp_p = *this;
    return std::move(tmp_p -= other);
  }

  size_t amount_of_monomials() const { return monomials_.size(); }

  [[nodiscard]] bool empty() const { return amount_of_monomials()==0; }

 private:
  container_type monomials_;
};
}  // namespace grobner

template<class T, number_of_variables_type TNumberOfVariables>
std::ostream &operator<<(
    std::ostream &os, grobner::Polynomial<T, TNumberOfVariables> const &pol) {
  if (pol.empty())
    os << 0;
  auto it = pol.begin();
  os << '(' << *it << ')';
  ++it;
  while (it != pol.end()) {
    os << "+(" <<*it << ')';
    ++it;
  }
  return os;
}