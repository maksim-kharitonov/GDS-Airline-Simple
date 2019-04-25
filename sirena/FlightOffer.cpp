#include "FlightOffer.h"

std::ostream &operator<<(ostream &stream, const Reservation &reservation) {
  stream << "PNR: " << reservation.pnr << " " << reservation.status << endl;
  if (!reservation.tickets.empty()) {
    stream << "TICKETS:" << endl;
    for (auto ticket = reservation.tickets.cbegin();
         ticket != reservation.tickets.cend();
         ++ticket) {
      stream << ticket->first << " " << ticket->second << endl;
    }
  }
  stream << static_cast<const FlightOffer &>(reservation) << endl;
  return stream;
}

std::ostream &__cdecl operator<<(std::ostream &stream,
                                 const FlightOffer &offer) {
  stream << offer.gds << " " << offer.uuid << " " << offer.generalCarrier
         << endl;

  for (std::vector<FlightOffer::OriginDestination>::const_iterator flight =
           offer.flights.begin();
       flight != offer.flights.end(); ++flight) {
    stream << *flight << endl;
  }

  stream << offer.totalPrice << endl
         << "--------------------------------" << endl;

  return stream;
}

std::ostream &__cdecl operator<<(std::ostream &stream,
                                 const FlightOffer::Price &price) {
  return stream << price.amount << " " << price.currency;
}

std::ostream &__cdecl operator<<(
    ostream &stream, const FlightOffer::OriginDestination &originDestination) {
  return stream << originDestination.marketingCarrier << " "
                << originDestination.departurePort << " "
                << "[" << originDestination.departureTime << "]"
                << " - " << originDestination.arrivalPort << "["
                << originDestination.arrivalTime << "]"
                << " " << originDestination.bookingClass << " "
                << originDestination.basicFareCode;
}

FlightOffer::Builder &FlightOffer::Builder::setGds(const string &gds) {
  this->gds = gds;
  return *this;
}

FlightOffer::Builder &FlightOffer::Builder::setUuid(const string &uuid) {
  this->uuid = uuid;
  return *this;
}

FlightOffer::Builder &FlightOffer::Builder::setGeneralCarrier(
    const string &generalCarrier) {
  this->generalCarrier = generalCarrier;
  return *this;
}

FlightOffer::Builder &FlightOffer::Builder::setPrice(const string &price) {
  size_t idx;
  this->totalPrice.amount = std::stod(price, &idx);
  return *this;
}

FlightOffer::Builder &FlightOffer::Builder::setPrice(const double price) {
  this->totalPrice.amount = price;
  return *this;
}

FlightOffer::Builder &FlightOffer::Builder::setCurrency(
    const string &currency) {
  this->totalPrice.currency = currency;
  return *this;
}

FlightOffer::Builder &FlightOffer::Builder::addFlight(
    const OriginDestination &flight) {
  this->flights.push_back(flight);
  return *this;
}

FlightOffer FlightOffer::Builder::build() {
  return FlightOffer(gds, uuid, generalCarrier, totalPrice, flights);
}

FlightOffer::OriginDestination
FlightOffer::OriginDestination::Builder::build() {
  return FlightOffer::OriginDestination(
      departurePort, arrivalPort, departureDate, arrivalDate, departureTime,
      arrivalTime, bookingClass, operatingCarrier, marketingCarrier,
      basicFareCode);
}

FlightOffer::OriginDestination::Builder &
FlightOffer::OriginDestination::Builder::setDeparturePort(
    const string &departurePort) {
  this->departurePort = departurePort;
  return *this;
}
FlightOffer::OriginDestination::Builder &
FlightOffer::OriginDestination::Builder::setArrivalPort(
    const string &arrivalPort) {
  this->arrivalPort = arrivalPort;
  return *this;
}
FlightOffer::OriginDestination::Builder &
FlightOffer::OriginDestination::Builder::setDepartureDate(
    const string &departureDate) {
  this->departureDate = departureDate;
  return *this;
}
FlightOffer::OriginDestination::Builder &
FlightOffer::OriginDestination::Builder::setArrivalDate(
    const string &arrivalDate) {
  this->arrivalDate = arrivalDate;
  return *this;
}
FlightOffer::OriginDestination::Builder &
FlightOffer::OriginDestination::Builder::setDepartureTime(
    const string &departureTime) {
  this->departureTime = departureTime;
  return *this;
}
FlightOffer::OriginDestination::Builder &
FlightOffer::OriginDestination::Builder::setArrivalTime(
    const string &arrivalTime) {
  this->arrivalTime = arrivalTime;
  return *this;
}
FlightOffer::OriginDestination::Builder &
FlightOffer::OriginDestination::Builder::setBookingClass(
    const string &bookingClass) {
  this->bookingClass = bookingClass;
  return *this;
}
FlightOffer::OriginDestination::Builder &
FlightOffer::OriginDestination::Builder::setOperatingCarrier(
    const string &operatingCarrier) {
  this->operatingCarrier = operatingCarrier;
  return *this;
}
FlightOffer::OriginDestination::Builder &
FlightOffer::OriginDestination::Builder::setMarketingCarrier(
    const string &marketingCarrier) {
  this->marketingCarrier = marketingCarrier;
  return *this;
}
FlightOffer::OriginDestination::Builder &
FlightOffer::OriginDestination::Builder::setBasicFareCode(
    const string &basicFareCode) {
  this->basicFareCode = basicFareCode;
  return *this;
}

string FlightOffer::toString() {
  ostringstream out;
  out << this;
  return out.str();
}

Reservation::Builder &Reservation::Builder::setPnr(const string &pnr) {
  this->pnr = pnr;
  return *this;
}

Reservation::Builder &Reservation::Builder::setStatus(const string &status) {
  this->status = status;
  return *this;
}

Reservation::Builder &Reservation::Builder::addTicket(const string &bso,
                                         const string &status) {
  this->tickets[bso] = status;
  return *this;
}

Reservation Reservation::Builder::build() {
  return Reservation(offer, pnr, status, tickets);
}
