#ifndef QFLIGHT_H
#define QFLIGHT_H

#include <QDate>
#include <QDebug>
#include <QList>
#include <QRandomGenerator>
#include <QString>
#include <QTextStream>
#include <QTime>

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
  static QDate generateDate();
  static QTime generateTime();

 public:
  static QFlight* generateRandomFlight();

  QFlight(QString number,
          QDate date,
          QTime time,
          QString destination,
          QString aircraft,
          quint32 seats,
          QString intermediate);
  QFlight() = default;
  QFlight(const QFlight& flight) = default;
  ~QFlight() = default;

  QString number;
  QDate date;
  QTime time;
  QString destination;
  QString aircraft;
  quint32 seats;
  QString intermediate;
};

QTextStream& operator>>(QTextStream& in, QFlight& flight);
QTextStream& operator<<(QTextStream& out, const QFlight& flight);

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
    "Москва",  "Санкт-Петербург", "Новосибирск", "Екатеринбург",
    "Казань",  "Железногорск",    "Челябинск",   "Самара",
    "Омск",    "Ростов-на-Дону",  "Уфа",         "Красноярск",
    "Пермь",   "Воронеж",         "Волгоград",   "Краснодар",
    "Саратов", "Тюмень",          "Тольятти",    "Ижевск"};

const QStringList intermediate = {"NULL",       "Ярославль",   "Иркутск",
                                  "Барнаул",    "Владивосток", "Хабаровск",
                                  "Ставрополь", "Сочи",        "Калининград",
                                  "Тула",       "Архангельск", "Горонозаводск"};
}  // namespace flightOptions

#endif  // QFLIGHT_H
