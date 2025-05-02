#include "circlechart.h"

CircleChart::CircleChart(QList<QFlight> flights,
                         QColumns column,
                         QGraphicsItem* parent)
    : FlightsChart(flights, column, parent) {
  flightsHash = filter->filteredFlights<QString>();
  createSeries();
}

void CircleChart::createSeries() {
  auto series = new QPieSeries();
  for (const auto& aircraft : flightsHash.keys()) {
    auto slice = new QPieSlice(aircraft, flightsHash[aircraft]);
    // auto color = new QColor("red");
    // auto brush = new QBrush(static_cast<Qt::GlobalColor>(i));
    // slice->setBrush(*brush);
    series->append(slice);
  }
  series->setLabelsVisible(true);
  addSeries(series);
}
