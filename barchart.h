#ifndef BARCHART_H
#define BARCHART_H

#include <QBarSeries>
#include <QBarSet>
#include <QChart>
#include <QPushButton>
#include <QRectF>
#include <QVBoxLayout>
#include <QWidget>
#include <map>
#include <string>

#include "chartview.h"

#include "../CMAKESRC/CriteriaSum/criteriasum.h"
#include "../CMAKESRC/Flight/Flight.h"

using std::map;
using std::wstring;

class BarChart : public QWidget {
  Q_OBJECT
 public:
  explicit BarChart(Flight* flights,
                    size_t& flightsAmount,
                    QWidget* parent = nullptr);
  void Hide();

 private:
  Flight* flights;
  size_t& flightsAmount;
  CriteriaSum* criteriaSum;
  map<wstring, int> flightsMap;
  // use parent chart and inherit it as all charts have the same fields

  QChartView* chartView;
};

#endif  // BARCHART_H
