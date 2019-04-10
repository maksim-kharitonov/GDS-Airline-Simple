#include "Command.h"
#include "Tools.h"
#include <algorithm>
#include <functional>
#include <locale>
using namespace std;

Command::Command() {}

Command::Command(const string &cmdString) {
  try {
    regex expr("^[\\t ]*(\\w+)(?:[\\t ]+([\\w ]*))?(?:\\\\(.*))?$",
               regex_constants::icase);
    for (sregex_iterator it(cmdString.begin(), cmdString.end(), expr), itEnd;
         it != itEnd; ++it) {
      if ((*it)[1] == "")
        throw CommandException(
            "Command format: <CMD_CODE> <CMD_PARAMS> \\ <CMD_MODIFIER>",
            "format_exception");
      _cmdCode = tools::uppercase_copy((*it)[1]);
      
      if ((*it)[2] != "") {
        _paramString = tools::trim_copy((*it)[2]);
      }
      if ((*it)[3] != "") {
        _modifier = tools::trim_copy((*it)[3]);
      }
    }

    if (_cmdCode == "") {
      throw CommandException(
          "Command format: <CMD_CODE> <CMD_PARAMS> \\ <CMD_MODIFIER>",
          "format_exception");
    }

  } catch (const std::regex_error &e) {
    throw CommandException(e.what(), "regex_exception");
  }
}

Command::~Command() {}

string Command::getCommandCode() { return _cmdCode; }

string Command::getParamString() { return _paramString; }

string Command::getModifier() { return _modifier; }

const char *CommandException::getCode() { return _code; }

