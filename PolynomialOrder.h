#include "Polynomial.h"

namespace grobner {
template <typename T, number_of_variables_type TNumberOfVariables>
class PolynomialOrder {
 public:
  PolynomialOrder() {}

  MonomialOrder<T, TNumberOfVariables>& get_mon_order() { return mon_order_; }

  PolynomialOrder(const std::vector<
                  std::function<bool(const Monomial<T, TNumberOfVariables>&,
                                     const Monomial<T, TNumberOfVariables>&)>>&
                      tmp_mon_ord) {
    mon_order_ = tmp_mon_ord;
  }

  bool is_less(Polynomial<T, TNumberOfVariables>& pol1,
                    Polynomial<T, TNumberOfVariables>& pol2) {
    pol1.sort_pol(mon_order_);
    pol2.sort_pol(mon_order_);

    auto it1 = pol1.rbegin();
    auto it2 = pol2.rbegin();
    while (it1 != pol1.rend() && it2 != pol2.rend()) {
      if (*it1 != *it2) {
        return mon_order_.is_less(*it1, *it2);
      }
      ++it1;
      ++it2;
    }
    return pol1.size() < pol2.size();
  }

 private:
  MonomialOrder<T, TNumberOfVariables> mon_order_;
};
}  // namespace grobner
