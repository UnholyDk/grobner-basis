#include "PolynomialOrder.h"

namespace grobner {
template<typename T, number_of_variables_type TNumberOfVariables = detail::gDefaultNumberOfVariables>
class PolynomialVector {
 public:
  PolynomialVector() {}

  PolynomialVector(Polynomial<T, TNumberOfVariables> pol) {
    pols_.emplace_back(std::move(pol));
  }

  auto begin() { return pols_.begin(); }

  auto end() { return pols_.end(); }

  auto begin() const { return pols_.begin(); }

  auto end() const { return pols_.end(); }

  size_t size() { return pols_.size(); }

  Polynomial<T, TNumberOfVariables> operator[](size_t i) const {
    return pols_[i];
  }

  Polynomial<T, TNumberOfVariables> &operator[](size_t i) { return pols_[i]; }

  bool equal_of_monoms_sorted(const Polynomial<T, TNumberOfVariables> &pol1,
                              const Polynomial<T, TNumberOfVariables> &pol2) {
    if (pol1.size()!=pol2.size()) {
      return false;
    }
    auto it1 = pol1.begin();
    auto it2 = pol2.begin();
    while (it1!=pol1.end()) {
      if ((*it1).are_variable_parts_same(*it2)) {
        return false;
      }
      ++it1;
      ++it2;
    }
    return true;
  }

  void add_pol(const Polynomial<T, TNumberOfVariables> &pol) {
    pols_.push_back(pol);
  }

 private:
  std::vector<Polynomial<T, TNumberOfVariables>> pols_;
};
}  // namespace grobner
