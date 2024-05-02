#ifndef _MODEL_DEPOSIT_H
#define _MODEL_DEPOSIT_H

#include <cstdint>
#include <iostream>

#include "interface.h"

#define DEPOSIT_AMOUNT_MIN 0
#define DEPOSIT_AMOUNT_MAX 1e+10

#define DEPOSIT_MONTHS_MIN 0
#define DEPOSIT_MONTHS_MAX 5 * 12

#define DEPOSIT_INTERSET_MIN 0
#define DEPOSIT_INTERSET_MAX 100

#define DEPOSIT_TAX_MIN 0
#define DEPOSIT_TAX_MAX 100

#define DEPOSIT_REPLENISHMENT_MIN DEPOSIT_AMOUNT_MIN
#define DEPOSIT_REPLENISHMENT_MAX DEPOSIT_AMOUNT_MAX

#define DEPOSIT_WITHDRAW_MIN DEPOSIT_AMOUNT_MIN
#define DEPOSIT_WITHDRAW_MAX DEPOSIT_AMOUNT_MAX

namespace my {

enum DepositFreq { YEARLY = 1, MONTHLY = 12 };

struct deposit_context {
  std::string amount;
  std::string interest;
  std::string term;
  std::string tax;
  std::string freq;
  std::string replenish;
  std::string withdrawal;
  std::string term_type;
  bool capital;
  long double res_interest;
  long double res_tax;
  long double res_revenue;
  bool error = false;
};

class DepositSolution : public Solution {
 public:
  using ld = long double;
  using i32 = int32_t;

  DepositSolution();
  DepositSolution(ld amount, ld interest, ld tax, ld term, DepositFreq freq,
                  ld replen, ld withdraw, bool capital);
  ~DepositSolution() = default;

  void SetInput(deposit_context& context);

  void Compute() override;

  long double GetResInterest() const;
  long double GetResRevenue() const;
  long double GetResTax() const;

 private:
  void TaxAmount();
  void ProfitAmount();
  void RevenueAmount();

  bool validate() override;

 private:
  ld amount;
  ld interest;
  ld tax;
  i32 term;
  DepositFreq freq;
  ld replenish;
  ld withdraw;
  ld res_interest;
  ld res_tax;
  ld res_revenue;
  bool capital;
};

inline long double DepositSolution::GetResInterest() const {
  return res_interest;
}

inline long double DepositSolution::GetResRevenue() const {
  return res_revenue;
}

inline long double DepositSolution::GetResTax() const { return res_tax; }

}  // namespace my

#endif