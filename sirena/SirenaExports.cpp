#include "SirenaExports.h"

namespace core {
SirenaGDS::SirenaGDS(map<string,string> _param): BaseGDS(_param) {}
SirenaGDS::~SirenaGDS() {}

string SirenaGDS::Say(string &s) {
  string result = "Calling SirenaGDS Say " + s;
  return result;
}

list<FlightOffer> SirenaGDS::Search(string &searchString) {
  list<FlightOffer> result;
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