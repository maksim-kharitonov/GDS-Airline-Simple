#pragma once
using namespace std;

#ifndef COMMAND_H
#define COMMAND_H

#include <iostream>
#include <regex>
#include <string>
#include <vector>
#include <map>
#include "Gds.h"
#include "ConfigReader.h"


class Command {
 public:
  static void destroy();
  static string getCommandCode(const string &cmdString);

  Command();
  Command(const string &cmdString);
  ~Command();

  string getCommandCode();
  string getParamString();
  string getModifier();
  virtual int execute() = 0;

 protected:
  string _gdsCode;
  string _cmdCode;
  string _paramString;
  string _modifier;

  static map<string, string> _gdsModulesStrings;
  static map<string, Gds *> _gdsModuleImplementations;
  static ConfigReader *_config;
};

class CommandException : public exception {
 public:
  CommandException(const char *msg, const char *code)
      : exception(msg), _code(code) {}
  const char *getCode();

 private:
  const char *_code;
};

class ExitCommand : public Command {
 public:
  ExitCommand(const string &cmdString) : Command(cmdString) {}
  int execute();
};

class ModuleCommad : public Command {
 public:
  ModuleCommad(const string &cmdString) : Command(cmdString) {}
  int execute();
};

class SayCommand : public Command {
 public:
  SayCommand(const string &cmdString) : Command(cmdString) {}
  int execute();
};

class SearchCommand : public Command {
 public:
  SearchCommand(const string &cmdString) : Command(cmdString) {}
  int execute();
};

class HoldCommand : public Command {
 public:
  HoldCommand(const string &cmdString) : Command(cmdString) {}
  int execute();
};

class BookCommand : public Command {
 public:
  BookCommand(const string &cmdString) : Command(cmdString) {}
  int execute();
};

class TicketCommand : public Command {
 public:
  TicketCommand(const string &cmdString) : Command(cmdString) {}
  int execute();
};

class HelpCommand : public Command {
 public:
  HelpCommand(const string &cmdString) : Command(cmdString) {}
  int execute();
};

class UnknownCommand : public Command {
 public:
  UnknownCommand(const string &cmdString) : Command(cmdString) {}
  int execute();
};

class CommandFactory {
 public:
  static Command *CreateCommand(const string &cmdString);
};

#endif  // !COMMAND_H
