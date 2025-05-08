#ifndef QFLIGHT_H
#define QFLIGHT_H

#include <QDate>
#include <QDebug>
#include <QList>
#include <QString>
#include <QTime>

#include "../CMAKESRC/Flight/Flight.h"

enum class QColumns {
  Number,
  Date,
  Time,
  Destination,
  Aircraft,
  Seats,
  Intermediate,
  COLUMN_COUNT
};

class QFlight {
 public:
  QFlight(const Flight& flight);
  QFlight(quint32 number,
          QDate date,
          QTime time,
          QString destination,
          QString aircraft,
          quint32 seats,
          QString intermediate);
  QFlight() = default;
  QFlight(const QFlight& flight) = default;
  ~QFlight() = default;

  quint32 number;
  QDate date;
  QTime time;
  QString destination;
  QString aircraft;
  quint32 seats;
  QString intermediate;
};

namespace flightOptions {
const QStringList aircrafts = {"А320",
                               "Boeing737",
                               "B737NG",
                               "Bombardier_Dash-8",
                               "Sukhoi_Superjet_100",
                               "Embraer",
                               "Boeing777",
                               "Ан-24"};

const QStringList destinations = {
    "Хабаровск",       "Железногорск", "Горнозаводск", "Москва",
    "Санкт-Петербург", "Красноярск",   "Псков",        "Новосибирск"};
}  // namespace flightOptions

#endif  // QFLIGHT_H
