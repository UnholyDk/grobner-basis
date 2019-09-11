#include "Algorithm.h"
#include <iostream>
#include <boost/rational.hpp>
#include "ResidueModulo.h"
#include "wFile.h"
#include <ctime>
#include <time.h>

using type_rational = boost::rational<int>;
using type_residue = ResidueModulo;

void test_1(std::ofstream &output, std::ofstream &output_time) {
  using degree_value_type = grobner::Monomial<type_rational>::degree_value_type;
  unsigned int start_time = clock();
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
  output << alg.reduction(g, syst) << ";\n"; // ans = -0.5ac^4
  unsigned int end_time = clock();
  unsigned int search_time = end_time - start_time;
  output_time << "Test works " << search_time << " milliseconds" << '\n';
}

void test_2(std::ofstream &output, std::ofstream &output_time) {
  using degree_value_type = grobner::Monomial<type_rational>::degree_value_type;
  unsigned int start_time = clock();
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

  auto it = syst.begin();
  output << *it;
  while (it != syst.end()) {
    output << ", " << *it;
    ++it;
  }
  output << ";\n";

  unsigned int end_time = clock();
  unsigned int search_time = end_time - start_time;
  output_time << "Test works " << search_time << " milliseconds" << '\n';
}

void test_3(std::ofstream &output, std::ofstream &output_time) {
  using degree_value_type = grobner::Monomial<type_rational>::degree_value_type;
  unsigned int start_time = clock();
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

  auto it = syst.begin();
  output << *it;
  while (it != syst.end()) {
    output << ", " << *it;
    ++it;
  }
  output << ";\n";

  unsigned int end_time = clock();
  unsigned int search_time = end_time - start_time;
  output_time << "Test works " << search_time << " milliseconds" << '\n';
}

void test_4(std::ofstream &output, std::ofstream &output_time) {
  using degree_value_type = grobner::Monomial<type_rational>::degree_value_type;
  unsigned int start_time = clock();
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

  auto it = syst.begin();
  output << *it;
  while (it != syst.end()) {
    output << ", " << *it;
    ++it;
  }
  output << ";\n";

  unsigned int end_time = clock();
  unsigned int search_time = end_time - start_time;
  output_time << "Test works " << search_time << " milliseconds" << '\n';
}

void test_5(std::ofstream &output, std::ofstream &output_time) {
  using degree_value_type = grobner::Monomial<type_residue>::degree_value_type;
  unsigned int start_time = clock();
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

  output << alg.reduction(g, syst) << ";\n"; // ans = 5a^2c^4

  unsigned int end_time = clock();
  unsigned int search_time = end_time - start_time;
  output_time << "Test works " << search_time << " milliseconds" << '\n';
}

void test_6(std::ofstream &output, std::ofstream &output_time) {
  using degree_value_type = grobner::Monomial<type_rational>::degree_value_type;
  unsigned int start_time = clock();
  grobner::PolynomialVector<type_rational> syst;
  grobner::Polynomial<type_rational> f1, f2, f3;
  std::array<degree_value_type, grobner::detail::gDefaultNumberOfVariables> d;
  std::array<degree_value_type, grobner::detail::gDefaultNumberOfVariables> e;
  std::array<degree_value_type, grobner::detail::gDefaultNumberOfVariables> a;
  d.fill(0);
  e.fill(0);
  a.fill(0);
  d[0] = 1;
  d[1] = 0;
  d[2] = 0;
  e[0] = 0;
  e[1] = 1;
  e[2] = 0;
  grobner::Monomial<type_rational> f11(1, d), f12(1, e);
  f1 += f11;
  f1 += f12;
  syst.add_pol(f1);
  d[0] = 0;
  d[1] = 2;
  d[2] = 0;
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

  auto it = syst.begin();
  output << *it;
  while (it != syst.end()) {
    output << ", " << *it;
    ++it;
  }
  output << ";\n";

  unsigned int end_time = clock();
  unsigned int search_time = end_time - start_time;
  output_time << "Test works " << search_time << " milliseconds" << '\n';
}

