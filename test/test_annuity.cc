#include "test_header.h"

TEST(Annuity, Test_1) {
  long double amount = 200000.0;
  uint32_t months = 3;
  long double interest = 12.0;
  my::CreditType type = my::ANNUITY;

  my::CreditSolution credit(amount, interest, months, type);
  credit.Compute();

  long double expect_monthly_pay = 68004.42;
  long double expect_total = 204013.26;
  long double expect_overpay = 4013.26;

  long double tolerance = 1e-2;

  EXPECT_TRUE(fabs(credit.GetOverpayment() - expect_overpay) < tolerance);
  EXPECT_TRUE(fabs(credit.GetMonthlyPayment() - expect_monthly_pay) <
              tolerance);
  EXPECT_TRUE(fabs(credit.GetTotalPayment() - expect_total) < tolerance);

  EXPECT_THROW(credit.GetFirstPayment(), std::runtime_error);
  EXPECT_THROW(credit.GetLastPayment(), std::runtime_error);
}

TEST(Annuity, Test_2) {
  long double amount = 300000000;
  uint32_t months = 12;
  long double interest = 20.0;
  my::CreditType type = my::ANNUITY;

  my::CreditSolution credit(amount, interest, months, type);
  credit.Compute();

  long double expect_monthly_pay = 27790351.77;
  long double expect_total = 333484221.24;
  long double expect_overpay = 33484221.24;

  long double tolerance = 1e-1;

  EXPECT_TRUE(fabs(credit.GetOverpayment() - expect_overpay) < tolerance);
  EXPECT_TRUE(fabs(credit.GetMonthlyPayment() - expect_monthly_pay) <
              tolerance);
  EXPECT_TRUE(fabs(credit.GetTotalPayment() - expect_total) < tolerance);

  EXPECT_THROW(credit.GetFirstPayment(), std::runtime_error);
  EXPECT_THROW(credit.GetLastPayment(), std::runtime_error);
}

TEST(Annuity, Test_3) {
  long double amount = 23;
  uint32_t months = 1;
  long double interest = 0.1;
  my::CreditType type = my::ANNUITY;

  my::CreditSolution credit(amount, interest, months, type);
  credit.Compute();

  long double expect_monthly_pay = 23;
  long double expect_total = 23;
  long double expect_overpay = 0;

  long double tolerance = 1e-2;

  EXPECT_TRUE(fabs(credit.GetOverpayment() - expect_overpay) < tolerance);
  EXPECT_TRUE(fabs(credit.GetMonthlyPayment() - expect_monthly_pay) <
              tolerance);
  EXPECT_TRUE(fabs(credit.GetTotalPayment() - expect_total) < tolerance);

  EXPECT_THROW(credit.GetFirstPayment(), std::runtime_error);
  EXPECT_THROW(credit.GetLastPayment(), std::runtime_error);
}

TEST(Annuity, Test_4) {
  long double amount = -1;
  uint32_t months = 12;
  long double interest = 20;
  my::CreditType type = my::ANNUITY;

  my::CreditSolution credit(amount, interest, months, type);
  EXPECT_THROW(credit.Compute(), std::runtime_error);
}

TEST(Annuity, Test_5) {
  long double amount = 0;
  uint32_t months = 12;
  long double interest = 20;
  my::CreditType type = my::ANNUITY;

  my::CreditSolution credit(amount, interest, months, type);
  EXPECT_THROW(credit.Compute(), std::runtime_error);
}

TEST(Annuity, Test_6) {
  long double amount = 23;
  uint32_t months = -12;
  long double interest = 20;
  my::CreditType type = my::ANNUITY;

  my::CreditSolution credit(amount, interest, months, type);
  EXPECT_THROW(credit.Compute(), std::runtime_error);
}

TEST(Annuity, Test_7) {
  long double amount = 300;
  uint32_t months = 12;
  long double interest = 0;
  my::CreditType type = my::ANNUITY;

  my::CreditSolution credit(amount, interest, months, type);
  EXPECT_THROW(credit.Compute(), std::runtime_error);
}

TEST(Annuity, Test_8) {
  long double amount = 300;
  uint32_t months = 1;
  long double interest = -10;
  my::CreditType type = my::ANNUITY;

  my::CreditSolution credit(amount, interest, months, type);
  EXPECT_THROW(credit.Compute(), std::runtime_error);
}

TEST(Annuity, Test_9) {
  my::Model model;
  my::credit_context cont;
  cont.amount = "200000";
  cont.months = "3";
  cont.type = "Annuity";
  cont.interest = "12";

  long double expect_monthly_pay = 68004.42;
  long double expect_total = 204013.26;
  long double expect_overpay = 4013.26;

  model.CreditSolve(cont);

  long double tolerance = 1e-2;

  EXPECT_TRUE(fabs(cont.overpayment - expect_overpay) < tolerance);
  EXPECT_TRUE(fabs(cont.monthly_payment - expect_monthly_pay) < tolerance);
  EXPECT_TRUE(fabs(cont.total_payment - expect_total) < tolerance);
}