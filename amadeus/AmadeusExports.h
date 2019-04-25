#pragma once
#include "AmadeusHttpClient.h"
#include "GdsExports.h"
#include "tinyxml.h"
#include <iostream>
#include <sstream>
#include "FlightOffer.h"

using namespace std;

namespace core {
// MS Visual C++ compiler emits C4275 warning about not exported base class.
class Amadeus_API AmadeusGDS : public BaseGDS {
 public:
  AmadeusGDS(map<string,string> _param);
  virtual ~AmadeusGDS();

  string Say(string &s);
  list<FlightOffer> Search(string &searchString);
  string Hold(string &offerId);
  string Book(string &offerId);
  string Ticket(string &pnr);

 private:
  AmadeusHttpClient *_httpClient;
  static string searchFlights(string &s);
  static SOCKET OpenConnection(const char *hostname, int port);
};
}  // namespace core