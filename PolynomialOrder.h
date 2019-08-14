#include "Polynomial.h"

namespace grobner {
template<typename T, number_of_variables_type TNumberOfVariables>
class PolynomialOrder {
 public:
  PolynomialOrder() {}

  MonomialOrder<T, TNumberOfVariables> &get_mon_order() { return mon_order_; }

  PolynomialOrder(const MonomialOrder<T, TNumberOfVariables> &tmp_mon_ord) {
    mon_order_ = tmp_mon_ord;
  }

  bool is_less(Polynomial<T, TNumberOfVariables> const &pol1,
               Polynomial<T, TNumberOfVariables> const &pol2) const {

    std::vector<const Monomial<T, TNumberOfVariables> &> view_poly1 = pol1.get_monomials();
    std::vector<const Monomial<T, TNumberOfVariables> &> view_poly2 = pol2.get_monomials();

    std::sort(view_poly1.begin(), view_poly1.end(),
              [this](Monomial<T, TNumberOfVariables> const &mon1,
                     Monomial<T, TNumberOfVariables> const &mon2) {
                return mon_order_.is_less(mon1, mon2);
              });

    std::sort(view_poly2.begin(), view_poly2.end(),
              [this](Monomial<T, TNumberOfVariables> const &mon1,
                     Monomial<T, TNumberOfVariables> const &mon2) {
                return mon_order_.is_less(mon1, mon2);
              });

    auto it1 = view_poly1.rbegin();
    auto it2 = view_poly2.rbegin();
    while (it1!=view_poly1.rend() && it2!=view_poly2.rend()) {
      if (mon_order_.is_less(*it1, *it2))
        return true;
      if (mon_order_.is_less(*it2, *it1))
        return false;
      ++it1;
      ++it2;
    }
    return view_poly1.size() < view_poly2.size();
  }

 private:
  MonomialOrder<T, TNumberOfVariables> mon_order_;
};
}  // namespace grobner
