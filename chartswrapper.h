#ifndef CHARTSWRAPPER_H
#define CHARTSWRAPPER_H

#include <QComboBox>
#include <QGridLayout>
#include <QStackedWidget>
#include <QWidget>

#include "barchart.h"
#include "circlechart.h"
#include "linechart.h"
#include "qflight.h"

class ChartsWrapper : public QWidget {
  Q_OBJECT
 public:
  explicit ChartsWrapper(QList<QFlight>& flights, QWidget* parent = nullptr);
  CircleChart* circleChart;
 public slots:
  void updateCharts();
 signals:
 private:
  QList<QFlight>& flights;
  QGridLayout* layout;
  QComboBox* chartChooser;

  BarChart* barChart;
  LineChart* lineChart;
  QStackedWidget* stackedCharts;

  void createCharts();
};

#endif  // CHARTSWRAPPER_H
