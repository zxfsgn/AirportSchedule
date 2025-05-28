#include "qflight.h"

QFlight::QFlight(QString number,
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

QTextStream& operator>>(QTextStream& in, QFlight& flight) {
  QString dateStr, timeStr;
  in >> flight.number >> dateStr >> timeStr >> flight.destination >>
      flight.aircraft >> flight.seats >> flight.intermediate;
  flight.date = QDate::fromString(dateStr, "yyyy-MM-dd");
  flight.time = QTime::fromString(timeStr, "hh:mm");
  return in;
}

QTextStream& operator<<(QTextStream& out, const QFlight& flight) {
  QString dateStr = flight.date.toString("yyyy-MM-dd");
  QString timeStr = flight.time.toString("hh:mm");
  out << flight.number << ' ' << dateStr << ' ' << timeStr << ' '
      << flight.destination << ' ' << flight.aircraft << ' ' << flight.seats
      << ' ' << flight.intermediate;
  return out;
}

QTime QFlight::generateTime() {
  int h = QRandomGenerator::global()->bounded(24);
  int m = QRandomGenerator::global()->bounded(60);
  QTime time(h, m);
  return time;
}

QDate QFlight::generateDate() {
  int y = 2025;
  int m = QRandomGenerator::global()->bounded(5, 13);
  int d =
      QRandomGenerator::global()->bounded(1, QDate(y, m, 1).daysInMonth() + 1);
  QDate date(y, m, d);
  return date;
}

QFlight* QFlight::generateRandomFlight() {
  QString number =
      "SU-" + QString::number(QRandomGenerator::global()->bounded(1000, 9999));
  QDate date = QFlight::generateDate();
  QTime time = QFlight::generateTime();
  QString destination = flightOptions::destinations.at(
      QRandomGenerator::global()->bounded(flightOptions::destinations.size()));

  QString intermediate;
  if (QRandomGenerator::global()->bounded(3) == 0) {
    intermediate =
        flightOptions::intermediate.at(QRandomGenerator::global()->bounded(
            flightOptions::intermediate.size()));
    while (intermediate == destination) {
      intermediate =
          flightOptions::intermediate.at(QRandomGenerator::global()->bounded(
              flightOptions::intermediate.size()));
    }
  } else {
    intermediate = "NULL";
  }
  quint32 seats = QRandomGenerator::global()->bounded(50, 400);
  QString aircraft = flightOptions::aircrafts.at(
      QRandomGenerator::global()->bounded(flightOptions::aircrafts.size()));
  QFlight* newFlight = new QFlight(number, date, time, destination, aircraft,
                                   seats, intermediate);
  return newFlight;
}
