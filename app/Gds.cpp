#include "Gds.h"

Gds::Gds(LPCSTR dllName, map<string, string> param) : BaseGDS(param) {
  _dll = LoadLibrary(dllName);
  GdsFactory factory =
      reinterpret_cast<GdsFactory>(GetProcAddress(_dll, "CreateGDS"));

  if (!factory) {
    FreeLibrary(_dll);
  }

  _instance = factory(_param);
}

Gds::~Gds() {
  _instance->Destroy();
  FreeLibrary(_dll);
}

string Gds::Say(string& s) { return _instance->Say(s); }

list<FlightOffer> Gds::Search(string& searchString) {
  return _instance->Search(searchString);
}

FlightOffer* Gds::Hold(string& offerId) { return _instance->Hold(offerId); }

Reservation* Gds::Book() {
  Reservation* result = _instance->Book();
  return result;
}

Reservation* Gds::Ticket(string& pnr) { return _instance->Ticket(pnr); }