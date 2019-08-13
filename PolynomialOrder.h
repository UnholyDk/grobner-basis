#include "Polynomial.h"

namespace grobner {
    template <typename T, number_of_variables_type TNumberOfVariables>
    class PolynomialOrder {
    public:
        PolynomialOrder() {}

        MonomialOrder<T, TNumberOfVariables>& get_mon_order() { return mon_order_; }

        PolynomialOrder(const MonomialOrder<T, TNumberOfVariables>& tmp_mon_ord) {
            mon_order_ = tmp_mon_ord;
        }

        bool is_less(Polynomial<T, TNumberOfVariables>& pol1,
                     Polynomial<T, TNumberOfVariables>& pol2) {
            std::sort((pol1.get_monomials()).begin(), (pol1.get_monomials()).end(),
                      [this](Monomial<T, TNumberOfVariables> const& mon1,
                             Monomial<T, TNumberOfVariables> const& mon2) {
                          return mon_order_.is_less(mon1, mon2);
                      });

            std::sort((pol2.get_monomials()).begin(), (pol2.get_monomials()).end(),
                      [this](Monomial<T, TNumberOfVariables> const& mon1,
                             Monomial<T, TNumberOfVariables> const& mon2) {
                          return mon_order_.is_less(mon1, mon2);
                      });

            auto it1 = pol1.rbegin();
            auto it2 = pol2.rbegin();
            while (it1 != pol1.rend() && it2 != pol2.rend()) {
                if (mon_order_.is_less(*it1, *it2))
                    return true;
                if (mon_order_.is_less(*it2, *it1))
                    return false;
                ++it1;
                ++it2;
            }
            return pol1.amount_of_monomials() < pol2.amount_of_monomials();
        }

    private:
        MonomialOrder<T, TNumberOfVariables> mon_order_;
    };
}  // namespace grobner