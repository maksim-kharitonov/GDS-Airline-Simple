#pragma once
#include "GdsExports.h"

using namespace std;

namespace core {
// MS Visual C++ compiler emits C4275 warning about not exported base class.
class Sirena_API SirenaGDS : public BaseGDS {
public:
  SirenaGDS();
  virtual ~SirenaGDS();

  string Say(string &s);
  string Search(string &searchString);
  string Hold(string &offerId);
  string Book(string &offerId);
  string Ticket(string &pnr);
};
} // namespace core