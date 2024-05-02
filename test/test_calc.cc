#include "test_header.h"

TEST(Calc, Test_1) {
  std::string exp = "x";
  bool is_x_set = true;
  long double x = 3.0;

  long double tol = 1e-15;

  my::CalcSolution calc(exp, is_x_set, x);
  calc.Compute();

  EXPECT_TRUE(fabsl(calc.GetResult() - x) < tol);
  EXPECT_EQ(calc.GetError(), false);
}

TEST(Calc, Test_2) {
  std::string exp = "(()";
  bool is_x_set = true;
  long double x = 3.0;

  my::CalcSolution calc(exp, is_x_set, x);
  calc.Compute();

  EXPECT_EQ(calc.GetError(), true);
}

TEST(Calc, Test_3) {
  std::string exp = "())";
  bool is_x_set = true;
  long double x = 3.0;

  my::CalcSolution calc(exp, is_x_set, x);
  calc.Compute();

  EXPECT_EQ(calc.GetError(), true);
}

TEST(Calc, Test_4) {
  std::string exp = "acos(cos(x))";
  bool is_x_set = true;
  long double x = 0.45;

  long double tol = 1e-15;

  my::CalcSolution calc(exp, is_x_set, x);
  calc.Compute();

  EXPECT_TRUE(fabsl(calc.GetResult() - x) < tol);
  EXPECT_EQ(calc.GetError(), false);
}

TEST(Calc, Test_5) {
  std::string exp = "cos(acos(x))";
  bool is_x_set = true;
  long double x = 0.45;

  long double tol = 1e-15;

  my::CalcSolution calc(exp, is_x_set, x);
  calc.Compute();

  EXPECT_TRUE(fabsl(calc.GetResult() - x) < tol);
  EXPECT_EQ(calc.GetError(), false);
}

TEST(Calc, Test_6) {
  std::string exp = "cos(x)";
  bool is_x_set = true;
  long double x = 0.2;

  long double tol = 1e-15;

  my::CalcSolution calc(exp, is_x_set, x);
  calc.Compute();

  EXPECT_TRUE(fabsl(calc.GetResult() - cosl(x)) < tol);
  EXPECT_EQ(calc.GetError(), false);
}

TEST(Calc, Test_7) {
  std::string exp = "cos(x)";
  bool is_x_set = true;
  long double x = 23;

  long double tol = 1e-15;

  my::CalcSolution calc(exp, is_x_set, x);
  calc.Compute();

  EXPECT_TRUE(fabsl(calc.GetResult() - cosl(x)) < tol);
  EXPECT_EQ(calc.GetError(), false);
}

TEST(Calc, Test_8) {
  std::string exp = "sin(x)";
  bool is_x_set = true;
  long double x = 0.45;

  long double tol = 1e-15;

  my::CalcSolution calc(exp, is_x_set, x);
  calc.Compute();

  EXPECT_TRUE(fabsl(calc.GetResult() - sin(x)) < tol);
  EXPECT_EQ(calc.GetError(), false);
}

TEST(Calc, Test_9) {
  std::string exp = "asin(x)";
  bool is_x_set = true;
  long double x = 45;

  my::CalcSolution calc(exp, is_x_set, x);
  calc.Compute();

  EXPECT_TRUE(isnanl(calc.GetResult()));
  EXPECT_EQ(calc.GetError(), false);
}

TEST(Calc, Test_10) {
  std::string exp = "asin(sin(x))";
  bool is_x_set = true;
  long double x = 0.45;

  long double tol = 1e-15;

  my::CalcSolution calc(exp, is_x_set, x);
  calc.Compute();

  EXPECT_TRUE(fabsl(calc.GetResult() - x) < tol);
  EXPECT_EQ(calc.GetError(), false);
}

TEST(Calc, Test_11) {
  std::string exp = "atan(tan(x))";
  bool is_x_set = true;
  long double x = 0.45;

  long double tol = 1e-15;

  my::CalcSolution calc(exp, is_x_set, x);
  calc.Compute();

  EXPECT_TRUE(fabsl(calc.GetResult() - x) < tol);
  EXPECT_EQ(calc.GetError(), false);
}

