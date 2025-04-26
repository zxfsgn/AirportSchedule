#ifndef CIRCLECHART_H
#define CIRCLECHART_H

#include <QChart>
#include <QChartView>
#include <QPieSeries>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <map>
#include <string>

#include "../CMAKESRC/CriteriaSum/criteriasum.h"
#include "../CMAKESRC/Flight/Flight.h"

namespace Ui {
class CircleChart;
}

using std::map;
using std::wstring;

class CircleChart : public QWidget {
  Q_OBJECT

 public:
  explicit CircleChart(Flight* flights,
                       size_t& flightsAmount,
                       QWidget* parent = nullptr);
  // set mainwindow as parent and then remove fckng flights and amount
  // but perhaps it won't derive parent's fields, anyway i can try to
  // make them protected. need to get difference between parent as
  // parameter and inherited parent
  ~CircleChart();

  void Hide();
  void createChart();

  QChartView* chartView;
  QChart* chart;

 private:
  Flight* flights;
  size_t& flightsAmount;
  CriteriaSum* criteriaSum;
  map<wstring, int> flightsMap;
  // use parent chart and inherit it as all charts have the same fields and
  // imports
};

#endif  // CIRCLECHART_H
