#include "test_header.h"

TEST(Deposit, Test_1) {
  long double amount = 200000;
  bool capital = true;
  my::DepositFreq freq = my::YEARLY;
  long double interest = 5;
  long double months = 12;
  long double tax = 0;
  long double replenish = 0;
  long double withdraw = 0;

  long double tolerance = 1e-0;
  long double expect_interest = 10000.82;
  long double expect_tax = 0.00;
  long double expect_revenue = 210000.82;

  my::DepositSolution deposit(amount, interest, tax, months, freq, replenish,
                               withdraw, capital);

  deposit.Compute();

  EXPECT_TRUE(fabs(deposit.GetResTax() - expect_tax) <= tolerance);
  EXPECT_TRUE(fabs(deposit.GetResRevenue() - expect_revenue) <= tolerance);
  EXPECT_TRUE(fabs(deposit.GetResInterest() - expect_interest) <= tolerance);
}

TEST(Deposit, Test_2) {
  long double amount = 200000;
  bool capital = false;
  my::DepositFreq freq = my::MONTHLY;
  long double interest = 13;
  long double months = 15;
  long double tax = 13;
  long double replenish = 200000;
  long double withdraw = 10000;

  long double tolerance = 1e-0;
  long double expect_interest = 248625;
  long double expect_tax = 32321.20;
  long double expect_revenue = 416304.00;

  my::DepositSolution deposit(amount, interest, tax, months, freq, replenish,
                               withdraw, capital);

  deposit.Compute();

  EXPECT_TRUE(fabs(deposit.GetResTax() - expect_tax) <= tolerance);
  EXPECT_TRUE(fabs(deposit.GetResRevenue() - expect_revenue) <= tolerance);
  EXPECT_TRUE(fabs(deposit.GetResInterest() - expect_interest) <= tolerance);
}

TEST(Deposit, Test_3) {
  long double amount = 0;
  bool capital = true;
  my::DepositFreq freq = my::YEARLY;
  long double interest = 5;
  long double months = 12;
  long double tax = 0;
  long double replenish = 0;
  long double withdraw = 0;

  my::DepositSolution deposit(amount, interest, tax, months, freq, replenish,
                               withdraw, capital);

  EXPECT_THROW(deposit.Compute(), std::runtime_error);
}

TEST(Deposit, Test_4) {
  long double amount = 142253;
  bool capital = true;
  my::DepositFreq freq = my::YEARLY;
  long double interest = 5;
  long double months = 0;
  long double tax = 0;
  long double replenish = 0;
  long double withdraw = 0;

  my::DepositSolution deposit(amount, interest, tax, months, freq, replenish,
                               withdraw, capital);

  EXPECT_THROW(deposit.Compute(), std::runtime_error);
}

TEST(Deposit, Test_5) {
  long double amount = 242112;
  bool capital = true;
  my::DepositFreq freq = my::YEARLY;
  long double interest = 5;
  long double months = 12;
  long double tax = 0;
  long double replenish = -2330;
  long double withdraw = -87280;

  my::DepositSolution deposit(amount, interest, tax, months, freq, replenish,
                               withdraw, capital);

  EXPECT_THROW(deposit.Compute(), std::runtime_error);
}

TEST(Deposit, Test_6) {
  long double amount = 242112;
  bool capital = true;
  my::DepositFreq freq = my::YEARLY;
  long double interest = 5;
  long double months = 12;
  long double tax = -10;
  long double replenish = 2330;
  long double withdraw = 87280;

  my::DepositSolution deposit(amount, interest, tax, months, freq, replenish,
                               withdraw, capital);

  EXPECT_THROW(deposit.Compute(), std::runtime_error);
}

TEST(Deposit, Test_7) {
  long double amount = 242112;
  bool capital = true;
  my::DepositFreq freq = my::YEARLY;
  long double interest = 0;
  long double months = 12;
  long double tax = 10;
  long double replenish = 2330;
  long double withdraw = 87280;

  my::DepositSolution deposit(amount, interest, tax, months, freq, replenish,
                               withdraw, capital);

  EXPECT_THROW(deposit.Compute(), std::runtime_error);
}

TEST(Deposit, Test_8) {
  long double amount = 242112;
  bool capital = true;
  my::DepositFreq freq = my::YEARLY;
  long double interest = -10;
  long double months = 12;
  long double tax = 10;
  long double replenish = 2330;
  long double withdraw = 87280;

  my::DepositSolution deposit(amount, interest, tax, months, freq, replenish,
                               withdraw, capital);

  EXPECT_THROW(deposit.Compute(), std::runtime_error);
}

TEST(Deposit, Test_9) {
  my::Model model;
  my::deposit_context cont;
  cont.amount = "200000";
  cont.capital = true;
  cont.freq = "Once a year";
  cont.interest = "5";
  cont.tax = "0";
  cont.replenish = "0";
  cont.withdrawal = "0";
  cont.term = "12";
  cont.term_type = "Month(s)";

  long double tolerance = 1e-0;
  long double expect_interest = 10000.82;
  long double expect_tax = 0.00;
  long double expect_revenue = 210000.82;

  model.DepositSolve(cont);

  EXPECT_TRUE(fabs(cont.res_tax - expect_tax) <= tolerance);
  EXPECT_TRUE(fabs(cont.res_revenue - expect_revenue) <= tolerance);
  EXPECT_TRUE(fabs(cont.res_interest - expect_interest) <= tolerance);
}