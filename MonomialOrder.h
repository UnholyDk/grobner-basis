#include <functional>
#include "Monomial.h"

namespace grobner {
 template <typename T>
 class MonomialOrder {
  public:
   MonomialOrder() {}

   MonomialOrder(const std::vector<
                 std::function<bool(const Monomial<T>&, const Monomial<T>&)>>&
                     tmp_mon_ord) {
     orders = tmp_mon_ord;
   }

   void add_order(
       const std::function<bool(const Monomial<T>&, const Monomial<T>&)>& func) {
     orders.push_back(func);
   }

   std::function<bool(const Monomial<T>&, const Monomial<T>&)> operator[](
       size_t i) const {
     return orders[i];
   }

   std::function<bool(const Monomial<T>&, const Monomial<T>&)>& operator[](
       size_t i) {
     return orders[i];
   }

   bool compair_less(const Monomial<T>& mon1, const Monomial<T>& mon2) const {
     for (auto func : orders) {
       if (func(mon1, mon2) != func(mon2, mon1)) {
         return func(mon1, mon2);
       }
     }
     return 0;
   }

   bool compair_less_or_eq(const Monomial<T>& mon1,
                           const Monomial<T>& mon2) const {
     for (auto func : orders) {
       if (func(mon1, mon2) != func(mon2, mon1)) {
         return func(mon1, mon2);
       }
     }
     return 1;
   }

  private:
   std::vector<std::function<bool(const Monomial<T>&, const Monomial<T>&)>>
       orders;
 };

 template <typename T>
 bool lexicograph(const Monomial<T>& mon1, const Monomial<T>& mon2) {
   for (size_t i = 0; i < 26; ++i) {
     if (mon1[i] != mon2[i]) {
       return mon1[i] < mon2[i];
     }
   }
   return 0;
 }
}  // namespace grobner
