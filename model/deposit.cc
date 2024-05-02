#include "deposit.h"

namespace my {

DepositSolution::DepositSolution()
    : amount(0),
      interest(0),
      tax(0),
      term(0),
      freq(YEARLY),
      replenish(0),
      withdraw(0),
      capital(false) {}

DepositSolution::DepositSolution(ld amount, ld interest, ld tax, ld term,
                                 DepositFreq freq, ld replen, ld withdraw,
                                 bool capital)
    : amount(amount),
      interest(interest),
      tax(tax),
      term(term),
      freq(freq),
      replenish(replen),
      withdraw(withdraw),
      capital(capital) {}

void DepositSolution::SetInput(deposit_context& context) {
  this->amount = GetDoubleFromString(context.amount, context.error);
  this->interest = GetDoubleFromString(context.interest, context.error);
  this->term = GetDoubleFromString(context.term, context.error);
  this->tax = GetDoubleFromString(context.tax, context.error);
  if (context.freq == "Once a month")
    this->freq = MONTHLY;
  else
    this->freq = YEARLY;
  if (context.term_type == "Year(s)") this->term *= 12;
  this->replenish = GetDoubleFromString(context.replenish, context.error);
  this->withdraw = GetDoubleFromString(context.withdrawal, context.error);
  this->capital = context.capital;
  this->res_interest = 0;
  this->res_revenue = 0;
  this->res_tax = 0;
}

bool DepositSolution::validate() {
  bool res = true;

  if (amount > DEPOSIT_AMOUNT_MAX || amount <= DEPOSIT_AMOUNT_MIN) res = false;
  if (interest >= DEPOSIT_INTERSET_MAX || interest <= DEPOSIT_INTERSET_MIN)
    res = false;
  if (tax >= DEPOSIT_TAX_MAX || tax < DEPOSIT_TAX_MIN) res = false;
  if (term > DEPOSIT_MONTHS_MAX || term <= DEPOSIT_MONTHS_MIN) res = false;
  if (replenish > DEPOSIT_REPLENISHMENT_MAX ||
      replenish < DEPOSIT_REPLENISHMENT_MIN)
    res = false;
  if (withdraw > DEPOSIT_WITHDRAW_MAX || withdraw < DEPOSIT_WITHDRAW_MIN)
    res = false;

  return res;
}

void DepositSolution::Compute() {
  if (!validate()) throw std::runtime_error("SmartDepositError: Invalid data");

  ProfitAmount();
  TaxAmount();
  RevenueAmount();
}

void DepositSolution::TaxAmount() { res_tax = res_interest * tax / 100; }

void DepositSolution::RevenueAmount() {
  res_revenue = res_interest + amount - res_tax;
}

void DepositSolution::ProfitAmount() {
  long double profit = 0.0;
  long double amount_copy = amount;

  if (term >= freq) {
    for (int i = 1; i <= term; i++) {
      long double local_profit = 0.0;
      if (freq == MONTHLY)
        local_profit += amount_copy * (interest / 12 / 100);
      else if (freq == YEARLY && i % 12 == 0)
        local_profit += amount_copy * (interest / 100);
      amount_copy += (replenish - withdraw);

      if (capital) amount_copy += local_profit;
      profit += local_profit;
    }
  }

  res_interest = profit;
}

}  // namespace my