#ifndef GDS_H
#define GDS_H

#include "GdsExports.h"
#include "GdsFactory.h"
#include <Windows.h>
#include <list>
#include "FlightOffer.h"

class Gds : public core::BaseGDS {
 public:
  Gds(LPCSTR dllName, map<string, string> param);
  ~Gds();

  string Say(string& s);
  list<FlightOffer> Search(string& searchString);
  FlightOffer* Hold(string& offerId);
  Reservation* Book();
  Reservation* Ticket(string& pnr);

 private:
  HMODULE _dll;
  core::BaseGDS* _instance;
};
#endif  //! GDS_H