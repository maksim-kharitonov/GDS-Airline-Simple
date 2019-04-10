#include "Tools.h"

namespace tools {
// trim from start (in place)
void ltrim(std::string &s) {
  s.erase(s.begin(),
          std::find_if(s.begin(), s.end(),
                       std::not1(std::ptr_fun<int, int>(std::isspace))));
}

// trim from end (in place)
void rtrim(std::string &s) {
  s.erase(std::find_if(s.rbegin(), s.rend(),
                       std::not1(std::ptr_fun<int, int>(std::isspace)))
              .base(),
          s.end());
}

// trim from both ends (in place)
void trim(std::string &s) {
  ltrim(s);
  rtrim(s);
}

void uppercase(std::string &s) {
  transform(s.begin(), s.end(), s.begin(), ::toupper);
}

void lowercase(std::string &s) {
  transform(s.begin(), s.end(), s.begin(), ::tolower);
}

// trim from start (copying)
std::string ltrim_copy(std::string s) {
  ltrim(s);
  return s;
}

// trim from end (copying)
std::string rtrim_copy(std::string s) {
  rtrim(s);
  return s;
}

// trim from both ends (copying)
std::string trim_copy(std::string s) {
  trim(s);
  return s;
}

std::string uppercase_copy(std::string s) {
  uppercase(s);
  return s;
}

std::string lowercase_copy(std::string s) {
  lowercase(s);
  return s;
}
} // namespace tools
