#include "AmadeusExports.h"
//прописал, чтобы Visual Studio не ругалась
#include "../lib/tinyxml.h"

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
  string response = _httpClient->get(request);

  TiXmlDocument doc;
  doc.Parse((const char *)response.c_str(), 0, TIXML_ENCODING_UTF8);

  TiXmlElement *rootElement = doc.RootElement();

  ostringstream out;
  out << "AVAILABLE FLIGHTS:" << endl << "---------------------------" << endl;
  int i = 0;
  if (NULL != rootElement) {
    TiXmlElement *pricingRoute =
        rootElement->FirstChildElement()->FirstChildElement("pricing_route");
    if (NULL != pricingRoute) {
      TiXmlElement *variant = pricingRoute->FirstChildElement("variant");
      while (variant) {
        FlightOffer::Builder offerBuilder =
            FlightOffer::Builder().setUuid(std::to_string(++i));
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
        out << offer;

        variant = variant->NextSiblingElement("variant");
      }
    }
  }

  return out.str();
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

}  // namespace core