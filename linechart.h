#ifndef LINECHART_H
#define LINECHART_H

#include <algorithm>

#include <QCategoryAxis>
#include <QLineSeries>
#include <QMap>
#include <QValueAxis>

#include "flightschart.h"

class LineChart : public FlightsChart {
  Q_OBJECT

 public:
  explicit LineChart(QList<QFlight>& flights,
                     QColumns column = QColumns::Date,
                     QGraphicsItem* parent = nullptr);

  void createSeries();
  void createAxis();

 private:
  QMap<int, int> flightsHash;
  QLineSeries* series;
  QCategoryAxis* axisX;
  QValueAxis* axisY;
};

#endif  // LINECHART_H
