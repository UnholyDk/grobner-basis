#include <functional>
#include "Monomial.h"

namespace grobner {
template <typename T, number_of_variables_type TNumberOfVariables>
class MonomialOrder {
  using monomial = Monomial<T, TNumberOfVariables>;
  using compare_signature_type = bool(const monomial&, const monomial&);
  using compare_storage_type = std::function<compare_signature_type>;
  using compare_container_type = std::vector<compare_storage_type>;

 public:
  MonomialOrder() {}

  MonomialOrder(const compare_container_type & tmp_mon_ord) {
    comparators_ = tmp_mon_ord;
  }

  void add_order(const compare_storage_type & func) {
    comparators_.push_back(func);
  }

  compare_storage_type operator[](size_t i) const {
    return comparators_[i];
  }

  compare_storage_type operator[](size_t i) {
    return comparators_[i];
  }

  bool is_less(const monomial & mon1, const monomial & mon2) const {
    for (auto func : comparators_) {
      if (func(mon1, mon2) != func(mon2, mon1)) {
        return func(mon1, mon2);
      }
    }
    return false;
  }

  bool is_less_eq(const monomial& mon1, const monomial & mon2) const {
    for (auto func : comparators_) {
      if (func(mon1, mon2) != func(mon2, mon1)) {
        return func(mon1, mon2);
      }
    }
    return true;
  }

 private:
  compare_container_type comparators_;
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
