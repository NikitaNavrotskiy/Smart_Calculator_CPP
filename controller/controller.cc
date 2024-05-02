#include "controller.h"

namespace my {

long double Controller::CalcSolve(const std::string& expression,
                                  const std::string& x_val, bool& error) {
  return model.CalcSolve(expression, x_val, error);
}

void Controller::CreditSolve(credit_context& context) {
  model.CreditSolve(context);
}

void Controller::DepositSolve(deposit_context& context) {
  model.DepositSolve(context);
}

}  // namespace my