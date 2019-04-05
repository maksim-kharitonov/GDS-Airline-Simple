#pragma once
using namespace std;

#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <regex>
#include <vector>

class Command {
public:
  Command();
  Command(const string &cmdString);
  ~Command();

private:
  string _cmdCode;
  vector<string> _param;
  string _modifier;
};

#endif // !COMMAND_H
