#include "AmadeusExports.h"
//��������, ����� Visual Studio �� ��������
#include "../lib/Colors.h"
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
  string request = "/search?" + searchString;
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
      cerr << BOLD(FRED("Already has reservation in status ")) << resPtr->status
           << endl;
      return resPtr;
    } else {
      string request = "/book?id=" + _holdedOffer->uuid;
      string response = _httpClient->get(request);

      TiXmlDocument doc;
      doc.Parse((const char *)response.c_str(), 0, TIXML_ENCODING_UTF8);

      TiXmlElement *rootElement = doc.RootElement();

      if (NULL != rootElement) {
        TiXmlElement *pnr =
            rootElement->FirstChildElement()->FirstChildElement("pnr");
        if (NULL != pnr) {
          Reservation *rs = new Reservation(*_holdedOffer);
          rs->pnr = pnr->GetText();
          rs->status = pnr->Attribute("status");
          _holdedOffer = rs;
          return rs;
        }
      }
      return NULL;
    }
  } else {
    return NULL;
  }
}

Reservation *AmadeusGDS::Ticket(string &pnr) {
  if (_holdedOffer) {
    Reservation *resPtr = dynamic_cast<Reservation *>(_holdedOffer);
    if (resPtr == nullptr) {
      cerr << BOLD(FRED("Offer is not booked")) << endl;
      return NULL;
    }
    if (resPtr->pnr != pnr) {
      cerr << BOLD(FRED("Offer for target PNR is not holded")) << endl;
      return NULL;
    }
    if (!resPtr->tickets.empty()) {
      cerr << BOLD(FRED("Offer already has tickets")) << endl;
      return NULL;
    }
    if (resPtr->status != "BOOKED") {
      cerr << BOLD(FRED("Offer is not booked")) << endl;
      return NULL;
    } else {
      string request = "/ticket?pnr=" + resPtr->pnr;
      string response = _httpClient->get(request);

      TiXmlDocument doc;
      doc.Parse((const char *)response.c_str(), 0, TIXML_ENCODING_UTF8);

      TiXmlElement *rootElement = doc.RootElement();

      if (NULL != rootElement) {
        TiXmlElement *pnr =
            rootElement->FirstChildElement()->FirstChildElement("pnr");
        if (NULL != pnr) {
          resPtr->status = pnr->Attribute("status");
        }

        TiXmlElement *tickets =
            rootElement->FirstChildElement()->FirstChildElement("tickets");
        if (NULL != tickets) {
          TiXmlElement *ticket = tickets->FirstChildElement("ticket");
          while (NULL != ticket) {
            resPtr->tickets[ticket->GetText()] = ticket->Attribute("status");
            ticket = ticket->NextSiblingElement("ticket");
          }
        }
        return resPtr;
      }
      return NULL;
    }
  } else {
    return NULL;
  }
}

map<string, FlightOffer> AmadeusGDS::_searchResult;
FlightOffer *AmadeusGDS::_holdedOffer;

}  // namespace core