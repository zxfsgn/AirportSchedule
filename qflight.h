#ifndef QFLIGHT_H
#define QFLIGHT_H

#include <QDate>
#include <QDebug>
#include <QString>
#include <QTime>
#include <string>

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

#endif  // QFLIGHT_H
