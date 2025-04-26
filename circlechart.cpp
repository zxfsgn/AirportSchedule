#include "circlechart.h"

CircleChart::CircleChart(Flight* flights,
                         size_t& flightsAmount,
                         QWidget* parent)
    : flights(flights), flightsAmount(flightsAmount), QWidget(parent) {
  const int aircraftColumn = 5 - 1;
  criteriaSum = new CriteriaSum(flights, flightsAmount, aircraftColumn);
  flightsMap = criteriaSum->getSums();
  auto backButton = new QPushButton;
  backButton->setText("Закрыть");
  auto series = new QPieSeries();
  for (const auto& [aircraft, amount] : flightsMap) {
    auto slice = new QPieSlice(QString::fromStdWString(aircraft), amount);
    // auto color = new QColor("red");
    // auto brush = new QBrush(static_cast<Qt::GlobalColor>(i));
    // slice->setBrush(*brush);
    series->append(slice);
  }
  series->setLabelsVisible(true);

  chart = new QChart;
  chart->addSeries(series);
  chart->createDefaultAxes();
  chart->setVisible(true);
  chart->setTitle("Количество вылетов");
  chart->setAnimationOptions(QChart::AllAnimations);

  chartView = new QChartView(chart);
  chartView->setRenderHint(QPainter::Antialiasing);
  chartView->setVisible(true);

  auto layout = new QVBoxLayout(this);
  layout->addWidget(backButton);
  layout->addWidget(chartView);
  connect(backButton, SIGNAL(clicked()), this, SLOT(close()));
  createChart();
}

CircleChart::~CircleChart() {
  delete criteriaSum;
  delete chart;
  delete chartView;
}

void CircleChart::createChart() {}

void CircleChart::Hide() {
  chartView->close();
}
