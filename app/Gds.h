#ifndef GDS_H
#define GDS_H

#include "GdsExports.h"
#include "GdsFactory.h"
#include <Windows.h>

class Gds : public core::BaseGDS {
 public:
  Gds(LPCSTR dllName);
  ~Gds();

  string Say(string& s);
  string Search(string& searchString);
  string Hold(string& offerId);
  string Book(string& offerId);
  string Ticket(string& pnr);

 private:
  HMODULE _dll;
  core::BaseGDS* _instance;
};
#endif  //! GDS_H