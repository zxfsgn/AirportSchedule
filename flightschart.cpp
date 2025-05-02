#include "flightschart.h"

FlightsChart::FlightsChart(QList<QFlight> flights,
                           QColumns column,
                           QGraphicsItem* parent)
    : column(column), QChart{parent} {
  filter = new FlightsFilter(flights, column);
  // remake FLIGHTSHASH  through template somehow
  // flightsHash = filter->filteredFlights<QString>();

  customizeChart();
  customizeView();
}

void FlightsChart::customizeChart() {
  createDefaultAxes();
  setVisible(true);
  setTitle("Количество вылетов");
  setAnimationOptions(QChart::AllAnimations);
}

void FlightsChart::customizeView() {
  chartView = new QChartView(this);
  chartView->setRenderHint(QPainter::Antialiasing);
  chartView->setVisible(true);
}
