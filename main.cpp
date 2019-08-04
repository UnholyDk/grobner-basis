#include <iostream>
#include "Algorithm.h"
#include <boost/rational.hpp>

int main() {
    grobner::PolynomialSet<double> syst;
    grobner::Polynomial<double> f1, f2, f3, f4, g, ans;

    std::vector<int> d(26);
    std::vector<int> e(26);

    d[0] = 2;
    d[1] = 1;
    d[2] = 0;
    e[0] = 1;
    e[1] = 1;
    e[2] = 0;
    grobner::Monomial<double> f11(1, d), f12(-1, e);
    f1 += f11;
    f1 += f12;
    syst += f1;

    d[0] = 0;
    d[1] = 2;
    d[2] = 0;
    e[0] = 0;
    e[1] = 1;
    e[2] = 1;
    grobner::Monomial<double> f21(1, d), f22(2, e);
    f2 += f21;
    f2 += f22;
    syst += f2;

    d[0] = 1;
    d[1] = 1;
    d[2] = 1;
    e[0] = 1;
    e[1] = 0;
    e[2] = 2;
    grobner::Monomial<double> f31(-1, d), f32(-2, e);
    f3 += f31;
    f3 += f32;
    syst += f3;

    d[0] = 2;
    d[1] = 0;
    d[2] = 2;
    e[0] = 1;
    e[1] = 0;
    e[2] = 2;
    grobner::Monomial<double> f41(2, d), f42(1, e);
    f4 += f41;
    f4 += f42;
    syst += f4;

    d[0] = 2;
    d[1] = 0;
    d[2] = 4;
    e[0] = 1;
    e[1] = 1;
    e[2] = 3;
    grobner::Monomial<double> g1(5, d), g2(-1, e);
    g += g1;
    g += g2;

    grobner::MonomialOrder<double> lex;
    lex.add_order(grobner::lexicograph<double>);

    grobner::Algorithm<double> alg(lex);
    std::cout << alg.reduction(g, syst);
    return 0;
}