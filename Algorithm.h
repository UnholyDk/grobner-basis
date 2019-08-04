#include "PolynomialSet.h"
namespace grobner {
 template <typename T>
 class Algorithm {
  public:
   Algorithm(const MonomialOrder<T>& order) : ord(order) {}

   Polynomial<T> reduction(Polynomial<T> g, PolynomialSet<T> syst_f) const {
     g.sort_pol(ord);
     for (auto& pol : syst_f) {
       pol.sort_pol(ord);
     }

     for (size_t i = 0; i < g.size(); ++i) {
       Monomial<T> mon_from_g = g[i];
       bool can_red = true;
       while (can_red) {
         can_red = false;
         for (const auto& pol_from_s : syst_f) {
           //
           Monomial<T> mon_L = L(pol_from_s);
           //
           if (mon_from_g.is_div(mon_L)) {
             //
             Monomial<T> tmp_c = mon_from_g / mon_L;
             Polynomial<T> tmp_p = pol_from_s * tmp_c;  // shit is here
             //
             g -= tmp_p;
             g.sort_pol(ord);
             if (i >= g.size()) {
               can_red = false;
             } else {
               mon_from_g = g[i];
               can_red = true;
             }
             break;
           }
         }
       }
     }
     return g.sort_pol(ord);
   }

   PolynomialSet<T> Buchberger(const PolynomialSet<T>& other_syst) const {
     PolynomialSet<T> ans_syst = other_syst;
     for (size_t i = 0; i < ans_syst.size(); ++i) {
       (ans_syst[i]).sort_pol(ord);
     }
     for (size_t i = 0; i < ans_syst.size(); ++i) {
       for (int j = i - 1; j >= 0; --j) {
         Polynomial<T> red_s_pol =
             reduction(S(ans_syst[i], ans_syst[j]), ans_syst);
         if (red_s_pol.size() !=
             0) {  // need fixed this to check empty polynomial
           ans_syst += red_s_pol;
         }
       }
     }
     return ans_syst;
   }

  private:
   Monomial<T> L(const Polynomial<T>& p) const { return p[p.size() - 1]; }

   std::pair<deg_container_type, deg_container_type> deegs_common_division(
       const Monomial<T>& m_1, const Monomial<T>& m_2) const {
     deg_container_type tmp_deegs_1(26), tmp_deegs_2(26);
     for (size_t i = 0; i < 26; ++i) {
       tmp_deegs_1[i] = std::max(m_1[i], m_2[i]) - m_1[i];
       tmp_deegs_2[i] = std::max(m_1[i], m_2[i]) - m_2[i];
     }
     return {tmp_deegs_1, tmp_deegs_2};
   }

   Polynomial<T> S(const Polynomial<T>& f_1, const Polynomial<T>& f_2) const {
     std::pair<deg_container_type, deg_container_type> tmp_deegs =
         deegs_common_division(L(f_1), L(f_2));
     Monomial<T> m_1(L(f_2).get_coefficient(), tmp_deegs.first);
     Monomial<T> m_2(L(f_1).get_coefficient(), tmp_deegs.second);
     return (f_1 * m_1 - f_2 * m_2).sort_pol(ord);
   }

   MonomialOrder<T> ord;
 };
}  // namespace grobner
