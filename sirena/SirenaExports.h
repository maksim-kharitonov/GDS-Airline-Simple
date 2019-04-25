#pragma once
#include "GdsExports.h"

using namespace std;

namespace core {
// MS Visual C++ compiler emits C4275 warning about not exported base class.
class Sirena_API SirenaGDS : public BaseGDS {
 public:
  SirenaGDS(map<string, string> _param);
  virtual ~SirenaGDS();

  string Say(string &s);
  list<FlightOffer> Search(string &searchString);
  FlightOffer *Hold(string &offerId);
  Reservation *Book();
  Reservation *Ticket(string &pnr);
};
}  // namespace core