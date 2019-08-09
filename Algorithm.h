#include "PolynomialSet.h"
#include <utility>
namespace grobner {
template <typename T, number_of_variables_type TNumberOfVariables>
class Algorithm {
 public:
  Algorithm(const MonomialOrder<T, TNumberOfVariables>& order) : ord_(std::move(order)) {}

  Polynomial<T, TNumberOfVariables> reduction(
      Polynomial<T, TNumberOfVariables> g,
      PolynomialSet<T, TNumberOfVariables> syst_f) const {
    g.sort_pol(ord_);
    for (auto& pol : syst_f) {
      pol.sort_pol(ord_);
    }

    for (size_t i = 0; i < g.size(); ++i) {
      Monomial<T, TNumberOfVariables> mon_from_g = g[i];
      bool can_red = true;
      while (can_red) {
        can_red = false;
        for (const auto& pol_from_s : syst_f) {
          //
          Monomial<T, TNumberOfVariables> mon_L = L(pol_from_s);
          //
          if (mon_from_g.is_div(mon_L)) {
            //
            Monomial<T, TNumberOfVariables> tmp_c = mon_from_g / mon_L;
            Polynomial<T, TNumberOfVariables> tmp_p =
                pol_from_s * tmp_c;  // shit is here
            //
            g -= tmp_p;
            g.sort_pol(ord_);
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
    return g.sort_pol(ord_);
  }

  PolynomialSet<T, TNumberOfVariables> Buchberger(
      const PolynomialSet<T, TNumberOfVariables>& other_syst) const {
    PolynomialSet<T, TNumberOfVariables> ans_syst = other_syst;
    for (size_t i = 0; i < ans_syst.size(); ++i) {
      (ans_syst[i]).sort_pol(ord_);
    }
    for (size_t i = 0; i < ans_syst.size(); ++i) {
      for (int j = i - 1; j >= 0; --j) {
        Polynomial<T, TNumberOfVariables> red_s_pol =
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
  Monomial<T, TNumberOfVariables> L(
      const Polynomial<T, TNumberOfVariables>& p) const {
    return p[p.size() - 1];
  }

  std::pair<deg_container_type, deg_container_type> deegs_common_division(
      const Monomial<T, TNumberOfVariables>& m_1,
      const Monomial<T, TNumberOfVariables>& m_2) const {
    deg_container_type tmp_deegs_1, tmp_deegs_2;
    for (size_t i = 0; i < 26; ++i) {
      tmp_deegs_1[i] = std::max(m_1[i], m_2[i]) - m_1[i];
      tmp_deegs_2[i] = std::max(m_1[i], m_2[i]) - m_2[i];
    }
    return {tmp_deegs_1, tmp_deegs_2};
  }

  Polynomial<T, TNumberOfVariables> S(
      const Polynomial<T, TNumberOfVariables>& f_1,
      const Polynomial<T, TNumberOfVariables>& f_2) const {
    std::pair<deg_container_type, deg_container_type> tmp_deegs =
        deegs_common_division(L(f_1), L(f_2));
    Monomial<T, TNumberOfVariables> m_1(L(f_2).get_coefficient(),
                                        tmp_deegs.first);
    Monomial<T, TNumberOfVariables> m_2(L(f_1).get_coefficient(),
                                        tmp_deegs.second);
    return (f_1 * m_1 - f_2 * m_2).sort_pol(ord_);
  }

  MonomialOrder<T, TNumberOfVariables> ord_;
};
}  // namespace grobner
