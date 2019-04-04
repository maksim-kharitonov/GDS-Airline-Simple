#include "AmadeusExports.h"

namespace core {
AmadeusGDS::AmadeusGDS() {}
AmadeusGDS::~AmadeusGDS() {}

string AmadeusGDS::Say(string &s) {
  string result = "Calling AmadeusGDS Say " + s;
  return result;
}

string AmadeusGDS::Search(string &searchString) {
  string result = "Calling AmadeusGDS search " + searchString;
  return result;
}

string AmadeusGDS::Hold(string &offerId) {
  string result = "Calling AmadeusGDS Hold offer " + offerId;
  return result;
}

string AmadeusGDS::Book(string &offerId) {
  string result = "Calling AmadeusGDS Book offer " + offerId;
  return result;
}

string AmadeusGDS::Ticket(string &pnr) {
  string result = "Calling AmadeusGDS Ticketing PNR " + pnr;
  return result;
}

} // namespace core