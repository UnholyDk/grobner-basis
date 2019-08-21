#include "Algorithm.h"
#include <iostream>
#include <boost/rational.hpp>
#include "ResidueModulo.h"
#include <cstdio>
#include <fstream>

using type_rational = boost::rational<int>;
using type_residue = ResidueModulo;

int test_1(std::ofstream &output) {
  grobner::PolynomialVector<type_rational, numberVariables> syst;
  grobner::Polynomial<type_rational, numberVariables> f1, f2, f3, f4, g, ans;
  std::array<deg_value_type, numberVariables> d;
  d.fill(0);
  std::array<deg_value_type, numberVariables> e;
  e.fill(0);
  d[0] = 2;
  d[1] = 1;
  d[2] = 0;
  e[0] = 1;
  e[1] = 1;
  e[2] = 0;
  grobner::Monomial<type_rational, numberVariables> f11(1, d), f12(-1, e);
  f1 += f11;
  f1 += f12;
  syst.add_pol(f1);
  d[0] = 0;
  d[1] = 2;
  d[2] = 0;
  e[0] = 0;
  e[1] = 1;
  e[2] = 1;
  grobner::Monomial<type_rational, numberVariables> f21(1, d), f22(2, e);
  f2 += f21;
  f2 += f22;
  syst.add_pol(f2);
  d[0] = 1;
  d[1] = 1;
  d[2] = 1;
  e[0] = 1;
  e[1] = 0;
  e[2] = 2;
  grobner::Monomial<type_rational, numberVariables> f31(-1, d), f32(-2, e);
  f3 += f31;
  f3 += f32;
  syst.add_pol(f3);
  d[0] = 2;
  d[1] = 0;
  d[2] = 2;
  e[0] = 1;
  e[1] = 0;
  e[2] = 2;
  grobner::Monomial<type_rational, numberVariables> f41(2, d), f42(1, e);
  f4 += f41;
  f4 += f42;
  syst.add_pol(f4);
  d[0] = 2;
  d[1] = 0;
  d[2] = 4;
  e[0] = 1;
  e[1] = 1;
  e[2] = 3;
  grobner::Monomial<type_rational, numberVariables> g1(5, d), g2(-1, e);
  g += g1;
  g += g2;
  grobner::MonomialOrder<type_rational, numberVariables>
      lex = grobner::MonomialOrder<type_rational, numberVariables>::Lex();
  grobner::Algorithm<type_rational, numberVariables> alg(lex);
  output << alg.reduction(g, syst) << "\n"; // ans = -0.5ac^4
  return 0;
}

int test_2(std::ofstream &output) {
  grobner::PolynomialVector<type_rational, numberVariables> syst;
  grobner::Polynomial<type_rational, numberVariables> f1, f2, g;
  std::array<deg_value_type, numberVariables> d;
  d.fill(0);
  std::array<deg_value_type, numberVariables> e;
  e.fill(0);
  d[0] = 2;
  d[1] = 1;
  d[2] = 0;
  e[0] = 1;
  e[1] = 0;
  e[2] = 1;
  grobner::Monomial<type_rational, numberVariables> f11(1, d), f12(-1, e);
  f1 += f11;
  f1 += f12;
  syst.add_pol(f1);
  d[0] = 0;
  d[1] = 2;
  d[2] = 0;
  e[0] = 0;
  e[1] = 1;
  e[2] = 1;
  grobner::Monomial<type_rational, numberVariables> f21(1, d), f22(2, e);
  f2 += f21;
  f2 += f22;
  syst.add_pol(f2);
  d[0] = 2;
  d[1] = 0;
  d[2] = 4;
  e[0] = 1;
  e[1] = 1;
  e[2] = 3;
  grobner::Monomial<type_rational, numberVariables> g1(5, d), g2(-1, e);
  g += g1;
  g += g2;
  grobner::MonomialOrder<type_rational, numberVariables>
      lex = grobner::MonomialOrder<type_rational, numberVariables>::Lex();
  grobner::Algorithm<type_rational, numberVariables> alg(lex);
  syst = alg.Buchberger(syst);
  output << alg.reduction(g, syst) << "\n"; // ans = -0.5ac^4
  return 0;
}

int test_3(std::ofstream &output) {
  grobner::PolynomialVector<type_rational, numberVariables> syst;
  grobner::Polynomial<type_rational, numberVariables> f1, f2, f3;
  std::array<deg_value_type, numberVariables> d;
  d.fill(0);
  std::array<deg_value_type, numberVariables> e;
  e.fill(0);
  d[0] = 1;
  d[1] = 1;
  d[2] = 0;
  e[0] = 0;
  e[1] = 1;
  e[2] = 1;
  grobner::Monomial<type_rational, numberVariables> f11(1, d), f12(2, e);
  f1 += f11;
  f1 += f12;
  syst.add_pol(f1);
  d[0] = 1;
  d[1] = 0;
  d[2] = 0;
  e[0] = 0;
  e[1] = 1;
  e[2] = 0;
  grobner::Monomial<type_rational, numberVariables> f21(1, d), f22(-1, e);
  f2 += f21;
  f2 += f22;
  syst.add_pol(f2);
  d[0] = 0;
  d[1] = 1;
  d[2] = 1;
  e[0] = 0;
  e[1] = 1;
  e[2] = 0;
  grobner::Monomial<type_rational, numberVariables> f31(1, d), f32(-1, e);
  f3 += f31;
  f3 += f32;
  syst.add_pol(f3);
  grobner::MonomialOrder<type_rational, numberVariables>
      lex = grobner::MonomialOrder<type_rational, numberVariables>::Lex();
  grobner::Algorithm<type_rational, numberVariables> alg(lex);
  syst = alg.Buchberger(syst);
  output << syst[3] << "\n"; // ans = +(-2b)+(-1b^2)
  return 0;
}

