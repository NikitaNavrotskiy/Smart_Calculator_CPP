#ifndef _MODEL_INTERFACE_H
#define _MODEL_INTERFACE_H

#include <regex>
#include <string>

namespace my {

class Solution {
 public:
  virtual void Compute() = 0;
  virtual bool validate() = 0;
  bool ValidateDouble(const std::string& double_);
  void ChangeToDots(std::string& str);

  long double GetDoubleFromString(const std::string& str, bool& error);
  ~Solution() = default;
};

inline bool Solution::ValidateDouble(const std::string& double_) {
  std::regex pattern(
      "(^-?[0-9]+((\\.|,)[0-9]+)?$)|(^[-\\+]?[0-9]+([\\.,][0-9]+)?[eE]([-\\+]["
      "0-9]+)?$)");

  return std::regex_match(double_, pattern);
}

}  // namespace my

#endif
