#include "PolynomialOrder.h"
template <typename T>
class PolynomialSet {
public:
    PolynomialSet() {}

    PolynomialSet(const Polynomial<T>& pol) {
        pols.push_back(pol);
    }

    auto begin() {
        return pols.begin();
    }

    auto end() {
        return pols.end();
    }

    auto begin() const {
        return pols.begin();
    }

    auto end() const {
        return pols.end();
    }

    size_t size() {
        return pols.size();
    }

    Polynomial<T> operator[](size_t i) const {
        return pols[i];
    }

    Polynomial<T>& operator[](size_t i) {
        return pols[i];
    }

    void operator+=(const Polynomial<T>& pol) {
        pols.push_back(pol);
    }

private:
    std::vector<Polynomial<T>> pols;
};
