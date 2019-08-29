#include "Algorithm.h"
#include <iostream>
#include <boost/rational.hpp>
#include "ResidueModulo.h"
#include "wFile.h"
#include <cstdio>

using type_rational = boost::rational<int>;
using type_residue = ResidueModulo;

void test_1(std::ofstream &output) {
  using degree_value_type = grobner::Monomial<type_rational>::degree_value_type;

  grobner::PolynomialVector<type_rational> syst;
  grobner::Polynomial<type_rational> f1, f2, f3, f4, g, ans;
  std::array<degree_value_type, grobner::detail::gDefaultNumberOfVariables> d;
  std::array<degree_value_type, grobner::detail::gDefaultNumberOfVariables> e;
  d.fill(0);
  e.fill(0);
  d[0] = 2;
  d[1] = 1;
  d[2] = 0;
  e[0] = 1;
  e[1] = 1;
  e[2] = 0;
  grobner::Monomial<type_rational> f11(1, d), f12(-1, e);
  f1 += f11;
  f1 += f12;
  syst.add_pol(f1);
  d[0] = 0;
  d[1] = 2;
  d[2] = 0;
  e[0] = 0;
  e[1] = 1;
  e[2] = 1;
  grobner::Monomial<type_rational> f21(1, d), f22(2, e);
  f2 += f21;
  f2 += f22;
  syst.add_pol(f2);
  d[0] = 1;
  d[1] = 1;
  d[2] = 1;
  e[0] = 1;
  e[1] = 0;
  e[2] = 2;
  grobner::Monomial<type_rational> f31(-1, d), f32(-2, e);
  f3 += f31;
  f3 += f32;
  syst.add_pol(f3);
  d[0] = 2;
  d[1] = 0;
  d[2] = 2;
  e[0] = 1;
  e[1] = 0;
  e[2] = 2;
  grobner::Monomial<type_rational> f41(2, d), f42(1, e);
  f4 += f41;
  f4 += f42;
  syst.add_pol(f4);
  d[0] = 2;
  d[1] = 0;
  d[2] = 4;
  e[0] = 1;
  e[1] = 1;
  e[2] = 3;
  grobner::Monomial<type_rational> g1(5, d), g2(-1, e);
  g += g1;
  g += g2;
  grobner::MonomialOrder<type_rational> lex = grobner::MonomialOrder<type_rational>::Lex();
  grobner::Algorithm<type_rational> alg(lex);
  output << alg.reduction(g, syst) << "\n"; // ans = -0.5ac^4
}

void test_2(std::ofstream &output) {
  using degree_value_type = grobner::Monomial<type_rational>::degree_value_type;

  grobner::PolynomialVector<type_rational> syst;
  grobner::Polynomial<type_rational> f1, f2, g;
  std::array<degree_value_type, grobner::detail::gDefaultNumberOfVariables> d;
  std::array<degree_value_type, grobner::detail::gDefaultNumberOfVariables> e;
  d.fill(0);
  e.fill(0);
  d[0] = 2;
  d[1] = 1;
  d[2] = 0;
  e[0] = 1;
  e[1] = 0;
  e[2] = 1;
  grobner::Monomial<type_rational> f11(1, d), f12(-1, e);
  f1 += f11;
  f1 += f12;
  syst.add_pol(f1);
  d[0] = 0;
  d[1] = 2;
  d[2] = 0;
  e[0] = 0;
  e[1] = 1;
  e[2] = 1;
  grobner::Monomial<type_rational> f21(1, d), f22(2, e);
  f2 += f21;
  f2 += f22;
  syst.add_pol(f2);
  d[0] = 2;
  d[1] = 0;
  d[2] = 4;
  e[0] = 1;
  e[1] = 1;
  e[2] = 3;
  grobner::Monomial<type_rational> g1(5, d), g2(-1, e);
  g += g1;
  g += g2;
  grobner::MonomialOrder<type_rational> lex = grobner::MonomialOrder<type_rational>::Lex();
  grobner::Algorithm<type_rational> alg(lex);
  syst = alg.Buchberger(syst);
  output << alg.reduction(g, syst) << "\n"; // ans = -0.5ac^4
}

void test_3(std::ofstream &output) {
  using degree_value_type = grobner::Monomial<type_rational>::degree_value_type;

  grobner::PolynomialVector<type_rational> syst;
  grobner::Polynomial<type_rational> f1, f2, f3;
  std::array<degree_value_type, grobner::detail::gDefaultNumberOfVariables> d;
  std::array<degree_value_type, grobner::detail::gDefaultNumberOfVariables> e;
  d.fill(0);
  e.fill(0);
  d[0] = 1;
  d[1] = 1;
  d[2] = 0;
  e[0] = 0;
  e[1] = 1;
  e[2] = 1;
  grobner::Monomial<type_rational> f11(1, d), f12(2, e);
  f1 += f11;
  f1 += f12;
  syst.add_pol(f1);
  d[0] = 1;
  d[1] = 0;
  d[2] = 0;
  e[0] = 0;
  e[1] = 1;
  e[2] = 0;
  grobner::Monomial<type_rational> f21(1, d), f22(-1, e);
  f2 += f21;
  f2 += f22;
  syst.add_pol(f2);
  d[0] = 0;
  d[1] = 1;
  d[2] = 1;
  e[0] = 0;
  e[1] = 1;
  e[2] = 0;
  grobner::Monomial<type_rational> f31(1, d), f32(-1, e);
  f3 += f31;
  f3 += f32;
  syst.add_pol(f3);
  grobner::MonomialOrder<type_rational>
      lex = grobner::MonomialOrder<type_rational>::Lex();
  grobner::Algorithm<type_rational> alg(lex);
  syst = alg.Buchberger(syst);
  output << syst[3] << "\n"; // ans = +(-2b)+(-1b^2)
}

