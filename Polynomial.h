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
          for (size_t i = 0; i < monomials_.size(); ++i) {
            if (monomials_[i].equal_of_variables(monomial)) {
              if (monomials_[i].get_coefficient() ==  -1 * monomial.get_coefficient()) {
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
          return *this;
        }

        Polynomial operator+(const Polynomial& other) const {
          Polynomial tmp_pol = *this;
          return std::move(tmp_pol += other);
        }

        Polynomial& operator*=(const T& coefficient) {
          if (coefficient == 0) {
            monomials_.clear();
            return *this;
          } else {
            for (auto& mon : monomials_) {
              mon *= coefficient;
            }
            return *this;
          }
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
          *this += other * (-1);
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

        size_t amount_of_monomials() const { return monomials_.size(); }

        [[nodiscard]] bool empty() const { return amount_of_monomials() == 0; }

    private:
        container_type monomials_;
        void dell_all_zero() {
          for (size_t i = 0; i < amount_of_monomials();) {
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
  if (pol.empty())
    os << T(0);
  for (auto& mon : pol) {
    os << "+(" << mon << ')';
  }
  return os;
}
