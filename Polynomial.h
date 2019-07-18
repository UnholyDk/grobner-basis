#include <algorithm>
#include "MonomialOrder.h"

namespace grobner {
 template <typename T>
 class Polynomial {
  public:
   Polynomial() {}

   Polynomial(const Monomial<T>& other_mon) { monoms.push_back(other_mon); }

   auto begin() const { return monoms.begin(); }

   auto end() const { return monoms.end(); }

   auto rbegin() const { return monoms.rbegin(); }

   auto rend() const { return monoms.rend(); }

   std::vector<Monomial<T>> get_monoms() const { return monoms; }

   size_t size() const { return monoms.size(); }

   void dell_0() {
     for (size_t i = 0; i < size();) {
       if (monoms[i].get_coef() == 0) {
         monoms.erase(monoms.begin() + i);
       } else {
         ++i;
       }
     }
   }

   void dell_same_monoms_or_add(const Monomial<T>& other) {
     for (auto& monom : monoms) {
       if (monom.is_equal(other)) {
         monom += other;
         return;
       }
     }
     monoms.push_back(other);
   }

   Polynomial<T>& operator+=(const Monomial<T>& other) {
     bool diff = true;
     for (size_t i = 0; i < monoms.size(); ++i) {
       if (monoms[i].is_equal(other)) {
         monoms[i] += other.get_coef();
         diff = false;
       }
     }
     if (diff) {
       monoms.push_back(other);
     }
     dell_0();
     return *this;
   }

   Polynomial<T> operator+(const Monomial<T>& other) const {
     Polynomial<T> tmp_p = *this;
     return tmp_p += other;
   }

   Monomial<T> operator[](size_t i) const { return monoms[i]; }

   Monomial<T>& operator[](size_t i) { return monoms[i]; }

   Polynomial<T>& operator+=(const Polynomial<T>& other) {
     for (const auto& mon_from_other : other.monoms) {
       *this += mon_from_other;
     }
     dell_0();
     return *this;
   }

   Polynomial<T> operator+(const Polynomial<T>& other) const {
     Polynomial<T> tmp_pol = *this;
     return tmp_pol += other;
   }

   Polynomial<T>& operator*=(const T& x) {
     for (auto& mon : monoms) {
       mon *= x;
     }
     dell_0();
     return *this;
   }

   Polynomial<T> operator*(const T& x) const {
     Polynomial<T> tmp_p = *this;
     return tmp_p *= x;
   }

   Polynomial<T>& operator*=(const Polynomial<T>& other) {
     Polynomial<T> tmp_p = *this;
     monoms.clear();
     for (const auto& mon_from_this : tmp_p.monoms) {
       for (const auto& mon_from_other : other.monoms) {
         *this += mon_from_this * mon_from_other;
       }
     }
     dell_0();
     return *this;
   }

   Polynomial<T> operator*(const Polynomial<T>& other) const {
     Polynomial<T> tmp_p = *this;
     return tmp_p *= other;
   }

   Polynomial<T>& operator-=(const Polynomial<T>& other) {
     *this *= -1;
     *this += other;
     *this *= -1;
     dell_0();
     return *this;
   }

   Polynomial<T> operator-(const Polynomial<T>& other) const {
     Polynomial<T> tmp_p = *this;
     return tmp_p -= other;
   }

   Polynomial<T> sort_pol(const MonomialOrder<T>& ord) {
     std::sort(monoms.begin(), monoms.end(),
               [&ord](Monomial<T> const& mon1, Monomial<T> const& mon2) {
                 return ord.compair_less(mon1, mon2);
               });
     return *this;
   }

   size_t size() { return monoms.size(); }

  private:
   std::vector<Monomial<T>> monoms;
 };
}  // namespace grobner

template <typename T>
std::ostream& operator<<(std::ostream& os, Polynomial<T> const& m) {
  std::vector<Monomial<T>> v = m.get_monoms();
  for (size_t i = 0; i < v.size(); ++i) {
    os << v[i];
  }
  return os;
}