TEST(Calc, Test_12) {
  std::string exp = "atan(tan(x))";
  bool is_x_set = true;
  long double x = 0.45;

  long double tol = 1e-15;

  my::CalcSolution calc(exp, is_x_set, x);
  calc.Compute();

  EXPECT_TRUE(fabsl(calc.GetResult() - x) < tol);
  EXPECT_EQ(calc.GetError(), false);
}

TEST(Calc, Test_13) {
  std::string exp = "sqrt(x)";
  bool is_x_set = true;
  long double x = -12;

  my::CalcSolution calc(exp, is_x_set, x);
  calc.Compute();

  EXPECT_TRUE(isnanl(calc.GetResult()));
  EXPECT_EQ(calc.GetError(), false);
}

TEST(Calc, Test_14) {
  std::string exp = "sqrt(x)";
  bool is_x_set = true;
  long double x = 4;

  long double tol = 1e-15;

  my::CalcSolution calc(exp, is_x_set, x);
  calc.Compute();

  EXPECT_TRUE(fabsl(calc.GetResult() - sqrt(x)) < tol);
  EXPECT_EQ(calc.GetError(), false);
}

TEST(Calc, Test_15) {
  std::string exp = "ln(x)";
  bool is_x_set = true;
  long double x = expl(1.0);

  long double tol = 1e-15;

  my::CalcSolution calc(exp, is_x_set, x);
  calc.Compute();

  EXPECT_TRUE(fabsl(calc.GetResult() - log(x)) < tol);
  EXPECT_EQ(calc.GetError(), false);
}

TEST(Calc, Test_16) {
  std::string exp = "ln(x)";
  bool is_x_set = true;
  long double x = 0;

  my::CalcSolution calc(exp, is_x_set, x);
  calc.Compute();

  EXPECT_TRUE(isinfl(calc.GetResult()));
  EXPECT_EQ(calc.GetError(), false);
}

TEST(Calc, Test_17) {
  std::string exp = "log10(x)";
  bool is_x_set = true;
  long double x = 10;

  long double tol = 1e-15;

  my::CalcSolution calc(exp, is_x_set, x);
  calc.Compute();

  EXPECT_TRUE(fabsl(calc.GetResult() - log10(x)) < tol);
  EXPECT_EQ(calc.GetError(), false);
}

TEST(Calc, Test_18) {
  std::string exp = "log10(x)";
  bool is_x_set = true;
  long double x = 0;

  my::CalcSolution calc(exp, is_x_set, x);
  calc.Compute();

  EXPECT_TRUE(isinfl(calc.GetResult()));
  EXPECT_EQ(calc.GetError(), false);
}

TEST(Calc, Test_19) {
  std::string exp = "atan(x)";
  bool is_x_set = true;
  long double x = 0.34;

  long double tol = 1e-15;

  my::CalcSolution calc(exp, is_x_set, x);
  calc.Compute();

  EXPECT_TRUE(fabsl(calc.GetResult() - atanl(x)) < tol);
  EXPECT_EQ(calc.GetError(), false);
}

TEST(Calc, Test_20) {
  std::string exp = "4mod(3+2)";
  bool is_x_set = true;

  long double tol = 1e-15;

  my::CalcSolution calc(exp, false, 0.0);
  calc.Compute();

  EXPECT_TRUE(fabsl(calc.GetResult() - fmodl(4.0, 5.0)) < tol);
  EXPECT_EQ(calc.GetError(), false);
}

TEST(Calc, Test_21) {
  std::string exp = "5mod(2+2)";
  bool is_x_set = true;

  long double tol = 1e-15;

  my::CalcSolution calc(exp, false, 0.0);
  calc.Compute();

  EXPECT_TRUE(fabsl(calc.GetResult() - fmodl(5.0, 4.0)) < tol);
  EXPECT_EQ(calc.GetError(), false);
}

TEST(Calc, Test_22) {
  std::string exp = "-5mod(2+2)";
  bool is_x_set = true;

  long double tol = 1e-15;

  my::CalcSolution calc(exp, false, 0.0);
  calc.Compute();

  EXPECT_TRUE(fabsl(calc.GetResult() - fmodl(-5.0, 4.0)) < tol);
  EXPECT_EQ(calc.GetError(), false);
}

