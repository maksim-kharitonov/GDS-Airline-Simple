#pragma once
using namespace std;

#ifndef COMMAND_H
#define COMMAND_H

#include <iostream>
#include <regex>
#include <string>
#include <vector>

class Command {
public:
  Command();
  Command(const string &cmdString);
  ~Command();

  string getCommandCode();
  string getParamString();
  string getModifier();

private:
  string _gdsCode;
  string _cmdCode;
  string _paramString;
  string _modifier;
};

class CommandException : public exception {
public:
  CommandException(const char *msg, const char *code) : exception(msg),_code(code) {}
  const char *getCode();
private:
  const char* _code;
};

#endif // !COMMAND_H
