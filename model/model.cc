#include "model.h"

namespace my {

long double Model::CalcSolve(const std::string& expression,
                             const std::string& x_val, bool& error) {
  calc_mod.SetInput(expression, x_val);
  calc_mod.Compute();

  error = calc_mod.GetError();
  return calc_mod.GetResult();
}

void Model::CreditSolve(credit_context& context) {
  cred_mod.SetInput(context);

  cred_mod.Compute();

  context.overpayment = cred_mod.GetOverpayment();
  if (context.type == "Annuity")
    context.monthly_payment = cred_mod.GetMonthlyPayment();
  else {
    context.first_payment = cred_mod.GetFirstPayment();
    context.last_payment = cred_mod.GetLastPayment();
  }
  context.total_payment = cred_mod.GetTotalPayment();
}

void Model::DepositSolve(deposit_context& context) {
  dep_mod.SetInput(context);

  dep_mod.Compute();

  context.res_interest = dep_mod.GetResInterest();
  context.res_tax = dep_mod.GetResTax();
  context.res_revenue = dep_mod.GetResRevenue();
}

}  // namespace my