#pragma once
#include "GdsExports.h"

using namespace std;

namespace core {
// MS Visual C++ compiler emits C4275 warning about not exported base class.
class Amadeus_API AmadeusGDS : public BaseGDS {
public:
  AmadeusGDS();
  virtual ~AmadeusGDS();

  string Say(string &s);
  string Search(string &searchString);
  string Hold(string &offerId);
  string Book(string &offerId);
  string Ticket(string &pnr);
};
} // namespace core