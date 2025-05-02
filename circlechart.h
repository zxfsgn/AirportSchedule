#ifndef CIRCLECHART_H
#define CIRCLECHART_H

#include <QPieSeries>

#include "flightschart.h"

class CircleChart : public FlightsChart {
  Q_OBJECT

 public:
  explicit CircleChart(QList<QFlight> flights,
                       QColumns column = QColumns::Aircraft,
                       QGraphicsItem* parent = nullptr);

 private:
  void createSeries();
};

#endif  // CIRCLECHART_H
