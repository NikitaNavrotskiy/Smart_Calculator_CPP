#include "calc.h"

namespace my {

CalcSolution::lexem::lexem(token tok, long double value)
    : tok(tok), value(value) {}

CalcSolution::CalcSolution()
    : infix_expresion(""), x_val(0.0), is_x_set(true) {}

CalcSolution::CalcSolution(const std::string& infix, bool is_x_set,
                           long double x_val)
    : infix_expresion(infix), x_val(x_val), is_x_set(is_x_set) {}

void CalcSolution::SetInput(const std::string& expression,
                            const std::string& x_val) {
  infix_expresion = expression;
  ChangeToDots(infix_expresion);
  ChangeToDots(const_cast<std::string&>(x_val));
  error = false;
  if (x_val == "")
    is_x_set = false;
  else
    SetDoubleXFromString(x_val);
  posfix_expresion.clear();
  count_braces = 0;
  unar = true;
  result = 0;
}

void CalcSolution::SetDoubleXFromString(const std::string& x) {
  if (!ValidateDouble(x))
    error = true;
  else {
    x_val = std::strtold(x.c_str(), nullptr);
    is_x_set = true;
  }
}

void CalcSolution::Compute() {
  validate();
  FromInfixToPosfix();
  FromPosfixToAnswer();
}

bool CalcSolution::validate() {
  for (size_t i = 1; i < infix_expresion.size();) {
    if (infix_expresion[i - 1] == '.') infix_expresion[i - 1] = ',';
    if (infix_expresion[i - 1] == '+') {
      if (infix_expresion[i] == '+')
        infix_expresion.erase(i, 1);
      else if (infix_expresion[i] == '-')
        infix_expresion.erase(i - 1, 1);
      else
        i++;
    } else if (infix_expresion[i - 1] == '-') {
      if (infix_expresion[i] == '+')
        infix_expresion.erase(i, 1);
      else if (infix_expresion[i] == '-') {
        infix_expresion[i - 1] = '+';
        infix_expresion.erase(i, 1);
      } else
        i++;
    } else
      i++;
  }
  if (infix_expresion[infix_expresion.size() - 1] == '.')
    infix_expresion[infix_expresion.size() - 1] = ',';
  while (infix_expresion[0] == '+') infix_expresion.erase(0, 1);
  if (infix_expresion[infix_expresion.size() - 1] == '-') error = true;
  return error;
}

void CalcSolution::FromInfixToPosfix() {
  std::stack<token> st;
  lexem tmp;
  bool end = false;

  while (!error && !end && infix_expresion.length() != 0) {
    if (infix_expresion[0] == '-' && infix_expresion.size() > 1 &&
        infix_expresion[1] == '(')
      FromInfixToPosfixUnarMinus(st);
    else if (infix_expresion[0] == 'x')
      FromInfixToPosfixX();
    else if (StartWithDouble())
      posfix_expresion.push_back(lexem(NUM, GetDoubleFromString()));
    else if (StartWithFunc(tmp)) {
      st.push(tmp.tok);
      if (tmp.tok == MOD) unar = true;
    } else if (infix_expresion[0] == '(') {
      st.push(OPEN_BRACE);
      FromInfixToPosfixOpenBrace();
    } else if (infix_expresion[0] == ')') {
      if (count_braces == 0)
        error = true;
      else
        FromInfixToPosfixCloseBrace(st);
    } else if (StartWithSmallOperation(tmp)) {
      FromInfixToPosfixSmallOper(tmp, st);
      unar = true;
    } else
      end = true;
  }
  if (count_braces != 0) error = true;
  if (!error) FromInfixToPosfixFinish(st);
}

bool CalcSolution::StartWithDouble() {
  bool res = false;

  if (isdigit(infix_expresion[0]) ||
      (infix_expresion.size() > 1 &&
       (infix_expresion[0] == '-' || infix_expresion[0] == '+') && unar &&
       isdigit(infix_expresion[1])))
    res = true;
  return res;
}

bool CalcSolution::StartWithFunc(lexem& lex) {
  lex.tok = NOTHING;
  size_t len = infix_expresion.length();
  if (len > 4 && !infix_expresion.compare(0, 5, "log10")) {
    lex.tok = LOG10;
    infix_expresion = infix_expresion.substr(5);
  }
  if (lex.tok == NOTHING && len > 3) {
    if (!infix_expresion.compare(0, 4, "acos"))
      lex.tok = ACOS;
    else if (!infix_expresion.compare(0, 4, "asin"))
      lex.tok = ASIN;
    else if (!infix_expresion.compare(0, 4, "atan"))
      lex.tok = ATAN;
    else if (!infix_expresion.compare(0, 4, "sqrt"))
      lex.tok = SQRT;
    if (lex.tok != NOTHING) infix_expresion = infix_expresion.substr(4);
  }
  if (lex.tok == NOTHING && len > 2) {
    if (!infix_expresion.compare(0, 3, "cos"))
      lex.tok = COS;
    else if (!infix_expresion.compare(0, 3, "sin"))
      lex.tok = SIN;
    else if (!infix_expresion.compare(0, 3, "tan"))
      lex.tok = TAN;
    else if (!infix_expresion.compare(0, 3, "mod"))
      lex.tok = MOD;
    if (lex.tok != NOTHING) infix_expresion = infix_expresion.substr(3);
  }
  if (lex.tok == NOTHING && len > 1 && !infix_expresion.compare(0, 2, "ln")) {
    lex.tok = LN;
    infix_expresion = infix_expresion.substr(2);
  }

  return lex.tok != NOTHING;
}

void CalcSolution::FromInfixToPosfixUnarMinus(std::stack<token>& st) {
  if (prev_close_brace) st.push(ADD);
  posfix_expresion.push_back(lexem(NUM, -1.0));
  st.push(MUL);
  infix_expresion = infix_expresion.substr(1);
  prev_close_brace = false;
}

void CalcSolution::FromInfixToPosfixX() {
  posfix_expresion.push_back(lexem(X, 0.0));
  infix_expresion = infix_expresion.substr(1);
  unar = false;
  prev_close_brace = false;
}

void CalcSolution::FromInfixToPosfixOpenBrace() {
  count_braces++;
  infix_expresion = infix_expresion.substr(1);
  unar = true;
  prev_close_brace = false;
}

void CalcSolution::FromInfixToPosfixSmallOper(lexem& lex,
                                              std::stack<token>& st) {
  bool stop = false;
  token tok1 = lex.tok;
  token tok2;
  infix_expresion = infix_expresion.substr(1);
  prev_close_brace = false;

  while (!stop && !error) {
    if (!st.empty()) {
      tok2 = st.top();
      int prior1 = GetPriority(tok1);
      int prior2 = GetPriority(tok2);

      if (prior2 != 0 && prior2 >= prior1 && tok2 >= ADD && tok2 <= POW) {
        posfix_expresion.push_back(lexem(tok2, 0.0));
        st.pop();
      } else
        stop = true;
    } else
      stop = true;
  }

  st.push(tok1);
}

void CalcSolution::FromInfixToPosfixCloseBrace(std::stack<token>& st) {
  count_braces--;
  unar = false;
  infix_expresion = infix_expresion.substr(1);
  prev_close_brace = true;

  token tmp;
  bool loc_res = false, was_open_brace = false;

  while (!loc_res) {
    if (st.size() == 0) {
      loc_res = true;
      error = true;
    } else {
      tmp = st.top();
      if (tmp == OPEN_BRACE) {
        was_open_brace = true;
        loc_res = true;
      } else {
        posfix_expresion.push_back(lexem(tmp, 0.0));
        st.pop();
      }
    }
  }

  if (was_open_brace == false)
    error = true;
  else {
    if (tmp == OPEN_BRACE && st.size() != 0) {
      st.pop();
      if (!st.empty()) {
        tmp = st.top();
        if (tmp >= MOD && tmp <= LOG10) {
          posfix_expresion.push_back(lexem(tmp, 0.0));
          st.pop();
        }
      }
    }
  }
}

void CalcSolution::FromInfixToPosfixFinish(std::stack<token>& st) {
  token tok;
  bool loc_res = false;

  while (!loc_res) {
    if (st.size() == 0)
      loc_res = true;
    else {
      tok = st.top();
      if (tok == OPEN_BRACE) {
        error = true;
        loc_res = true;
      } else {
        posfix_expresion.push_back(lexem(tok, 0.0));
        st.pop();
      }
    }
  }
}

bool CalcSolution::StartWithSmallOperation(lexem& lex) {
  lex.tok = NOTHING;

  switch (infix_expresion[0]) {
    case '+':
      lex.tok = ADD;
      break;
    case '-':
      lex.tok = SUB;
      break;
    case '*':
      lex.tok = MUL;
      break;
    case '/':
      lex.tok = DIV;
      break;
    case '^':
      lex.tok = POW;
      break;
    default:
      break;
  }

  return lex.tok != NOTHING;
}

long double CalcSolution::GetDoubleFromString() {
  unar = false;
  long double res = 0.0;
  char* next_token;

  res = std::strtold(infix_expresion.c_str(), &next_token);
  infix_expresion = std::string(next_token);

  return res;
}

int CalcSolution::GetPriority(token tok) {
  int res = 0;

  if (tok == POW)
    res = 3;
  else if (tok == MUL || tok == DIV)
    res = 2;
  else if (tok == SUB || tok == ADD)
    res = 1;

  return res;
}

void CalcSolution::FromPosfixToAnswer() {
  std::stack<lexem> st;

  for (auto it = posfix_expresion.begin();
       !error && it != posfix_expresion.end(); it++) {
    if (it->tok == NUM)
      st.push(*it);
    else if (it->tok == X)
      st.push(lexem(NUM, x_val));
    else if (it->tok <= MOD && it->tok >= ADD)
      st.push(lexem(NUM, FromPosfixToAnswerSmallOper(st, it->tok)));
    else if (it->tok <= LOG10 && it->tok >= SIN)
      st.push(lexem(NUM, FromPosfixToAnswerFunc(st, it->tok)));
  }

  if (!st.empty()) {
    result = st.top().value;
    st.pop();
    if (!st.empty()) error = true;
  } else
    error = true;
}

long double CalcSolution::FromPosfixToAnswerSmallOper(std::stack<lexem>& st,
                                                      token oper) {
  long double res = 0.0, a = 0.0, b = 0.0;

  if (st.empty())
    error = 1;
  else {
    a = st.top().value;
    st.pop();
  }
  if (oper == SUB && (st.empty() || (!st.empty() && st.top().tok != NUM)))
    res = -a;
  else if (st.empty())
    error = true;
  else {
    b = st.top().value;
    st.pop();

    switch (oper) {
      case ADD:
        res = b + a;
        break;
      case SUB:
        res = b - a;
        break;
      case MUL:
        res = b * a;
        break;
      case DIV:
        if (fabsl(a) < 1e-15)
          error = true;
        else
          res = b / a;
        break;
      case POW:
        res = powl(b, a);
        break;
      case MOD:
        res = fmodl(b, a);
        break;
      default:
        break;
    }
  }

  return res;
}

long double CalcSolution::FromPosfixToAnswerFunc(std::stack<lexem>& st,
                                                 token oper) {
  double res = 0.0, a = 0.0;

  if (st.empty())
    error = true;
  else {
    a = st.top().value;
    st.pop();

    switch (oper) {
      case COS:
        res = cosl(a);
        break;
      case SIN:
        res = sinl(a);
        break;
      case TAN:
        res = tanl(a);
        break;
      case ACOS:
        res = acosl(a);
        break;
      case ASIN:
        res = asinl(a);
        break;
      case ATAN:
        res = atanl(a);
        break;
      case SQRT:
        res = sqrtl(a);
        break;
      case LOG10:
        res = log10l(a);
        break;
      case LN:
        res = logl(a);
        break;
      default:
        break;
    }
  }

  if (isnanl(res) && !st.empty()) error = true;
  return res;
}

}  // namespace my
