#include "Command.h"
#include <algorithm>
#include <functional>
#include <locale>
#include "Colors.h"
#include "Tools.h"
using namespace std;

FlightOffer *Command::_holdedOffer;

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
      string moduleName = tools::uppercase_copy(it->first);
      string moduleDll = it->second;
      _gdsModuleImplementations[moduleName] =
          new Gds(moduleDll.c_str(),
                  _config->getSection(tools::uppercase_copy(moduleName)));
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
  } else if (command == "HELP") {
    return new HelpCommand(cmdString);
  } else {
    return new UnknownCommand(cmdString);
  }
}

int ExitCommand::execute() { return 1; }

int UnknownCommand::execute() { return 2; }

int SayCommand::execute() {
  string gds = tools::uppercase_copy(_modifier);
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
  _holdedOffer = NULL;
  string gds = tools::uppercase_copy(_modifier);

  regex expr(
      "^[\\t ]*"
      "([A-Za-z]{3})"
      "[\\t ]*"
      "([A-Za-z]{3})"
      "[\\t ]*"
      "((?:0[1-9]|[12][0-9]|3[01])"
      "[\\t ]*"
      "(?:JAN|FEB|MAR|APR|MAY|JUN|JUL|AUG|SEP|OCT|NOV|DEC)"
      "[\\t ]*"
      "[0-9][0-9]"
      ")$",
      regex_constants::icase);
  smatch sm;
  bool found = regex_search(_paramString, sm, expr);
  if (!found) {
    throw CommandException(
        "Command format: SEARCH PR1 PR2 DD MON YY \\ <CMD_MODIFIER>",
        "format_exception");
  }

  stringstream reqstream;
  for (sregex_iterator it(_paramString.begin(), _paramString.end(), expr),
       itEnd;
       it != itEnd; ++it) {
    reqstream << "prt1=" << tools::uppercase_copy((*it)[1]) << "&prt2=" << tools::uppercase_copy((*it)[2])
              << "&date=" << (*it)[3];
  }
  string request = reqstream.str();

  if (gds == "") {
    for (auto it = _gdsModuleImplementations.cbegin();
         it != _gdsModuleImplementations.cend(); ++it) {
      list<FlightOffer> offers = it->second->Search(request);
      for (list<FlightOffer>::iterator offer = offers.begin();
           offer != offers.end(); ++offer) {
        cout << *offer << endl;
      }
    }
  } else {
    list<FlightOffer> offers = _gdsModuleImplementations[gds]->Search(request);
    for (list<FlightOffer>::iterator offer = offers.begin();
         offer != offers.end(); ++offer) {
      cout << *offer << endl;
    }
  }

  return 0;
}

int HoldCommand::execute() {
  string gds = tools::uppercase_copy(_modifier);
  if (gds == "") {
    throw CommandException("Add GDS modifier: HOLD <UUID> \\ <GDS>",
                           "format_exception");
  } else {
    FlightOffer *offer = _gdsModuleImplementations[gds]->Hold(_paramString);
    if (offer) {
      _holdedOffer = offer;
      cout << BOLD(FGRN("Offer hold: SUCCESS")) << endl
           << "------------------------" << endl;
      cout << *_holdedOffer << endl;
    } else {
      throw CommandException("Selected offer not found", "Data exception");
    }
  }
  return 0;
}

int BookCommand::execute() {
  if (_modifier != "" || _paramString != "") {
    throw CommandException("Command format: BOOK", "format_exception");
  } else if (!_holdedOffer) {
    throw CommandException("Holded offer not found; please hold first",
                           "Data exception");
  } else {
    Reservation *reservation =
        _gdsModuleImplementations[_holdedOffer->gds]->Book();
    if (reservation) {
      //_holdedOffer = reservation;
      cout << BOLD(FGRN("Offer book: SUCCESS")) << endl
           << "------------------------" << endl;
      cout << *reservation << endl;
      _holdedOffer = reservation;
    } else {
      throw CommandException(
          "Booking command exception. Hold offer again or try later",
          "Data exception");
    }
  }
  return 0;
}

int TicketCommand::execute() {
  if (_paramString == "") {
    throw CommandException("Command format: BOOK <PNR>", "format_exception");
  } else if (!_holdedOffer) {
    throw CommandException("Holded offer not found; please hold first",
                           "Data exception");
  } else {
    Reservation *resPtr = dynamic_cast<Reservation *>(_holdedOffer);
    if (resPtr == nullptr) {
      throw CommandException("Offer was not booked.", "Data exception");
    }

    Reservation *reservation =
        _gdsModuleImplementations[resPtr->gds]->Ticket(_paramString);
    if (reservation) {
      //_holdedOffer = reservation;
      cout << BOLD(FGRN("Offer ticket: SUCCESS")) << endl
           << "------------------------" << endl;
      cout << *reservation << endl;
      _holdedOffer = reservation;
    } else {
      throw CommandException(
          "Ticket command exception. Hold offer again or try later",
          "Data exception");
    }
  }
  return 0;
}

int HelpCommand::execute() {
  cout << "-----------------------------" << endl;
  cout << BOLD(FMAG("Command syntax: ")) << endl;
  cout << "-----------------------------" << endl;
  cout << "Command format: <CMD_CODE> <CMD_PARAMS> \\ <CMD_MODIFIER>" << endl;
  cout << "List of available commands:" << endl;
  cout << "-----------------------------" << endl;
  cout << BOLD(FGRN("SEARCH")) << endl;
  cout << "-----------------------------" << endl;
  cout << "find available flights using specified options" << endl;
  cout << "SEARCH <CITY1> <CITY2> <DD><MON><YY> \ <GDS>" << endl;
  cout << BOLD(FGRN("HOLD")) << endl;
  cout << "-----------------------------" << endl;
  cout << "Hold target offer for reservation" << endl;
  cout << "HOLD <OFFER_ID> \ <GDS>" << endl;
  cout << BOLD(FGRN("BOOK")) << endl;
  cout << "-----------------------------" << endl;
  cout << "Book holded offer" << endl;
  cout << "BOOK" << endl;
  cout << BOLD(FGRN("TICKET")) << endl;
  cout << "-----------------------------" << endl;
  cout << "Ticket reservation by number" << endl;
  cout << "TICKET <PNR>" << endl;
  cout << "-----------------------------" << endl;
  cout << BOLD(FGRN("EXIT")) << endl;
  cout << "-----------------------------" << endl;
  cout << "exit programm without saving result" << endl;
  return 0;
}