void test_4(std::ofstream &output) {
  using degree_value_type = grobner::Monomial<type_rational>::degree_value_type;

  grobner::PolynomialVector<type_rational> syst;
  grobner::Polynomial<type_rational> f1, f2;
  std::array<degree_value_type, grobner::detail::gDefaultNumberOfVariables> d;
  std::array<degree_value_type, grobner::detail::gDefaultNumberOfVariables> e;
  d.fill(0);
  e.fill(0);
  d[0] = 2;
  d[1] = 1;
  d[2] = 0;
  e[0] = 1;
  e[1] = 0;
  e[2] = 1;
  grobner::Monomial<type_rational> f11(1, d), f12(2, e);
  f1 += f11;
  f1 += f12;
  d[0] = 0;
  d[1] = 0;
  d[2] = 2;
  grobner::Monomial<type_rational> f13(1, d);
  f1 += f13;
  syst.add_pol(f1);
  d[0] = 0;
  d[1] = 1;
  d[2] = 1;
  e[0] = 0;
  e[1] = 0;
  e[2] = 0;
  grobner::Monomial<type_rational> f21(1, d), f22(-1, e);
  f2 += f21;
  f2 += f22;
  syst.add_pol(f2);
  grobner::MonomialOrder<type_rational> lex = grobner::MonomialOrder<type_rational>::Lex();
  grobner::Algorithm<type_rational> alg(lex);
  syst = alg.Buchberger(syst);
  output << syst[2] << "\n"; // ans = +(-1c^3)+(-2ac^2)+(-1a^2)
}

void test_5(std::ofstream &output) {
  using degree_value_type = grobner::Monomial<type_residue>::degree_value_type;

  ResidueModulo a1(1, 7);
  ResidueModulo a2(-1, 7);
  ResidueModulo a3(5, 7);
  ResidueModulo a4(2, 7);
  ResidueModulo a5(-1, 7);
  ResidueModulo a6(-2, 7);

  grobner::PolynomialVector<type_residue> syst;
  grobner::Polynomial<type_residue> f1, f2, f3, f4, g, ans;
  std::array<degree_value_type, grobner::detail::gDefaultNumberOfVariables> d;
  std::array<degree_value_type, grobner::detail::gDefaultNumberOfVariables> e;
  d.fill(0);
  e.fill(0);
  d[0] = 2;
  d[1] = 1;
  d[2] = 0;
  e[0] = 1;
  e[1] = 1;
  e[2] = 0;
  grobner::Monomial<type_residue> f11(a1, d), f12(a2, e);
  f1 += f11;
  f1 += f12;
  syst.add_pol(f1);
  d[0] = 0;
  d[1] = 2;
  d[2] = 0;
  e[0] = 0;
  e[1] = 1;
  e[2] = 1;
  grobner::Monomial<type_residue> f21(a1, d), f22(a4, e);
  f2 += f21;
  f2 += f22;
  syst.add_pol(f2);
  d[0] = 1;
  d[1] = 1;
  d[2] = 1;
  e[0] = 1;
  e[1] = 0;
  e[2] = 2;
  grobner::Monomial<type_residue> f31(a2, d), f32(a6, e);
  f3 += f31;
  f3 += f32;
  syst.add_pol(f3);
  d[0] = 2;
  d[1] = 0;
  d[2] = 2;
  e[0] = 1;
  e[1] = 0;
  e[2] = 2;
  grobner::Monomial<type_residue> f41(a4, d), f42(a1, e);
  f4 += f41;
  f4 += f42;
  syst.add_pol(f4);
  d[0] = 2;
  d[1] = 0;
  d[2] = 4;
  e[0] = 1;
  e[1] = 1;
  e[2] = 3;
  grobner::Monomial<type_residue> g1(a3, d), g2(a2, e);
  g += g1;
  g += g2;
  grobner::MonomialOrder<type_residue> lex = grobner::MonomialOrder<type_residue>::Lex();
  grobner::Algorithm<type_residue> alg(lex);
  output << alg.reduction(g, syst) << "\n"; // ans = 5a^2c^4
}

void all_tests() {
  wFile output("output.txt");
  test_1(output());
  test_2(output());
  test_3(output());
  test_4(output());
  test_5(output());
}

bool check() {
  all_tests();
  std::vector<std::string>
      true_ans = {"(-1/2ac^4)", "(-1/2ac^4)", "(-2/1b)+(-b^2)", "(-c^3)+(-2/1ac^2)+(-a^2)", "(5a^2c^4)"};
  std::ifstream output("output.txt");
  std::string curr_ans;
  for (size_t test_id = 1; test_id <= true_ans.size();
       ++test_id) {
    getline(output, curr_ans);
    if (curr_ans != true_ans[test_id - 1]) {
      std::cout << "WA " << test_id << '\n';
      output.close();
      return false;
    }
  }
  output.close();
  return true;
}
