#ifndef LINECHART_H
#define LINECHART_H

#include <QChart>
#include <QChartView>
#include <QLineSeries>
#include <QPushButton>
#include <QRectF>
#include <QVBoxLayout>
#include <QWidget>
#include <map>
#include <string>

#include "../CMAKESRC/CriteriaSum/criteriasum.h"
#include "../CMAKESRC/Flight/Flight.h"

class LineChart : public QWidget {
  Q_OBJECT
 public:
  explicit LineChart(Flight* flights,
                     size_t& flightsAmount,
                     QWidget* parent = nullptr);

 private:
  Flight* flights;
  size_t& flightsAmount;
  CriteriaSum* criteriaSum;
  map<wstring, int> flightsMap;
  // use parent chart and inherit it as all charts have the same fields and
  // imports

  QChartView* chartView;
};

#endif  // LINECHART_H
