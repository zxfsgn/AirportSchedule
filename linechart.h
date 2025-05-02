#ifndef LINECHART_H
#define LINECHART_H

#include <QLineSeries>

#include "flightschart.h"

class LineChart : public FlightsChart {
  Q_OBJECT

 public:
  explicit LineChart(QList<QFlight> flights,
                     QColumns column = QColumns::Date,
                     QGraphicsItem* parent = nullptr);

 private:
  QHash<QDate, int> flightsHash;
  void createSeries();
};

#endif  // LINECHART_H
