#include "Gds.h"

Gds::Gds(LPCSTR dllName) {
  _dll = LoadLibrary(dllName);
  GdsFactory factory =
      reinterpret_cast<GdsFactory>(GetProcAddress(_dll, "CreateGDS"));

  if (!factory) {
    FreeLibrary(_dll);
  }

  _instance = factory();
}

Gds::~Gds() {
  _instance->Destroy();
  FreeLibrary(_dll);
}

string Gds::Say(string& s) { return _instance->Say(s); }

string Gds::Search(string& searchString) {
  return _instance->Search(searchString);
}

string Gds::Hold(string& offerId) { return _instance->Hold(offerId); }

string Gds::Book(string& offerId) { return _instance->Book(offerId); }

string Gds::Ticket(string& pnr) { return _instance->Ticket(pnr); }