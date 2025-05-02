#ifndef FLIGHTSCHART_H
#define FLIGHTSCHART_H

#include <QChart>
#include <QChartView>
#include <QList>

#include "flightsfilter.h"
#include "qflight.h"

class FlightsChart : public QChart {
  Q_OBJECT

 public:
  explicit FlightsChart(QList<QFlight> flights,
                        QColumns column,
                        QGraphicsItem* parent = nullptr);

  QChartView* chartView;

 protected:
  QList<QFlight> flights;
  QColumns column;
  FlightsFilter* filter;
  //??TEMPLATE??
  QHash<QString, int> flightsHash;

  void createSeries() {}
  void customizeChart();
  void customizeView();
};

#endif
