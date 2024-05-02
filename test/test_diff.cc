#include "test_header.h"

TEST(Diff, Test_1) {
  long double amount = 200000.0;
  uint32_t months = 3;
  long double interest = 12.0;
  my::CreditType type = my::DIFF;

  my::CreditSolution credit(amount, interest, months, type);
  credit.Compute();

  long double expect_first_pay = 68666.67;
  long double expect_last_pay = 67333.33;
  long double expect_total = 204000.00;
  long double expect_overpay = 4000.00;

  long double tolerance = 1e-2;

  EXPECT_TRUE(fabs(credit.GetOverpayment() - expect_overpay) < tolerance);
  EXPECT_TRUE(fabs(credit.GetFirstPayment() - expect_first_pay) < tolerance);
  EXPECT_TRUE(fabs(credit.GetLastPayment() - expect_last_pay) < tolerance);
  EXPECT_TRUE(fabs(credit.GetTotalPayment() - expect_total) < tolerance);
}

TEST(Diff, Test_2) {
  long double amount = 300000000;
  uint32_t months = 12;
  long double interest = 20;
  my::CreditType type = my::DIFF;

  my::CreditSolution credit(amount, interest, months, type);
  credit.Compute();

  long double expect_first_pay = 30000000;
  long double expect_last_pay = 25416666.67;
  long double expect_total = 332500000.00;
  long double expect_overpay = 32500000.00;

  long double tolerance = 1e-1;

  EXPECT_TRUE(fabs(credit.GetOverpayment() - expect_overpay) < tolerance);
  EXPECT_TRUE(fabs(credit.GetFirstPayment() - expect_first_pay) < tolerance);
  EXPECT_TRUE(fabs(credit.GetLastPayment() - expect_last_pay) < tolerance);
  EXPECT_TRUE(fabs(credit.GetTotalPayment() - expect_total) < tolerance);
}

TEST(Diff, Test_3) {
  long double amount = 23;
  uint32_t months = 3;
  long double interest = 0.1;
  my::CreditType type = my::DIFF;

  my::CreditSolution credit(amount, interest, months, type);
  credit.Compute();

  long double expect_first_pay = 7.67;
  long double expect_last_pay = 7.67;
  long double expect_total = 23.00;
  long double expect_overpay = 0.00;

  long double tolerance = 1e-2;

  EXPECT_TRUE(fabs(credit.GetOverpayment() - expect_overpay) < tolerance);
  EXPECT_TRUE(fabs(credit.GetFirstPayment() - expect_first_pay) < tolerance);
  EXPECT_TRUE(fabs(credit.GetLastPayment() - expect_last_pay) < tolerance);
  EXPECT_TRUE(fabs(credit.GetTotalPayment() - expect_total) < tolerance);

  EXPECT_THROW(credit.GetMonthlyPayment(), std::runtime_error);
}

TEST(Diff, Test_4) {
  long double amount = -1;
  uint32_t months = 12;
  long double interest = 20;
  my::CreditType type = my::DIFF;

  my::CreditSolution credit(amount, interest, months, type);
  EXPECT_THROW(credit.Compute(), std::runtime_error);
}

TEST(Diff, Test_5) {
  long double amount = 0;
  uint32_t months = 12;
  long double interest = 20;
  my::CreditType type = my::DIFF;

  my::CreditSolution credit(amount, interest, months, type);
  EXPECT_THROW(credit.Compute(), std::runtime_error);
}

TEST(Diff, Test_6) {
  long double amount = 300;
  uint32_t months = -12;
  long double interest = 20;
  my::CreditType type = my::DIFF;

  my::CreditSolution credit(amount, interest, months, type);
  EXPECT_THROW(credit.Compute(), std::runtime_error);
}

TEST(Diff, Test_7) {
  long double amount = 300;
  uint32_t months = 12;
  long double interest = 0;
  my::CreditType type = my::DIFF;

  my::CreditSolution credit(amount, interest, months, type);
  EXPECT_THROW(credit.Compute(), std::runtime_error);
}

TEST(Diff, Test_8) {
  long double amount = 300;
  uint32_t months = 12;
  long double interest = -12;
  my::CreditType type = my::DIFF;

  my::CreditSolution credit(amount, interest, months, type);
  EXPECT_THROW(credit.Compute(), std::runtime_error);
}