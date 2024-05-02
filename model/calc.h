#ifndef _MODEL_CALC_H
#define _MODEL_CALC_H

#include <cmath>
#include <list>
#include <regex>
#include <stack>
#include <string>

#include "interface.h"

namespace my {

enum token {
  NUM,
  OPEN_BRACE,
  X,
  ADD,
  SUB,
  MUL,
  DIV,
  POW,
  MOD,
  SIN,
  COS,
  TAN,
  ASIN,
  ACOS,
  ATAN,
  SQRT,
  LN,
  LOG10,
  NOTHING
};

class CalcSolution final : public Solution {
 public:
  CalcSolution();
  CalcSolution(const std::string& infix, bool is_x_set, long double x_val);
  ~CalcSolution() = default;

  void SetDoubleXFromString(const std::string& x);
  void SetInput(const std::string& expression, const std::string& x_val);

  void Compute() override;
  bool validate() override;

  long double GetResult() const;
  bool GetError() const;

 private:
  struct lexem {
   public:
    lexem() : tok(NOTHING), value(0) {}
    lexem(token, long double);

    token tok;
    long double value;
  };

 private:
  void FromInfixToPosfix();

  bool StartWithDouble();
  bool StartWithFunc(lexem& lex);
  bool StartWithSmallOperation(lexem& lex);
  long double GetDoubleFromString();
  int GetPriority(token tok);

  void FromInfixToPosfixUnarMinus(std::stack<token>& st);
  void FromInfixToPosfixX();
  void FromInfixToPosfixOpenBrace();
  void FromInfixToPosfixCloseBrace(std::stack<token>& st);
  void FromInfixToPosfixSmallOper(lexem& lex, std::stack<token>& st);
  void FromInfixToPosfixFinish(std::stack<token>& st);

  void FromPosfixToAnswer();
  long double FromPosfixToAnswerSmallOper(std::stack<lexem>& st, token tok);
  long double FromPosfixToAnswerFunc(std::stack<lexem>& st, token tok);

 private:
  std::string infix_expresion;
  std::list<lexem> posfix_expresion;
  long double result = 0;
  long double x_val;
  bool is_x_set = false;
  bool error = false;
  bool unar = true;
  int count_braces = 0;
  bool prev_close_brace = false;
};

inline long double CalcSolution::GetResult() const { return result; }

inline bool CalcSolution::GetError() const { return error; }

}  // namespace my

#endif