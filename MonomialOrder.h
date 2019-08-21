#include <functional>
#include "Monomial.h"

namespace grobner {
template<typename T, number_of_variables_type TNumberOfVariables>
class MonomialOrder {
  using monomial = Monomial<T, TNumberOfVariables>;
  using compare_signature_type = bool(const monomial &, const monomial &);
  using compare_type = std::function<compare_signature_type>;
  using compare_container_type = std::vector<compare_type>;

 public:
  MonomialOrder() {}

  MonomialOrder(std::initializer_list<compare_type> comparators) : comparators_(comparators) {}

  auto begin() { return comparators_.begin(); }

  auto end() { return comparators_.end(); }

  auto rbegin() { return comparators_.rbegin(); }

  auto rend() { return comparators_.rend(); }

  size_t size() {
    return comparators_.size();
  }

  MonomialOrder &operator+=(const compare_type &compare) {
    comparators_.push_back(compare);
    return *this;
  }

  MonomialOrder &operator+=(const MonomialOrder &other) {
    comparators_.reserve(comparators_.size() + other.size());
    comparators_.insert(comparators_.end(),
                        other.begin(),
                        other.end());
    return *this;
  }

  MonomialOrder operator+(const MonomialOrder &other) const {
    compare_container_type tmp_comparators = comparators_;
    return std::move(tmp_comparators += other);
  }

  bool is_less(const monomial &mon1, const monomial &mon2) const {
    for (auto comparator : comparators_) {
      if (comparator(mon1, mon2)!=comparator(mon2, mon1)) {
        return comparator(mon1, mon2);
      }
    }
    return false;
  }

  bool is_less_eq(const monomial &mon1, const monomial &mon2) const {
    return !is_less(mon2, mon1);
  }

  static MonomialOrder Lex() {
    MonomialOrder tmp_mon_ord;
    tmp_mon_ord += compare_type([](const Monomial<T, TNumberOfVariables> &mon1,
                                   const Monomial<T, TNumberOfVariables> &mon2) {
      for (size_t i = 0; i < 26; ++i) {
        if (mon1[i]!=mon2[i]) {
          return mon1[i] < mon2[i];
        }
      }
      return false;
    });
    return tmp_mon_ord;
  }

  static MonomialOrder RevLexDegOrder() {
    MonomialOrder tmp_mon_ord;
    tmp_mon_ord += compare_type([](const Monomial<T, TNumberOfVariables> &mon1,
                                   const Monomial<T, TNumberOfVariables> &mon2) {
      for (int i = 25; i >= 0; --i) {
        if (mon1[i]!=mon2[i]) {
          return mon1[i] < mon2[i];
        }
      }
      return false;
    });
    return tmp_mon_ord;
  }

 private:
  compare_container_type comparators_;
};
}  // namespace grobner
