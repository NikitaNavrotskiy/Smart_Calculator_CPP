#ifndef _MODEL_MODEL_H
#define _MODEL_MODEL_H

#include "calc.h"
#include "credit.h"
#include "deposit.h"

namespace my {

class Model {
 public:
  long double CalcSolve(const std::string& expression, const std::string& x_val,
                        bool& error);

  void CreditSolve(credit_context& context);

  void DepositSolve(deposit_context& context);

 private:
  CalcSolution calc_mod;
  CreditSolution cred_mod;
  DepositSolution dep_mod;
};

}  // namespace my

#endif