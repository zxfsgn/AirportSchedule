#ifndef CIRCLECHART_H
#define CIRCLECHART_H

#include <QComboBox>
#include <QGraphicsDropShadowEffect>
#include <QGraphicsEffect>
#include <QGridLayout>
#include <QLineEdit>
#include <QPieSeries>
#include <QToolTip>

#include "flightschart.h"

class CircleChart : public FlightsChart {
  Q_OBJECT

 public:
  explicit CircleChart(QList<QFlight>& flights,
                       QColumns column = QColumns::Aircraft,
                       QGraphicsItem* parent = nullptr);

 public slots:
  void createSeries();
  void highlightSlice(QPieSlice* selectedSlice);

 private:
  // QString selectedAircraft;
  QPieSeries* series;
  QComboBox* aircraftSelector;

  void setSelector();
  void setAnimation();

  QList<QString> possibleAircrafts = {"А320",
                                      "Boeing737",
                                      "B737NG",
                                      "Bombardier_Dash-8",
                                      "Sukhoi_Superjet_100",
                                      "Embraer",
                                      "Boeing777",
                                      "Ан-24"};
};

#endif  // CIRCLECHART_H