int test_4(std::ofstream &output) {
  grobner::PolynomialVector<type_rational, numberVariables> syst;
  grobner::Polynomial<type_rational, numberVariables> f1, f2;
  std::array<deg_value_type, numberVariables> d;
  d.fill(0);
  std::array<deg_value_type, numberVariables> e;
  e.fill(0);
  d[0] = 2;
  d[1] = 1;
  d[2] = 0;
  e[0] = 1;
  e[1] = 0;
  e[2] = 1;
  grobner::Monomial<type_rational, numberVariables> f11(1, d), f12(2, e);
  f1 += f11;
  f1 += f12;
  d[0] = 0;
  d[1] = 0;
  d[2] = 2;
  grobner::Monomial<type_rational, numberVariables> f13(1, d);
  f1 += f13;
  syst.add_pol(f1);
  d[0] = 0;
  d[1] = 1;
  d[2] = 1;
  e[0] = 0;
  e[1] = 0;
  e[2] = 0;
  grobner::Monomial<type_rational, numberVariables> f21(1, d), f22(-1, e);
  f2 += f21;
  f2 += f22;
  syst.add_pol(f2);
  grobner::MonomialOrder<type_rational, numberVariables>
      lex = grobner::MonomialOrder<type_rational, numberVariables>::Lex();
  grobner::Algorithm<type_rational, numberVariables> alg(lex);
  syst = alg.Buchberger(syst);
  output << syst[2] << "\n"; // ans = +(-1c^3)+(-2ac^2)+(-1a^2)
  return 0;
}

int test_5(std::ofstream &output) {
  //freopen("output.txt", "w", stdout);
  ResidueModulo a1(1, 7);
  ResidueModulo a2(-1, 7);
  ResidueModulo a3(5, 7);
  ResidueModulo a4(2, 7);
  ResidueModulo a5(-1, 7);
  ResidueModulo a6(-2, 7);

  grobner::PolynomialVector<type_residue, numberVariables> syst;
  grobner::Polynomial<type_residue, numberVariables> f1, f2, f3, f4, g, ans;
  std::array<deg_value_type, numberVariables> d;
  d.fill(0);
  std::array<deg_value_type, numberVariables> e;
  e.fill(0);
  d[0] = 2;
  d[1] = 1;
  d[2] = 0;
  e[0] = 1;
  e[1] = 1;
  e[2] = 0;
  grobner::Monomial<type_residue, numberVariables> f11(a1, d), f12(a2, e);
  f1 += f11;
  f1 += f12;
  syst.add_pol(f1);
  d[0] = 0;
  d[1] = 2;
  d[2] = 0;
  e[0] = 0;
  e[1] = 1;
  e[2] = 1;
  grobner::Monomial<type_residue, numberVariables> f21(a1, d), f22(a4, e);
  f2 += f21;
  f2 += f22;
  syst.add_pol(f2);
  d[0] = 1;
  d[1] = 1;
  d[2] = 1;
  e[0] = 1;
  e[1] = 0;
  e[2] = 2;
  grobner::Monomial<type_residue, numberVariables> f31(a2, d), f32(a6, e);
  f3 += f31;
  f3 += f32;
  syst.add_pol(f3);
  d[0] = 2;
  d[1] = 0;
  d[2] = 2;
  e[0] = 1;
  e[1] = 0;
  e[2] = 2;
  grobner::Monomial<type_residue, numberVariables> f41(a4, d), f42(a1, e);
  f4 += f41;
  f4 += f42;
  syst.add_pol(f4);
  d[0] = 2;
  d[1] = 0;
  d[2] = 4;
  e[0] = 1;
  e[1] = 1;
  e[2] = 3;
  grobner::Monomial<type_residue, numberVariables> g1(a3, d), g2(a2, e);
  g += g1;
  g += g2;
  grobner::MonomialOrder<type_residue, numberVariables>
      lex = grobner::MonomialOrder<type_residue, numberVariables>::Lex();
  grobner::Algorithm<type_residue, numberVariables> alg(lex);
  output << alg.reduction(g, syst) << "\n"; // ans = 5a^2c^4
  return 0;
}

int all_tests() {
  std::ofstream output("output.txt");
  test_1(output);
  test_2(output);
  test_3(output);
  test_4(output);
  test_5(output);
  output.close();
  return 0;
}
