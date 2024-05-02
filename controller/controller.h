#ifndef _CONTEXT_CONTEXT_H
#define _CONTEXT_CONTEXT_H

#include "../model/model.h"

namespace my {

class Controller {
 public:
  long double CalcSolve(const std::string& expression, const std::string& x_val,
                        bool& error);

  void CreditSolve(credit_context& context);

  void DepositSolve(deposit_context& context);

 private:
  Model model;
};

}  // namespace my

#endif