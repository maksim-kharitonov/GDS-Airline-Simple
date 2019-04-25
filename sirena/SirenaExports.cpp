#include "SirenaExports.h"

namespace core {
SirenaGDS::SirenaGDS(map<string, string> _param) : BaseGDS(_param) {}
SirenaGDS::~SirenaGDS() {}

string SirenaGDS::Say(string &s) {
  string result = "Calling SirenaGDS Say " + s;
  return result;
}

list<FlightOffer> SirenaGDS::Search(string &searchString) {
  list<FlightOffer> result;
  return result;
}

FlightOffer *SirenaGDS::Hold(string &offerId) { return NULL; }

Reservation *SirenaGDS::Book() { return NULL; }

Reservation *SirenaGDS::Ticket(string &pnr) { return NULL; }

}  // namespace core