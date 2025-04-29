#include "qflight.h"

QFlight::QFlight(const Flight& flight) {
  number = flight.number;
  date = QDate::fromString(QString::fromStdWString(flight.date), "dd.MM.yy");
  if (!date.isValid()) {
    qDebug() << "Invalid date";
  }
  time = QTime::fromString(QString::fromStdWString(flight.time), "HH:mm");
  if (!time.isValid()) {
    qDebug() << "Invalid time";
  }
  destination = QString::fromStdWString(flight.destination);
  aircraft = QString::fromStdWString(flight.aircraft);
  seats = flight.seats;
  intermediate = QString::fromStdWString(flight.intermediate);
}

QFlight::QFlight(quint32 number,
                 QDate date,
                 QTime time,
                 QString destination,
                 QString aircraft,
                 quint32 seats,
                 QString intermediate)
    : number(number),
      date(date),
      time(time),
      destination(destination),
      aircraft(aircraft),
      seats(seats),
      intermediate(intermediate) {}
