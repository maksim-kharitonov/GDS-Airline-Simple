#pragma once

#ifndef TOOLS_H
#define TOOLS_H

#include <algorithm>
#include <cctype>
#include <functional>
#include <locale>

namespace tools {
// trim from start (in place)
void ltrim(std::string &s);

// trim from end (in place)
void rtrim(std::string &s);

// trim from both ends (in place)
void trim(std::string &s);

// uppercase (in place)
void uppercase(std::string &s);

// lowercase (in place)
void lowercase(std::string &s);

// trim from start (copying)
std::string ltrim_copy(std::string s);

// trim from end (copying)
std::string rtrim_copy(std::string s);

// trim from both ends (copying)
std::string trim_copy(std::string s);

// uppercase
std::string uppercase_copy(std::string s);

// lowercase
std::string lowercase_copy(std::string s);
} // namespace tools

#endif // !TOOLS_H