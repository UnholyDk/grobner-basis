#include "PolynomialVector.h"
#include <utility>
namespace grobner {
template<typename T, index_type TNumberOfVariables = detail::gDefaultNumberOfVariables>
class Algorithm {
 public:
  Algorithm(const MonomialOrder<T, TNumberOfVariables> &order)
      : ord_(std::move(order)) {}

  Polynomial<T, TNumberOfVariables>
  reduction(Polynomial<T, TNumberOfVariables> g,
            PolynomialVector<T, TNumberOfVariables> syst_f) const {
    sort_pol(g);
    for (auto &pol : syst_f) {
      sort_pol(pol);
    }
    return reduction_sorted(g, syst_f);
  }

  Polynomial<T, TNumberOfVariables>
  reduction_sorted(
      const Polynomial<T, TNumberOfVariables> &g,
      const PolynomialVector<T, TNumberOfVariables> &syst_f) const {
    Polynomial<T, TNumberOfVariables> ans = g;
    sort_pol(ans);
    for (size_t i = 0; i < ans.amount_of_monomials(); ++i) {
      Monomial<T, TNumberOfVariables> mon_from_ans = ans[i];
      bool can_red = true;
      while (can_red) {
        can_red = false;
        for (const auto &pol_from_s : syst_f) {
          if (mon_from_ans.is_divisible(L(pol_from_s))) {
            Monomial<T, TNumberOfVariables> tmp_c =
                mon_from_ans / L(pol_from_s);
            ans -= pol_from_s * tmp_c;
            sort_pol(ans);
            if (i >= ans.amount_of_monomials()) {
              can_red = false;
            } else {
              mon_from_ans = ans[i];
              can_red = true;
            }
            break;
          }
        }
      }
    }
    return sort_pol(ans);
  }

  PolynomialVector<T, TNumberOfVariables>
  Buchberger(const PolynomialVector<T, TNumberOfVariables> &other_syst) const {
    PolynomialVector<T, TNumberOfVariables> ans_syst = other_syst;
    for (size_t i = 0; i < ans_syst.size(); ++i) {
      sort_pol(ans_syst[i]);
    }
    for (size_t i = 0; i < ans_syst.size(); ++i) {
      for (int j = i - 1; j >= 0; --j) {
        Polynomial<T, TNumberOfVariables> red_s_pol =
            reduction(S(ans_syst[i], ans_syst[j]), ans_syst);
        if (red_s_pol.amount_of_monomials() != 0) {
          ans_syst.add_pol(red_s_pol);
        }
      }
    }
    return ans_syst;
  }

  const Monomial<T, TNumberOfVariables> &
  get_monomial(const Polynomial<T, TNumberOfVariables> &pol,
               size_t index) const {
    Polynomial<T, TNumberOfVariables> tmp_p = pol;
    sort_pol(tmp_p);
    return tmp_p[tmp_p.amount_of_monomials() - index];
  }

  Polynomial<T, TNumberOfVariables>
  sort_pol(Polynomial<T, TNumberOfVariables> &pol) const {
    std::sort((pol.get_monomials()).begin(), (pol.get_monomials()).end(),
              [this](Monomial<T, TNumberOfVariables> const &mon1,
                     Monomial<T, TNumberOfVariables> const &mon2) {
                return ord_.is_less(mon1, mon2);
              });
    return pol;
  }

 private:
  using deg_container_type = typename Monomial<T, TNumberOfVariables>::deg_container_type; //maybe fix or not

  Monomial<T, TNumberOfVariables>
  L(const Polynomial<T, TNumberOfVariables> &p) const {
    return p[p.amount_of_monomials() - 1];
  }

  std::pair<deg_container_type, deg_container_type>
  deegs_common_division(const Monomial<T, TNumberOfVariables> &m_1,
                        const Monomial<T, TNumberOfVariables> &m_2) const {
    deg_container_type tmp_deegs_1, tmp_deegs_2;
    for (size_t i = 0; i < 26; ++i) {
      tmp_deegs_1[i] = std::max(m_1[i], m_2[i]) - m_1[i];
      tmp_deegs_2[i] = std::max(m_1[i], m_2[i]) - m_2[i];
    }
    return {tmp_deegs_1, tmp_deegs_2};
  }

  Polynomial<T, TNumberOfVariables>
  S(const Polynomial<T, TNumberOfVariables> &f_1,
    const Polynomial<T, TNumberOfVariables> &f_2) const {
    std::pair<deg_container_type, deg_container_type> tmp_deegs =
        deegs_common_division(L(f_1), L(f_2));
    Monomial<T, TNumberOfVariables> m_1(L(f_2).get_coefficient(),
                                        tmp_deegs.first);
    Monomial<T, TNumberOfVariables> m_2(L(f_1).get_coefficient(),
                                        tmp_deegs.second);
    Polynomial<T, TNumberOfVariables> ans;
    ans += f_1 * m_1;
    ans -= f_2 * m_2;
    return sort_pol(ans);
  }

  MonomialOrder<T, TNumberOfVariables> ord_;
};
} // namespace grobner
