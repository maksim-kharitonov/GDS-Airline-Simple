#pragma once
#ifndef FLIGHTOFFER_H
#define FLIGHTOFFER_H

#ifdef _WIN32
#define FLIGHT_OFFER_API __declspec(dllexport)
#else
#define FLIGHT_OFFER_API
#endif

#include <ostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

struct FlightOffer {
 public:
  FlightOffer(){};
  virtual ~FlightOffer(){};
  class Builder;
  struct Price {
    double amount;
    string currency;
  };
  struct OriginDestination {
    string departurePort;
    string arrivalPort;
    string departureDate;
    string arrivalDate;
    string departureTime;
    string arrivalTime;
    string bookingClass;
    string operatingCarrier;
    string marketingCarrier;
    string basicFareCode;
    OriginDestination(const string departurePort, const string arrivalPort,
                      const string departureDate, const string arrivalDate,
                      const string departureTime, const string arrivalTime,
                      const string bookingClass, const string operatingCarrier,
                      const string marketingCarrier, const string basicFareCode)
        : departurePort(departurePort),
          arrivalPort(arrivalPort),
          departureDate(departureDate),
          arrivalDate(arrivalDate),
          departureTime(departureTime),
          arrivalTime(arrivalTime),
          bookingClass(bookingClass),
          operatingCarrier(operatingCarrier),
          marketingCarrier(marketingCarrier),
          basicFareCode(basicFareCode) {}

    class Builder;
  };
  string gds;
  string uuid;
  string generalCarrier;
  Price totalPrice;
  vector<OriginDestination> flights;

  string toString();

  FlightOffer(const string gds, const string uuid, const string generalCarrier,
              const Price totalPrice, const vector<OriginDestination> flights)
      : gds(gds),
        uuid(uuid),
        generalCarrier(generalCarrier),
        totalPrice(totalPrice),
        flights(flights){};
};

class FlightOffer::Builder {
 private:
  string gds;
  string uuid;
  string generalCarrier;
  Price totalPrice;
  vector<OriginDestination> flights;

 public:
  Builder()
      : gds("---"),
        uuid("---"),
        generalCarrier("---"),
        totalPrice(),
        flights() {}

  Builder &setGds(const string &gds);
  Builder &setUuid(const string &uuid);
  Builder &setGeneralCarrier(const string &generalCarrier);
  Builder &setPrice(const string &price);
  Builder &setPrice(const double price);
  Builder &setCurrency(const string &currency);
  Builder &addFlight(const OriginDestination &flight);

  FlightOffer build();
};

class FlightOffer::OriginDestination::Builder {
 private:
  string departurePort;
  string arrivalPort;
  string departureDate;
  string arrivalDate;
  string departureTime;
  string arrivalTime;
  string bookingClass;
  string operatingCarrier;
  string marketingCarrier;
  string basicFareCode;

 public:
  Builder()
      : departurePort("---"),
        arrivalPort("---"),
        departureDate("00.00.00"),
        arrivalDate("00.00.00"),
        departureTime("00:00"),
        arrivalTime("00:00"),
        bookingClass("---"),
        operatingCarrier("---"),
        marketingCarrier("---"),
        basicFareCode("---"){};
  Builder &setDeparturePort(const string &departurePort);
  Builder &setArrivalPort(const string &arrivalPort);
  Builder &setDepartureDate(const string &departureDate);
  Builder &setArrivalDate(const string &arrivalDate);
  Builder &setDepartureTime(const string &departureTime);
  Builder &setArrivalTime(const string &arrivalTime);
  Builder &setBookingClass(const string &bookingClass);
  Builder &setOperatingCarrier(const string &operatingCarrier);
  Builder &setMarketingCarrier(const string &marketingCarrier);
  Builder &setBasicFareCode(const string &basicFareCode);
  FlightOffer::OriginDestination build();
};

FLIGHT_OFFER_API ostream &operator<<(ostream &stream,
                                     const FlightOffer &flightOffer);
ostream &operator<<(ostream &stream,
                    const FlightOffer::OriginDestination &originDestination);
ostream &operator<<(ostream &stream, const FlightOffer::Price &price);

struct Reservation : public FlightOffer {
  ~Reservation(){};
  string pnr;
  string status;
  Reservation(FlightOffer const &offer, const string &pnr, const string &status)
      : FlightOffer(offer), pnr(pnr), status(status){};
};

FLIGHT_OFFER_API ostream &operator<<(ostream &stream,
                                     const Reservation &reservation);

#endif  // !FLIGHTOFFER_H
