#ifndef FLIGHTSCHART_H
#define FLIGHTSCHART_H

#include <QChartView>
#include <QList>
#include <QtCharts>

#include "flightsfilter.h"
#include "flighttablemodel.h"
#include "qflight.h"

// using namespace QtCharts;

class FlightsChart : public QChart {
  Q_OBJECT

 public:
  explicit FlightsChart(QList<QFlight>& flights,
                        QColumns column,
                        QGraphicsItem* parent = nullptr);

  QChartView* chartView;

 protected slots:
  void createSeries() {}
  // void initializeModel(FlightTableModel*);

 protected:
  // FlightTableModel* model{};
  QList<QFlight>& flights;
  QColumns column;
  FlightsFilter* filter;
  //??TEMPLATE??
  QMap<QString, int> flightsHash;

  void customizeChart();
  void customizeView();
};

#endif
