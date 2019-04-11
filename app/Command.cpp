#include "Command.h"
#include <algorithm>
#include <functional>
#include <locale>
#include "Tools.h"
using namespace std;

string Command::getCommandCode(const string &cmdString) {
  smatch sm;
  regex expr("^[\\t ]*(\\w+)");
  bool found = regex_search(cmdString, sm, expr);
  if (found) {
    return tools::uppercase_copy(sm.str(1));
  } else {
    throw CommandException(
        "Command format: <CMD_CODE> <CMD_PARAMS> \\ <CMD_MODIFIER>",
        "format_exception");
  }
}

void Command::destroy() {
  delete _config;
  for (auto it = _gdsModuleImplementations.cbegin();
       it != _gdsModuleImplementations.cend(); ++it) {
    delete (it->second);
  }
}

map<string, string> Command::_gdsModulesStrings;
map<string, Gds *> Command::_gdsModuleImplementations;
ConfigReader *Command::_config;

Command::Command() {
  if (_gdsModulesStrings.empty()) {
    _config = new ConfigReader("./conf/config.ini");
    _gdsModulesStrings = _config->getSection("GDS_MODULE_LIST");
    for (auto it = _gdsModulesStrings.cbegin(); it != _gdsModulesStrings.cend();
         ++it) {
      _gdsModuleImplementations[it->first] = new Gds(it->second.c_str());
    }
  }
}

Command::Command(const string &cmdString) : Command() {
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

Command *CommandFactory::CreateCommand(const string &cmdString) {
  string command = Command::getCommandCode(cmdString);
  if (command == "EXIT") {
    return new ExitCommand(cmdString);
  } else if (command == "SAY") {
    return new SayCommand(cmdString);
  } else if (command == "SEARCH") {
    return new SearchCommand(cmdString);
  } else if (command == "HOLD") {
    return new HoldCommand(cmdString);
  } else if (command == "BOOK") {
    return new BookCommand(cmdString);
  } else if (command == "TICKET") {
    return new TicketCommand(cmdString);
  } else if (command == "MODULES") {
    return new ModuleCommad(cmdString);
  } else {
    return new UnknownCommand(cmdString);
  }
}

int ExitCommand::execute() { return 1; }

int UnknownCommand::execute() { return 2; }

int SayCommand::execute() {
  string gds = tools::lowercase_copy(_modifier);
  if (gds == "") {
    for (auto it = _gdsModuleImplementations.cbegin();
         it != _gdsModuleImplementations.cend(); ++it) {
      cout << it->second->Say(_paramString) << endl;
    }
  } else {
    cout << _gdsModuleImplementations[gds]->Say(_paramString) << endl;
  }

  return 0;
}

int ModuleCommad::execute() {
  cout << "----------- Available module list: -----------------" << endl;
  for (auto it = _gdsModulesStrings.cbegin(); it != _gdsModulesStrings.cend();
       ++it) {
    cout << it->first << " " << it->second << endl;
  }
  return 0;
}

int SearchCommand::execute() {
  string gds = tools::lowercase_copy(_modifier);
  if (gds == "") {
    for (auto it = _gdsModuleImplementations.cbegin();
         it != _gdsModuleImplementations.cend(); ++it) {
      cout << it->second->Search(_paramString) << endl;
    }
  } else {
    cout << _gdsModuleImplementations[gds]->Search(_paramString) << endl;
  }

  return 0;
}

int HoldCommand::execute() {
  string gds = tools::lowercase_copy(_modifier);
  if (gds == "") {
    for (auto it = _gdsModuleImplementations.cbegin();
         it != _gdsModuleImplementations.cend(); ++it) {
      cout << it->second->Hold(_paramString) << endl;
    }
  } else {
    cout << _gdsModuleImplementations[gds]->Hold(_paramString) << endl;
  }
  return 0;
}

int BookCommand::execute() {
  string gds = tools::lowercase_copy(_modifier);
  if (gds == "") {
    for (auto it = _gdsModuleImplementations.cbegin();
         it != _gdsModuleImplementations.cend(); ++it) {
      cout << it->second->Book(_paramString) << endl;
    }
  } else {
    cout << _gdsModuleImplementations[gds]->Book(_paramString) << endl;
  }
  return 0;
}

int TicketCommand::execute() {
  string gds = tools::lowercase_copy(_modifier);
  if (gds == "") {
    for (auto it = _gdsModuleImplementations.cbegin();
         it != _gdsModuleImplementations.cend(); ++it) {
      cout << it->second->Ticket(_paramString) << endl;
    }
  } else {
    cout << _gdsModuleImplementations[gds]->Ticket(_paramString) << endl;
  }
  return 0;
}
