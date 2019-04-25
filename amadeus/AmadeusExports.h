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
  FlightOffer *Hold(string &offerId);
  Reservation *Book();
  Reservation *Ticket(string &pnr);

 private:
  AmadeusHttpClient *_httpClient;
  static string searchFlights(string &s);
  static SOCKET OpenConnection(const char *hostname, int port);

  static map<string, FlightOffer> _searchResult;  // Результаты последнего поиска
  static FlightOffer *_holdedOffer;  // Выбранный вариант перелета
};
}  // namespace core