void cyclic3(std::ofstream &output, std::ofstream &output_time) {
  using degree_value_type = grobner::Monomial<type_rational>::degree_value_type;
  unsigned int start_time = clock();
  grobner::PolynomialVector<type_rational> syst;
  grobner::Polynomial<type_rational> f1, f2, f3;
  std::array<degree_value_type, grobner::detail::gDefaultNumberOfVariables> d;
  std::array<degree_value_type, grobner::detail::gDefaultNumberOfVariables> e;
  std::array<degree_value_type, grobner::detail::gDefaultNumberOfVariables> a;
  a.fill(0);
  d.fill(0);
  e.fill(0);
  d[2] = 3;
  grobner::Monomial<type_rational> f11(1, d), f12(-1, e);
  f1 += f11;
  f1 += f12;
  d[2] = 0;
  d[0] = 1;
  e[1] = 1;
  a[2] = 1;
  grobner::Monomial<type_rational> f21(1, d), f22(1, e), f23(1, a);
  f2 += f21;
  f2 += f22;
  f3 += f23;
  d[0] = 0;
  d[1] = 2;
  e[2] = 1;
  a[2] = 2;
  grobner::Monomial<type_rational> f31(1, d), f32(1, e), f33(1, a);
  f3 += f31;
  f3 += f32;
  f3 += f33;
  syst.add_pol(f1);
  syst.add_pol(f2);
  syst.add_pol(f3);
  grobner::MonomialOrder<type_rational> lex = grobner::MonomialOrder<type_rational>::Lex();
  grobner::Algorithm<type_rational> alg(lex);
  syst = alg.Buchberger(syst);

  auto it = syst.begin();
  output << *it;
  while (it != syst.end()) {
    output << ", " << *it;
    ++it;
  }
  output << ";\n";

  unsigned int end_time = clock();
  unsigned int search_time = end_time - start_time;
  output_time << "Test works " << search_time << " milliseconds" << '\n';

}

void cyclic4(std::ofstream &output, std::ofstream &output_time) {
  using degree_value_type = grobner::Monomial<type_rational>::degree_value_type;
  unsigned int start_time = clock();
  grobner::PolynomialVector<type_rational> syst;
  grobner::Polynomial<type_rational> f1, f2, f3, f4;
  std::array<degree_value_type, grobner::detail::gDefaultNumberOfVariables> d;
  std::array<degree_value_type, grobner::detail::gDefaultNumberOfVariables> e;
  std::array<degree_value_type, grobner::detail::gDefaultNumberOfVariables> a;
  a.fill(0);
  d.fill(0);
  e.fill(0);

  a[1] = 2;
  grobner::Monomial<type_rational> f11(1, a);
  f1 += f11;
  a[1] = 1;
  a[2] = 1;
  grobner::Monomial<type_rational> f12(1, a);
  f1 += f12;
  a[3] = 1;
  a[2] = 0;
  grobner::Monomial<type_rational> f13(1, a);
  f1 += f13;
  a[1] = 0;
  a[2] = 2;
  a[3] = 0;
  grobner::Monomial<type_rational> f14(1, a);
  f1 += f14;
  a[2] = 1;
  a[3] = 1;
  grobner::Monomial<type_rational> f15(1, a);
  f1 += f15;
  a[2] = 0;
  a[3] = 2;
  grobner::Monomial<type_rational> f16(1, a);
  f1 += f16;
  a[3] = 0;
  a[0] = 1;
  grobner::Monomial<type_rational> f21(1, a);
  f2 += f21;
  a[0] = 0;
  a[1] = 1;
  grobner::Monomial<type_rational> f22(1, a);
  f2 += f22;
  a[1] = 0;
  a[2] = 1;
  grobner::Monomial<type_rational> f23(1, a);
  f2 += f23;
  a[2] = 0;
  a[3] = 1;
  grobner::Monomial<type_rational> f24(1, a);
  f2 += f24;
  a[3] = 4;
  grobner::Monomial<type_rational> f31(1, a);
  f3 += f31;
  a.fill(0);
  grobner::Monomial<type_rational> f32(-1, a);
  f3 += f32;
  a[3] = 0;
  a[2] = 3;
  grobner::Monomial<type_rational> f41(1, a);
  f4 += f41;
  a[2] = 2;
  a[3] = 1;
  grobner::Monomial<type_rational> f42(1, a);
  f4 += f42;
  a[2] = 1;
  a[3] = 2;
  grobner::Monomial<type_rational> f43(1, a);
  f4 += f43;
  a[2] = 0;
  a[3] = 3;
  grobner::Monomial<type_rational> f44(1, a);
  f4 += f44;
  syst.add_pol(f1);
  syst.add_pol(f3);
  syst.add_pol(f2);
  syst.add_pol(f4);
  grobner::MonomialOrder<type_rational> lex = grobner::MonomialOrder<type_rational>::Lex();
  grobner::Algorithm<type_rational> alg(lex);
  //syst = alg.Buchberger(syst);

  auto it = syst.begin();
  output << *it;
  while (it != syst.end()) {
    output << ", " << *it;
    ++it;
  }
  output << ";\n";

  unsigned int end_time = clock();
  unsigned int search_time = end_time - start_time;
  output_time << "Test works " << search_time << " milliseconds" << '\n';
}

