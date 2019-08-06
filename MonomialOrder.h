#include <functional>
#include "Monomial.h"

namespace grobner {
template <typename T, number_of_variables_type TNumberOfVariables>
class MonomialOrder {
 public:
  MonomialOrder() {}

  MonomialOrder(const std::vector<
                std::function<bool(const Monomial<T, TNumberOfVariables>&,
                                   const Monomial<T, TNumberOfVariables>&)>>&
                    tmp_mon_ord) {
    orders = tmp_mon_ord;
  }

  void add_order(
      const std::function<bool(const Monomial<T, TNumberOfVariables>&,
                               const Monomial<T, TNumberOfVariables>&)>& func) {
    orders.push_back(func);
  }

  std::function<bool(const Monomial<T, TNumberOfVariables>&,
                     const Monomial<T, TNumberOfVariables>&)>
  operator[](size_t i) const {
    return orders[i];
  }

  std::function<bool(const Monomial<T, TNumberOfVariables>&,
                     const Monomial<T, TNumberOfVariables>&)>&
  operator[](size_t i) {
    return orders[i];
  }

  bool is_less(const Monomial<T, TNumberOfVariables>& mon1,
                    const Monomial<T, TNumberOfVariables>& mon2) const {
    for (auto func : orders) {
      if (func(mon1, mon2) != func(mon2, mon1)) {
        return func(mon1, mon2);
      }
    }
    return false;
  }

  bool is_less_eq(const Monomial<T, TNumberOfVariables>& mon1,
                          const Monomial<T, TNumberOfVariables>& mon2) const {
    for (auto func : orders) {
      if (func(mon1, mon2) != func(mon2, mon1)) {
        return func(mon1, mon2);
      }
    }
    return true;
  }

 private:
  std::vector<std::function<bool(const Monomial<T, TNumberOfVariables>&,
                                 const Monomial<T, TNumberOfVariables>&)>>
      orders;
};

template <typename T, number_of_variables_type TNumberOfVariables>
bool lexicograph(const Monomial<T, TNumberOfVariables>& mon1,
                 const Monomial<T, TNumberOfVariables>& mon2) {
  for (size_t i = 0; i < 26; ++i) {
    if (mon1[i] != mon2[i]) {
      return mon1[i] < mon2[i];
    }
  }
  return false;
}
}  // namespace grobner
