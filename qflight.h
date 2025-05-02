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

  // template <typename T>
  // T operator[](QColumns column) {
  //   switch (column) {
  //     case Columns::Number:
  //       if constexpr (typeid(T) == typeid(quint32)) {
  //         return number;
  //       }
  //       break;
  //     case Columns::Date:
  //       if constexpr (typeid(T) == typeid(QDate)) {
  //         return date;
  //       }
  //       break;
  //     case Columns::Time:
  //       if constexpr (typeid(T) == typeid(QTime)) {
  //         return time;
  //         number;
  //       }
  //       break;
  //     case Columns::Destination:
  //       if constexpr (typeid(T) == typeid(QString)) {
  //         return destination;
  //       }
  //       break;
  //     case Columns::Aircraft:
  //       if constexpr (typeid(T) == typeid(QString)) {
  //         return aircraft;
  //       }

  //       break;
  //     case Columns::Seats:
  //       if constexpr (typeid(T) == typeid(quint32)) {
  //         return seats;
  //       };
  //       break;
  //     case Columns::Intermediate:
  //       if constexpr (typeid(T) == typeid(QString)) {
  //         return intermediate;
  //       }
  //       break;
  //     default:
  //       break;
  //   }
  //   return T();
  // }
};

#endif  // QFLIGHT_H