void cyclic5(std::ofstream &output, std::ofstream &output_time){
  using degree_value_type = grobner::Monomial<type_rational>::degree_value_type;
  unsigned int start_time = clock();
  grobner::PolynomialVector<type_rational> syst;
  grobner::Polynomial<type_rational> f1, f2, f3, f4, f5;
  std::array<degree_value_type, grobner::detail::gDefaultNumberOfVariables> d;
  std::array<degree_value_type, grobner::detail::gDefaultNumberOfVariables> e;
  std::array<degree_value_type, grobner::detail::gDefaultNumberOfVariables> a;
  a.fill(0);
  d.fill(0);
  e.fill(0);

  a[1] = 2;
  grobner::Monomial<type_rational> f11(1, a);
  f1 += f11;
  a[1] = 1;
  a[2] = 1;
  grobner::Monomial<type_rational> f12(1, a);
  f1 += f12;
  a[3] = 1;
  a[2] = 0;
  grobner::Monomial<type_rational> f13(1, a);
  f1 += f13;
  a[1] = 0;
  a[2] = 2;
  a[3] = 0;
  grobner::Monomial<type_rational> f14(1, a);
  f1 += f14;
  a[2] = 1;
  a[3] = 1;
  grobner::Monomial<type_rational> f15(1, a);
  f1 += f15;
  a[2] = 0;
  a[3] = 0;
  a[1] = 1;
  a[4] = 1;
  grobner::Monomial<type_rational> f16(1, a);
  f1 += f16;
  a[1] = 0;
  a[2] = 1;
  grobner::Monomial<type_rational> f17(1, a);
  f1 += f17;
  a[2] = 0;
  a[4] = 0;
  a[3] = 2;
  grobner::Monomial<type_rational> f18(1, a);
  f1 += f18;
  a[3] = 1;
  a[4] = 1;
  grobner::Monomial<type_rational> f19(1, a);
  f1 += f19;
  a[3] = 0;
  a[4] = 2;
  grobner::Monomial<type_rational> f190(1, a);
  f1 += f190;


  a[3] = 0;
  a[0] = 1;
  grobner::Monomial<type_rational> f21(1, a);
  f2 += f21;
  a[0] = 0;
  a[1] = 1;
  grobner::Monomial<type_rational> f22(1, a);
  f2 += f22;
  a[1] = 0;
  a[2] = 1;
  grobner::Monomial<type_rational> f23(1, a);
  f2 += f23;
  a[2] = 0;
  a[3] = 1;
  grobner::Monomial<type_rational> f24(1, a);
  f2 += f24;
  a[3] = 0;
  a[4] = 1;
  grobner::Monomial<type_rational> f25(1, a);
  f2 += f25;
  a[3] = 0;
  a[4] = 5;
  grobner::Monomial<type_rational> f31(1, a);
  f3 += f31;
  a.fill(0);
  grobner::Monomial<type_rational> f32(-1, a);
  f3 += f32;
  a[3] = 0;
  a[2] = 3;
  grobner::Monomial<type_rational> f41(1, a);
  f4 += f41;
  a[2] = 2;
  a[3] = 1;
  grobner::Monomial<type_rational> f42(1, a);
  f4 += f42;
  a[2] = 1;
  a[3] = 2;
  grobner::Monomial<type_rational> f43(1, a);
  f4 += f43;
  a[2] = 0;
  a[3] = 3;
  grobner::Monomial<type_rational> f44(1, a);
  f4 += f44;
  a[3] = 0;
  a[2] = 2;
  a[4] = 1;
  grobner::Monomial<type_rational> f45(1, a);
  f4 += f45;
  a[2] = 1;
  a[3] = 1;
  grobner::Monomial<type_rational> f46(1, a);
  f4 += f46;
  a[3] = 0;
  a[4] = 2;
  grobner::Monomial<type_rational> f47(1, a);
  f4 += f47;
  a[2] = 0;
  a[3] = 2;
  a[4] = 1;
  grobner::Monomial<type_rational> f48(1, a);
  f4 += f48;
  a[3] = 1;
  a[4] = 2;
  grobner::Monomial<type_rational> f49(1, a);
  f4 += f49;
  a[3] = 0;
  a[4] = 3;
  grobner::Monomial<type_rational> f490(1, a);
  f4 += f490;
  a[4] = 0;
  a[3] = 4;
  grobner::Monomial<type_rational> f51(1, a);
  f5 += f51;
  a[3] = 3;
  a[4] = 1;
  grobner::Monomial<type_rational> f52(1, a);
  f5 += f52;
  a[3] = 2;
  a[4] = 2;
  grobner::Monomial<type_rational> f53(1, a);
  f5 += f53;
  a[3] = 1;
  a[4] = 3;
  grobner::Monomial<type_rational> f54(1, a);
  f5 += f54;
  a[3] = 0;
  a[4] = 4;
  grobner::Monomial<type_rational> f55(1, a);
  f5 += f55;
  syst.add_pol(f1);
  syst.add_pol(f3);
  syst.add_pol(f2);
  syst.add_pol(f4);
  syst.add_pol(f5);
  grobner::MonomialOrder<type_rational> lex = grobner::MonomialOrder<type_rational>::Lex();
  grobner::Algorithm<type_rational> alg(lex);
  //syst = alg.Buchberger(syst);

  auto it = syst.begin();
  output << *it;
  while (it != syst.end()) {
    output << ", " << *it;
    ++it;
  }
  output << ";\n";

  unsigned int end_time = clock();
  unsigned int search_time = end_time - start_time;
  output_time << "Test works " << search_time << " milliseconds" << '\n';
}


void all_tests() {
  wFile output("output.txt");
  wFile output_time("output_time.txt");
  test_1(output(), output_time());
  test_2(output(), output_time());
  test_3(output(), output_time());
  test_4(output(), output_time());
  test_5(output(), output_time());
  test_6(output(), output_time());
  cyclic3(output(), output_time());
  cyclic4(output(), output_time());
  cyclic5(output(), output_time());
}

bool check() {
  all_tests();
  std::vector<std::string>
      true_ans = {"(-1/2ac^4)", "(-1/2ac^4)", "(-2/1b)+(-b^2)", "(-c^3)+(-2/1ac^2)+(-a^2)", "(5a^2c^4)", "2"};
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
