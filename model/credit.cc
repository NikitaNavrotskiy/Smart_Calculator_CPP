#include "credit.h"

namespace my {

CreditSolution::CreditSolution()
    : amount(0), interest(0), months(0), type(ANNUITY) {}

CreditSolution::CreditSolution(ld amount, ld interest, ld months,
                               CreditType type)
    : amount(amount), interest(interest), months(months), type(type) {}

void CreditSolution::SetInput(credit_context& context) {
  this->amount = GetDoubleFromString(context.amount, context.error);
  this->interest = GetDoubleFromString(context.interest, context.error);
  this->months = GetDoubleFromString(context.months, context.error);
  if (context.type == "Annuity")
    this->type = ANNUITY;
  else
    this->type = DIFF;
  if (context.term_type == "Year(s)") this->months *= 12;
  this->first_payment = 0;
  this->last_payment = 0;
  this->monthly_payment = 0;
  this->overpayment = 0;
  this->total_payment = 0;
}

bool CreditSolution::validate() {
  bool res = true;

  if (amount > CREDIT_AMOUNT_MAX || amount <= CREDIT_AMOUNT_MIN) res = false;
  if (interest >= CREDIT_INTERSET_MAX || interest <= CREDIT_INTERSET_MIN)
    res = false;
  if (months >= CREDIT_MONTHS_MAX || months < CREDIT_MONTHS_MIN) res = false;
  return res;
}

void CreditSolution::Compute() {
  if (!validate()) throw std::runtime_error("SmartCreditError: Invalid data");
  if (type == ANNUITY) {
    AnnuityMonthlyPayment();
    AnnuityTotalPayment();
    AnnuityOverpayment();
  } else if (type == DIFF) {
    first_payment = DiffNmonthPayment(1);
    last_payment = DiffNmonthPayment(months);
    DiffTotalPayment();
    DiffOverpayment();
  }
}

void CreditSolution::AnnuityMonthlyPayment() {
  ld interest_by_month = interest / 12 / 100;

  monthly_payment =
      amount * (interest_by_month +
                interest_by_month / (powl(1 + interest_by_month, months) - 1));
}

void CreditSolution::AnnuityOverpayment() {
  overpayment = total_payment - amount;
}

void CreditSolution::AnnuityTotalPayment() {
  total_payment = monthly_payment * months;
}

long double CreditSolution::DiffNmonthPayment(i32 n) {
  ld remain = amount - (amount / months) * (n - 1);

  return amount / months + remain * interest / 12 / 100;
}

void CreditSolution::DiffOverpayment() { overpayment = total_payment - amount; }

void CreditSolution::DiffTotalPayment() {
  long double interest_by_month = interest / 12 / 100;
  long double main_part = amount / months;
  long double payment = 0.0;

  for (int i = 1; i <= static_cast<i32>(months); i++) {
    long double left = amount - (main_part * (i - 1));
    long double interest_payment = left * interest_by_month;
    long double _monthly_payment = main_part + interest_payment;
    payment += _monthly_payment;
  }

  total_payment = payment;
}

}  // namespace my
