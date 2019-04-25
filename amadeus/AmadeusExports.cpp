#include "AmadeusExports.h"
//прописал, чтобы Visual Studio не ругалась
#include "../lib/tinyxml.h"

namespace core {
AmadeusGDS::AmadeusGDS(map<string, string> _param) : BaseGDS(_param) {
  string hostname = _param["hostname"];
  int port = stoi(_param["port"]);
  _httpClient = new AmadeusHttpClient(hostname, port);
}
AmadeusGDS::~AmadeusGDS() { delete _httpClient; }

string AmadeusGDS::Say(string &s) {
  string result = "Calling AmadeusGDS Say " + s;
  return result;
}

list<FlightOffer> AmadeusGDS::Search(string &searchString) {
  _searchResult.clear();
  delete _holdedOffer;

  list<FlightOffer> result;
  string request = "/search";
  string response = _httpClient->get(request);

  TiXmlDocument doc;
  doc.Parse((const char *)response.c_str(), 0, TIXML_ENCODING_UTF8);

  TiXmlElement *rootElement = doc.RootElement();

  int i = 0;
  if (NULL != rootElement) {
    TiXmlElement *pricingRoute =
        rootElement->FirstChildElement()->FirstChildElement("pricing_route");
    if (NULL != pricingRoute) {
      TiXmlElement *variant = pricingRoute->FirstChildElement("variant");
      while (variant) {
        FlightOffer::Builder offerBuilder = FlightOffer::Builder()
                                                .setUuid(std::to_string(++i))
                                                .setGds("AMADEUS");
        const char *generalCarrier = variant->Attribute("seance");
        if (generalCarrier) {
          offerBuilder.setGeneralCarrier(generalCarrier);
        }
        TiXmlElement *totalPrice = variant->FirstChildElement("variant_total");
        if (totalPrice) {
          offerBuilder.setPrice(totalPrice->GetText());
          offerBuilder.setCurrency(totalPrice->Attribute("currency"));
        }
        TiXmlElement *flight = variant->FirstChildElement("flight");
        while (flight) {
          FlightOffer::OriginDestination::Builder odBuilder =
              FlightOffer::OriginDestination::Builder();
          TiXmlElement *company = flight->FirstChildElement("company");
          if (company) {
            odBuilder.setMarketingCarrier(company->GetText());
          }
          TiXmlElement *origin = flight->FirstChildElement("origin");
          if (origin) {
            odBuilder.setDeparturePort(origin->GetText());
          }
          TiXmlElement *destination = flight->FirstChildElement("destination");
          if (destination) {
            odBuilder.setArrivalPort(destination->GetText());
          }
          TiXmlElement *deptdate = flight->FirstChildElement("deptdate");
          if (deptdate) {
            odBuilder.setDepartureDate(deptdate->GetText());
          }
          TiXmlElement *arrvdate = flight->FirstChildElement("arrvdate");
          if (arrvdate) {
            odBuilder.setArrivalDate(arrvdate->GetText());
          }
          TiXmlElement *deptime = flight->FirstChildElement("depttime");
          if (deptime) {
            odBuilder.setDepartureTime(deptime->GetText());
          }
          TiXmlElement *arrvtime = flight->FirstChildElement("arrvtime");
          if (arrvtime) {
            odBuilder.setArrivalTime(arrvtime->GetText());
          }
          TiXmlElement *bookingClass = flight->FirstChildElement("class");
          if (bookingClass) {
            odBuilder.setBookingClass(bookingClass->GetText());
          }

          TiXmlElement *priceDetail = flight->FirstChildElement("price");
          if (priceDetail) {
            TiXmlElement *fare = priceDetail->FirstChildElement("fare");
            if (fare) {
              odBuilder.setBasicFareCode(fare->Attribute("code"));
            }
          }

		  offerBuilder.addFlight(odBuilder.build());

		  flight = flight->NextSiblingElement("flight");
        }

        FlightOffer offer = offerBuilder.build();
        result.push_back(offer);
        _searchResult[offer.uuid] = offer;

        variant = variant->NextSiblingElement("variant");
      }
    }
  }

  return result;
}

FlightOffer *AmadeusGDS::Hold(string &offerId) {
  if (_searchResult.find(offerId) != _searchResult.end()) {
    _holdedOffer = &_searchResult[offerId];
    return &_searchResult[offerId];
  } else {
    return NULL;
  }
}

Reservation *AmadeusGDS::Book() {
  if (_holdedOffer) {
    Reservation *resPtr = dynamic_cast<Reservation *>(_holdedOffer);
    if (resPtr != nullptr) {
      cout << "Already has reservation in status " << resPtr->status << endl;
      return resPtr;
    } else {
      string request = "/book?id=" + _holdedOffer->uuid;
      string result = _httpClient->get(request);
      Reservation *rs = new Reservation(*_holdedOffer, "AABBCC", "BOOKED");
      _holdedOffer = rs;
      return rs;
    }
  } else {
    return NULL;
  }
}

Reservation *AmadeusGDS::Ticket(string &pnr) {
  string request = "/ticket";
  string result = _httpClient->get(request);
  return NULL;
}

map<string, FlightOffer> AmadeusGDS::_searchResult;
FlightOffer *AmadeusGDS::_holdedOffer;

}  // namespace core