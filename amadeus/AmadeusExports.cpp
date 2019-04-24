#include "AmadeusExports.h"

namespace core {
AmadeusGDS::AmadeusGDS() {
  _httpClient = new AmadeusHttpClient("haritonov", 8888);
}
AmadeusGDS::~AmadeusGDS() { delete _httpClient; }

string AmadeusGDS::Say(string &s) {
  string result = "Calling AmadeusGDS Say " + s;
  return result;
}

string AmadeusGDS::Search(string &searchString) {
  string request = "/search";
  string result = _httpClient->get(request);
  return result;
}

string AmadeusGDS::Hold(string &offerId) {
  string request = "/hold";
  string result = _httpClient->get(request);
  return result;
}

string AmadeusGDS::Book(string &offerId) {
  string request = "/book";
  string result = _httpClient->get(request);
  return result;
}

string AmadeusGDS::Ticket(string &pnr) {
  string request = "/ticket";
  string result = _httpClient->get(request);
  return result;
}

} // namespace core