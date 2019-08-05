#include "PolynomialOrder.h"

namespace grobner {
template <typename T, number_of_variables_type TNumberOfVariables>
class PolynomialSet {
 public:
  PolynomialSet() {}

  PolynomialSet(const Polynomial<T, TNumberOfVariables>& pol) {
    pols.push_back(pol);
  }

  auto begin() { return pols.begin(); }

  auto end() { return pols.end(); }

  auto begin() const { return pols.begin(); }

  auto end() const { return pols.end(); }

  size_t size() { return pols.size(); }

  Polynomial<T, TNumberOfVariables> operator[](size_t i) const {
    return pols[i];
  }

  Polynomial<T, TNumberOfVariables>& operator[](size_t i) { return pols[i]; }

  void operator+=(const Polynomial<T, TNumberOfVariables>& pol) {
    pols.push_back(pol);
  }

 private:
  std::vector<Polynomial<T, TNumberOfVariables>> pols;
};
}  // namespace grobner
