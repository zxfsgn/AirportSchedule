#include "linechart.h"

LineChart::LineChart(Flight* flights, size_t& flightsAmount, QWidget* parent)
    : flights(flights), flightsAmount(flightsAmount), QWidget{parent} {
  const int dateColumn = 2 - 1;
  criteriaSum = new CriteriaSum(flights, flightsAmount, dateColumn);
  flightsMap = criteriaSum->getSums();

  auto backButton = new QPushButton;
  backButton->setText("Закрыть");

  connect(backButton, SIGNAL(clicked(bool)), this, SLOT(close()));

  auto series = new QLineSeries();
  int i = 0;
  for (const auto& [date, amount] : flightsMap) {
    // auto color = new QColor("red");
    // auto brush = new QBrush(static_cast<Qt::GlobalColor>(i));
    // slice->setBrush(*brush);
    series->append(QString::fromStdWString(date).toInt(), amount);
  }
  // series->setLabelsVisible(true);

  auto chart = new QChart;
  // QRectF rect(0,0,700,700);
  // chart->setPlotArea(rect);
  chart->addSeries(series);
  chart->createDefaultAxes();
  chart->setVisible(true);
  chart->setTitle("Количество вылетов по месяцам");
  chart->setAnimationOptions(QChart::AllAnimations);

  chartView = new QChartView(chart);
  chartView->setMinimumSize(1000, 500);
  chartView->setRenderHint(QPainter::Antialiasing);
  chartView->setVisible(true);

  auto layout = new QVBoxLayout(this);
  layout->addWidget(backButton);
  layout->addWidget(chartView);
}
