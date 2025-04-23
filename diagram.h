#ifndef DIAGRAM_H
#define DIAGRAM_H

#include <QChart>
#include <QPieSeries>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <map>
#include <string>

#include "chartview.h"

#include "../CMAKESRC/CriteriaSum/criteriasum.h"
#include "../CMAKESRC/Flight/Flight.h"

namespace Ui {
class Diagram;
}

using std::map;
using std::wstring;

class Diagram : public QWidget {
  Q_OBJECT

 public:
  explicit Diagram(Flight* flights,
                   size_t& flightsAmount,
                   QWidget* parent = nullptr);
  // set mainwindow as parent and then remove fckng flights and amount
  // but perhaps it won't derive parent's fields, anyway i can try to
  // make them protected. need to get difference between parent as
  // parameter and inherited parent
  void Hide();
  void createChart();

  QChartView* chartView;
  QChart* chart;

  ~Diagram();

 private:
  Flight* flights;
  size_t& flightsAmount;
  CriteriaSum* criteriaSum;
  map<wstring, int> flightsMap;
  // use parent chart and inherit it as all charts have the same fields and
  // imports

  Ui::Diagram* ui;
};

#endif  // DIAGRAM_H
