#pragma once
#include "AmadeusHttpClient.h"
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

 private:
  AmadeusHttpClient *_httpClient;
  static string searchFlights(string &s);
  static SOCKET OpenConnection(const char *hostname, int port);
};
}  // namespace core