TEST(Calc, Test_23) {
  std::string exp = "5mod(0)";
  bool is_x_set = true;

  my::CalcSolution calc(exp, false, 0.0);
  calc.Compute();

  EXPECT_TRUE(isnanl(calc.GetResult()));
  EXPECT_EQ(calc.GetError(), false);
}

TEST(Calc, Test_24) {
  std::string exp = "5mod(-2-2)";
  bool is_x_set = true;

  long double tol = 1e-15;

  my::CalcSolution calc(exp, false, 0.0);
  calc.Compute();

  EXPECT_TRUE(fabsl(calc.GetResult() - fmodl(5.0, -4.0)) < tol);
  EXPECT_EQ(calc.GetError(), false);
}

TEST(Calc, Test_25) {
  std::string exp = "0mod(0)";
  bool is_x_set = true;

  my::CalcSolution calc(exp, false, 0.0);
  calc.Compute();

  EXPECT_TRUE(isnanl(calc.GetResult()));
  EXPECT_EQ(calc.GetError(), false);
}

TEST(Calc, Test_26) {
  std::string exp = "4^0";
  bool is_x_set = true;

  long double tol = 1e-15;

  my::CalcSolution calc(exp, false, 0.0);
  calc.Compute();

  EXPECT_TRUE(fabsl(calc.GetResult() - powl(4, 0)) < tol);
  EXPECT_EQ(calc.GetError(), false);
}

TEST(Calc, Test_27) {
  std::string exp = "0^4";
  bool is_x_set = true;

  long double tol = 1e-15;

  my::CalcSolution calc(exp, false, 0.0);
  calc.Compute();

  EXPECT_TRUE(fabsl(calc.GetResult() - powl(0, 4)) < tol);
  EXPECT_EQ(calc.GetError(), false);
}

TEST(Calc, Test_28) {
  std::string exp = "0^0";
  bool is_x_set = true;

  long double tol = 1e-15;

  my::CalcSolution calc(exp, false, 0.0);
  calc.Compute();

  EXPECT_TRUE(fabsl(calc.GetResult() - powl(0, 0)) < tol);
  EXPECT_EQ(calc.GetError(), false);
}

TEST(Calc, Test_29) {
  std::string exp = "4+5";
  bool is_x_set = true;

  long double tol = 1e-15;

  my::CalcSolution calc(exp, false, 0.0);
  calc.Compute();

  EXPECT_TRUE(fabsl(calc.GetResult() - (4 + 5)) < tol);
  EXPECT_EQ(calc.GetError(), false);
}

TEST(Calc, Test_30) {
  std::string exp = "4-5";
  bool is_x_set = true;

  long double tol = 1e-15;

  my::CalcSolution calc(exp, false, 0.0);
  calc.Compute();

  EXPECT_TRUE(fabsl(calc.GetResult() - (4 - 5)) < tol);
  EXPECT_EQ(calc.GetError(), false);
}

TEST(Calc, Test_31) {
  std::string exp = "7*-7";
  bool is_x_set = true;

  long double tol = 1e-15;

  my::CalcSolution calc(exp, false, 0.0);
  calc.Compute();

  EXPECT_TRUE(fabsl(calc.GetResult() - (7 * -7)) < tol);
  EXPECT_EQ(calc.GetError(), false);
}

TEST(Calc, Test_32) {
  std::string exp = "2/3";
  bool is_x_set = true;

  long double tol = 1e-15;

  my::CalcSolution calc(exp, false, 0.0);
  calc.Compute();

  EXPECT_TRUE(fabsl(calc.GetResult() - (2 / 3.0)) < tol);
  EXPECT_EQ(calc.GetError(), false);
}

TEST(Calc, Test_33) {
  std::string exp = "2/0";
  bool is_x_set = true;

  my::CalcSolution calc(exp, false, 0.0);
  calc.Compute();

  EXPECT_EQ(calc.GetError(), true);
}

TEST(Calc, Test_34) {
  std::string exp = "-cos(sin(tan(4modx)))";
  bool is_x_set = true;
  long double x = 0.56;
  long double tol = 1e-15;

  my::CalcSolution calc(exp, true, x);
  calc.Compute();

  EXPECT_TRUE(fabsl(calc.GetResult() - (-cos(sin(tan(fmodl(4, x)))))) < tol);
  EXPECT_EQ(calc.GetError(), false);
}

