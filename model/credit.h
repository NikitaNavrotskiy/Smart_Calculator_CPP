#ifndef _MODEL_CREDIT_H
#define _MODEL_CREDIT_H

#include <cmath>
#include <cstdint>
#include <iostream>

#include "interface.h"

#define CREDIT_AMOUNT_MIN 0
#define CREDIT_AMOUNT_MAX 1e+10

#define CREDIT_MONTHS_MIN 0
#define CREDIT_MONTHS_MAX 30 * 12

#define CREDIT_INTERSET_MIN 0
#define CREDIT_INTERSET_MAX 100

namespace my {

enum CreditType : bool { ANNUITY, DIFF };

struct credit_context {
  std::string amount;
  std::string interest;
  std::string months;
  std::string type;
  std::string term_type;
  long double first_payment;
  long double last_payment;
  long double monthly_payment;
  long double total_payment;
  long double overpayment;
  bool error = false;
};

class CreditSolution final : public Solution {
 public:
  using ld = long double;
  using i32 = int32_t;

  CreditSolution();
  CreditSolution(ld amount, ld interest, ld months, CreditType type);
  ~CreditSolution() = default;

  void SetInput(credit_context& context);

  void Compute() override;

  long double GetOverpayment() const;
  long double GetTotalPayment() const;
  long double GetMonthlyPayment() const;

  long double GetFirstPayment() const;
  long double GetLastPayment() const;

 private:
  void AnnuityMonthlyPayment();
  void AnnuityOverpayment();
  void AnnuityTotalPayment();

  long double DiffNmonthPayment(i32 n);
  void DiffOverpayment();
  void DiffTotalPayment();

  bool validate() override;

 private:
  ld amount;
  ld interest;
  i32 months;
  CreditType type;
  ld first_payment = 0;
  ld last_payment = 0;
  ld monthly_payment = 0;
  ld total_payment = 0;
  ld overpayment = 0;
};

inline long double CreditSolution::GetOverpayment() const {
  return overpayment;
}

inline long double CreditSolution::GetTotalPayment() const {
  return total_payment;
}

inline long double CreditSolution::GetMonthlyPayment() const {
  if (type == DIFF)
    throw std::runtime_error(
        "SmartCreditError: Differential has first and last \
                                                payments instead of monthly");
  return monthly_payment;
}

inline long double CreditSolution::GetFirstPayment() const {
  if (type == ANNUITY)
    throw std::runtime_error(
        "SmartCreditError: Annuity has monthly \
                                                payments instead of first and last");
  return first_payment;
}

inline long double CreditSolution::GetLastPayment() const {
  if (type == ANNUITY)
    throw std::runtime_error(
        "SmartCreditError: Annuity has monthly \
                                                payments instead of first and last");
  return last_payment;
}

}  // namespace my

#endif