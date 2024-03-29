#include <functional>
#include "Monomial.h"

namespace grobner {
template<typename T, index_type TNumberOfVariables = detail::gDefaultNumberOfVariables>
class MonomialOrder {
  using monomial = Monomial<T, TNumberOfVariables>;
  using index_type = typename monomial::index_type;
  using compare_signature_type = bool(const monomial &, const monomial &);
  using compare_type = std::function<compare_signature_type>;
  using compare_container_type = std::vector<compare_type>;

 public:
  bool is_less(const monomial &mon1, const monomial &mon2) const {
    for (auto comparator : comparators_) {
      if (comparator(mon1, mon2) || comparator(mon2, mon1)) {
        return comparator(mon1, mon2);
      }
    }
    return false;
  }

  bool is_less_eq(const monomial &mon1, const monomial &mon2) const {
    return !is_less(mon2, mon1);
  }

  bool operator()(const monomial &mon1, const monomial &mon2) const {
    return is_less(mon1, mon2);
  }

  compare_container_type get_comparators() const {
    return comparators_;
  }

  static const MonomialOrder &Lex() {
    static MonomialOrder LexOrder{[](const monomial &mon1,
                                     const monomial &mon2) {
      for (index_type i = 0; i < TNumberOfVariables; ++i) {
        if (mon1[i] != mon2[i]) {
          return mon1[i] < mon2[i];
        }
      }
      return false;
    }};
    return LexOrder;
  }

  static const MonomialOrder &RevLex() {
    static MonomialOrder RevLexOrder{[](const monomial &mon1,
                                        const monomial &mon2) {
      for (index_type i = 0; i < TNumberOfVariables; ++i) {
        if (mon1[i] != mon2[i]) {
          return mon1[i] > mon2[i];
        }
      }
      return false;
    }};
    return RevLexOrder;
  }

  static const MonomialOrder &Deg() {
    static MonomialOrder DegOrder{[](const monomial &mon1,
                                     const monomial &mon2) {
      unsigned int sum1 = 0, sum2 = 0;
      for (index_type i = 0; i < TNumberOfVariables; ++i) {
        sum1 += mon1[i];
        sum2 += mon2[i];
      }
      return sum1 < sum2;
    }};
    return DegOrder;
  }

  static const MonomialOrder &DegLex() {
    static MonomialOrder DegLexOrder{Deg() + Lex()};
    return DegLexOrder;
  }

  static const MonomialOrder &DegRevLex() {
    static MonomialOrder DegRevLexOrder{Deg() + RevLex()};
    return DegRevLexOrder;
  }

 private:
  MonomialOrder() = default;

  MonomialOrder(std::initializer_list<compare_type> comparators) : comparators_(comparators) {}

  MonomialOrder &operator+=(const compare_type &compare) {
    comparators_.push_back(compare);
    return *this;
  }

  MonomialOrder &operator+=(const MonomialOrder &other) {
    comparators_.reserve(comparators_.size() + (other.get_comparators()).size());
    comparators_.insert(comparators_.end(),
                        (other.get_comparators()).begin(),
                        (other.get_comparators()).end());
    return *this;
  }

  MonomialOrder operator+(const MonomialOrder &other) const {
    MonomialOrder tmp = *this;
    tmp += other;
    return tmp;
  }

  compare_container_type comparators_;
};
}  // namespace grobner
