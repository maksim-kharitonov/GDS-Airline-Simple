#pragma once

#ifdef _WIN32
#ifdef amadeus_EXPORTS
#define Amadeus_API __declspec(dllexport)
#else
#define Amadeus_API __declspec(dllimport)
#endif // Amadeus_API
#else
#define Amadeus_API
#endif

#include <string>
#include <list>
#include <map>
#include "FlightOffer.h"

using namespace std;

namespace core {
class BaseGDS {
 protected:
  map<string, string> _param;
 public:
  BaseGDS(map<string, string> _param) : _param(_param){};
  virtual void Destroy() { delete this; }

  virtual string Say(string &s) = 0;
  virtual list<FlightOffer> Search(string &searchString) = 0;
  virtual string Hold(string &offerId) = 0;
  virtual string Book(string &offerId) = 0;
  virtual string Ticket(string &pnr) = 0;
};
} // namespace core