TEST(Calc, Test_35) {
  std::string exp = "2*8-3*4+7*8-3^2";
  bool is_x_set = true;
  long double x = 0.56;
  long double tol = 1e-15;

  my::CalcSolution calc(exp, false, 0.0);
  calc.Compute();

  EXPECT_TRUE(
      fabsl(calc.GetResult() - (2 * 8 - 3 * 4 + 7 * 8 - powl(3, 2)) < tol));
  EXPECT_EQ(calc.GetError(), false);
}

TEST(Calc, Test_36) {
  std::string exp = "(3+4)*6";
  bool is_x_set = true;
  long double x = 0.56;
  long double tol = 1e-15;

  my::CalcSolution calc(exp, true, x);
  calc.Compute();

  EXPECT_TRUE(fabsl(calc.GetResult() - ((3 + 4) * 6)) < tol);
  EXPECT_EQ(calc.GetError(), false);
}

TEST(Calc, Test_37) {
  std::string exp = "6*(3+4)";
  bool is_x_set = true;
  long double x = 0.56;
  long double tol = 1e-15;

  my::CalcSolution calc(exp, false, 0.0);
  calc.Compute();

  EXPECT_TRUE(fabsl(calc.GetResult() - (6 * (3 + 4)) < tol));
  EXPECT_EQ(calc.GetError(), false);
}

TEST(Calc, Test_38) {
  std::string exp = "7*-(8-9)";
  bool is_x_set = true;
  long double x = 0.56;
  long double tol = 1e-15;

  my::CalcSolution calc(exp, true, x);
  calc.Compute();

  EXPECT_TRUE(fabsl(calc.GetResult() - (7 * -(8 - 9))) < tol);
  EXPECT_EQ(calc.GetError(), false);
}

TEST(Calc, Test_39) {
  std::string exp = "1.12334232+2.4525453";
  bool is_x_set = true;
  long double x = 0.56;
  long double tol = 1e-15;

  my::CalcSolution calc(exp, false, 0.0);
  calc.Compute();

  EXPECT_TRUE(fabsl(calc.GetResult() - (1.12334232 + 2.4525453) < tol));
  EXPECT_EQ(calc.GetError(), false);
}

TEST(Calc, Test_40) {
  std::string exp = "--(8+9)";
  bool is_x_set = true;
  long double x = 0.56;
  long double tol = 1e-15;

  my::CalcSolution calc(exp, false, 0.0);
  calc.Compute();

  EXPECT_TRUE(fabsl(calc.GetResult() - (17) < tol));
  EXPECT_EQ(calc.GetError(), false);
}

TEST(Calc, Test_41) {
  std::string exp = "-+(8+9)";
  bool is_x_set = true;
  long double x = 0.56;
  long double tol = 1e-15;

  my::CalcSolution calc(exp, false, 0.0);
  calc.Compute();

  EXPECT_TRUE(fabsl(calc.GetResult() - (-17) < tol));
  EXPECT_EQ(calc.GetError(), false);
}

TEST(Calc, Test_42) {
  std::string exp = "+-(8+9)";
  bool is_x_set = true;
  long double x = 0.56;
  long double tol = 1e-15;

  my::CalcSolution calc(exp, false, 0.0);
  calc.Compute();

  EXPECT_TRUE(fabsl(calc.GetResult() - (-17) < tol));
  EXPECT_EQ(calc.GetError(), false);
}

TEST(Calc, Test_43) {
  std::string exp = "++(8+9) ";
  bool is_x_set = true;
  long double x = 0.56;
  long double tol = 1e-15;

  my::CalcSolution calc(exp, false, 0.0);
  calc.Compute();

  EXPECT_TRUE(fabsl(calc.GetResult() - (17) < tol));
  EXPECT_EQ(calc.GetError(), false);
}

TEST(Calc, Test_44) {
  my::Model model;

  bool error = false;
  long double res = model.CalcSolve("2+2*x", "2", error);

  EXPECT_TRUE(fabs(res - 6) < 1e-10);
}