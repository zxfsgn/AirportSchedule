#include "linechart.h"

LineChart::LineChart(QList<QFlight> flights,
                     QColumns column,
                     QGraphicsItem* parent)
    : FlightsChart(flights, column, parent) {
  flightsHash = filter->filteredFlights<QDate>();
  createSeries();
}

void LineChart::createSeries() {
  auto series = new QLineSeries();
  int i = 0;
  for (const auto& date : flightsHash.keys()) {
    // auto color = new QColor("red");
    // auto brush = new QBrush(static_cast<Qt::GlobalColor>(i));
    // slice->setBrush(*brush);
    series->append(date.month(), flightsHash[date]);
  }
  addSeries(series);
}
