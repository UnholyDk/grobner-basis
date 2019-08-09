#include "PolynomialOrder.h"

namespace grobner {
template <typename T, number_of_variables_type TNumberOfVariables>
class PolynomialSet {
 public:
  PolynomialSet() {}

  PolynomialSet(Polynomial<T, TNumberOfVariables> pol) {
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

  Polynomial<T, TNumberOfVariables>& operator[](size_t i) { return pols_[i]; }

  void operator+=(const Polynomial<T, TNumberOfVariables>& pol) {
    pols_.push_back(pol);
  }

 private:
  std::vector<Polynomial<T, TNumberOfVariables>> pols_;
};
}  // namespace grobner
