#include "SirenaExports.h"

namespace core {
SirenaGDS::SirenaGDS() {}
SirenaGDS::~SirenaGDS() {}

string SirenaGDS::Say(string &s) {
  string result = "Calling SirenaGDS Say " + s;
  return result;
}

string SirenaGDS::Search(string &searchString) {
  string result = "Calling SirenaGDS search " + searchString;
  return result;
}

string SirenaGDS::Hold(string &offerId) {
  string result = "Calling SirenaGDS Hold offer " + offerId;
  return result;
}

string SirenaGDS::Book(string &offerId) {
  string result = "Calling SirenaGDS Book offer " + offerId;
  return result;
}

string SirenaGDS::Ticket(string &pnr) {
  string result = "Calling SirenaGDS Ticketing PNR " + pnr;
  return result;
}

} // namespace core