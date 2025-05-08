#ifndef BARCHART_H
#define BARCHART_H

#include <QBarSeries>
#include <QBarSet>

#include "flightschart.h"

class BarChart : public FlightsChart {
  Q_OBJECT
 public:
  explicit BarChart(QList<QFlight>& flights,
                    QColumns column = QColumns::Destination,
                    QGraphicsItem* parent = nullptr);

  void createSeries();

 private:
};

#endif  // BARCHART_H
