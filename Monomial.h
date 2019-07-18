#include <iostream>
#include <string>
#include <vector>

namespace grobner {
 template <typename T>
 class Monomial {
  public:
   Monomial(const T& x) : coef(x), deegs(26) { deegs.resize(26); }

   Monomial(const T& coef_tmp, const std::vector<int>& deegs_tmp)
       : coef(coef_tmp), deegs(deegs_tmp) {
     deegs.resize(26);
   }

   auto begin() const { return deegs.begin(); }

   auto end() const { return deegs.end(); }

   auto rbegin() const { return deegs.rbegin(); }

   auto rend() const { return deegs.rend(); }

   T get_coef() const { return coef; }

   std::vector<int> get_deegs() const { return deegs; }

   int operator[](size_t i) const { return deegs[i]; }

   int& operator[](size_t i) { return deegs[i]; }

   bool is_equal(const Monomial<T>& other) const {
     for (size_t i = 0; i < 26; ++i) {
       if (deegs[i] != other[i]) {
         return 0;
       }
     }
     return 1;
   }

   bool is_div(const Monomial<T>& other) const {
     for (size_t i = 0; i < 26; ++i) {
       if (deegs[i] < other[i]) {
         return false;
       }
     }
     return true;
   }

   Monomial<T>& operator*=(const T& x) {
     coef *= x;
     return *this;
   }

   Monomial<T> operator*(const T& x) const {
     Monomial<T> tmp_m = *this;
     return tmp_m *= x;
   }

   Monomial<T>& operator*=(const Monomial<T>& other) {
     coef *= other.get_coef();
     for (size_t i = 0; i < 26; ++i) {
       deegs[i] += other[i];
     }
     return *this;
   }

   Monomial<T> operator*(const Monomial<T>& other) const {
     Monomial<T> tmp_m = *this;
     return tmp_m *= other;
   }

   Monomial<T>& operator+=(const Monomial<T>& other) {
     // check for equal
     coef += other.get_coef();
     return *this;
   }

   Monomial<T> operator+(const Monomial<T>& other) const {
     Monomial<T> tmp_m;
     return tmp_m += other;
   }

   Monomial<T> operator/(const Monomial<T>& other) const {
     std::vector<int> tmp_deegs(26);
     for (size_t i = 0; i < 26; ++i) {
       tmp_deegs[i] = deegs[i] - other[i];
     }
     return {coef / other.get_coef(), tmp_deegs};
   }

   bool operator==(const Monomial<T>& other) const { return is_equal(other); }

   bool operator!=(const Monomial<T>& other) const { return !(is_equal(other)); }

  private:
   T coef;
   std::vector<int> deegs;
 };
}  // namespace grobner

template <typename T>
std::ostream& operator<<(std::ostream& os, Monomial<T> const& m) {
  if (m.get_coef() == 0) return os;
  if (m.get_coef() < 0)
    os << m.get_coef();
  else
    os << '+' << m.get_coef();
  std::vector<int> v = m.get_deegs();
  for (size_t i = 0; i < v.size(); ++i) {
    if (v[i] == 0) {
      continue;
    } else if (v[i] == 1) {
      os << char('a' + i);
    } else {
      os << char('a' + i) << '^' << v[i];
    }
  }
  return os;
}
