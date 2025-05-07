#include "chartswrapper.h"

ChartsWrapper::ChartsWrapper(QList<QFlight>& flights, QWidget* parent)
    : flights(flights), QWidget{parent} {
  chartChooser = new QComboBox();
  chartChooser->addItems({"Круговая", "Столбчатая", "График"});
  stackedCharts = new QStackedWidget();

  createCharts();

  layout = new QGridLayout(this);
  layout->addWidget(chartChooser);
  layout->addWidget(stackedCharts);
  connect(chartChooser, &QComboBox::activated, stackedCharts,
          &QStackedWidget::setCurrentIndex);
}

void ChartsWrapper::createCharts() {
  circleChart = new CircleChart(flights);
  barChart = new BarChart(flights);
  lineChart = new LineChart(flights);

  stackedCharts->addWidget(circleChart->chartView);
  stackedCharts->addWidget(barChart->chartView);
  stackedCharts->addWidget(lineChart->chartView);
}

void ChartsWrapper::updateCharts() {
  circleChart->createSeries();
  barChart->createSeries();
  lineChart->createSeries();
}
