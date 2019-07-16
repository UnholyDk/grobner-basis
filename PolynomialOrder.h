#include "Polynomial.h"
template <typename T>
class PolynomialOrder {
public:
    PolynomialOrder() {}

    MonomialOrder<T>& get_mon_order() {
        return mon_order;
    }

    PolynomialOrder(const std::vector<std::function<bool(const Monomial<T>&, const Monomial<T>&)>>& tmp_mon_ord) {
        mon_order = tmp_mon_ord;
    }

    bool compair_less(Polynomial<T>& pol1, Polynomial<T>& pol2) {
        pol1.sort_pol(mon_order);
        pol2.sort_pol(mon_order);

        auto it1 = pol1.rbegin();
        auto it2 = pol2.rbegin();
        while (it1 != pol1.rend() && it2 != pol2.rend()) {
            if (*it1 != *it2) {
                return mon_order.compair_less(*it1, *it2);
            }
            ++it1;
            ++it2;
        }
        return pol1.size() < pol2.size();
    }

private:
    MonomialOrder<T> mon_order;
};
