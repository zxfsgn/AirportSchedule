#ifndef FLIGHTSFILTER_H
#define FLIGHTSFILTER_H

#include <type_traits>

#include <QList>
#include <QMap>

#include "qflight.h"

class FlightsFilter {
 public:
  FlightsFilter(QList<QFlight>& flights, QColumns column);

  template <typename T>
  QMap<T, int> filteredFlights() {
    int flightsAmount = flights.size();
    QMap<T, int> flightsHash;
    for (size_t i = 0; i < flightsAmount; ++i) {
      ++flightsHash[getFieldByColumn<T>(i)];
    }
    return flightsHash;
  }
  QList<QFlight>& flights;

 private:
  QColumns column;

  template <typename T>
  T getFieldByColumn(int index) {
    switch (column) {
      case QColumns::Aircraft:
        if constexpr (std::is_same_v<T, QString>)
          return flights[index].aircraft;
        break;
      case QColumns::Destination:
        if constexpr (std::is_same_v<T, QString>)
          return flights[index].destination;
        break;
      case QColumns::Intermediate:
        if constexpr (std::is_same_v<T, QString>)
          return flights[index].intermediate;
        break;
      case QColumns::Date:
        if constexpr (std::is_same_v<T, int>)
          return flights[index].date.month();
        break;
      default:
        break;
    }
    return T();
  }
};

#endif  // FLIGHTSFILTER_H
