#include "barchart.h"

BarChart::BarChart(Flight* flights, size_t& flightsAmount, QWidget* parent)
    : flights(flights), flightsAmount(flightsAmount), QWidget{parent} {
  auto backButton = new QPushButton;
  backButton->setText("Закрыть");

  const int destinationColumn = 4 - 1;
  criteriaSum = new CriteriaSum(flights, flightsAmount, destinationColumn);
  flightsMap = criteriaSum->getSums();

  connect(backButton, SIGNAL(clicked(bool)), this, SLOT(close()));

  auto series = new QBarSeries();
  for (const auto& [destination, amount] : flightsMap) {
    auto set = new QBarSet(QString::fromStdWString(destination));
    *set << amount;
    // auto color = new QColor("red");
    // auto brush = new QBrush(static_cast<Qt::GlobalColor>(i));
    // slice->setBrush(*brush);
    series->append(set);
  }
  series->setLabelsVisible(true);

  auto chart = new QChart;
  // QRectF rect(0,0,700,700);
  // chart->setPlotArea(rect);
  chart->addSeries(series);
  chart->createDefaultAxes();
  chart->setVisible(true);
  chart->setTitle("Количество вылетов");
  chart->setAnimationOptions(QChart::AllAnimations);

  chartView = new QChartView(chart);
  chartView->setMinimumSize(1000, 500);
  chartView->setRenderHint(QPainter::Antialiasing);
  chartView->setVisible(true);

  auto layout = new QVBoxLayout(this);
  layout->addWidget(backButton);
  layout->addWidget(chartView);
}

void BarChart::Hide() {
  chartView->setVisible(false);
}
