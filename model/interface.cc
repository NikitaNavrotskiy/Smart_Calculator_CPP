#include "interface.h"

void my::Solution::ChangeToDots(std::string& str) {
  for (size_t i = 0; i < str.size(); i++)
    if (str[i] == '.') str[i] = ',';
}

long double my::Solution::GetDoubleFromString(const std::string& str,
                                               bool& error) {
  if (!ValidateDouble(str)) error = true;
  return strtold(str.c_str(), nullptr);
}
