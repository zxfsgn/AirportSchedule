#include "barchart.h"

BarChart::BarChart(QList<QFlight>& flights,
                   QColumns column,
                   QGraphicsItem* parent)
    : FlightsChart(flights, column, parent) {
  flightsHash = filter->filteredFlights<QString>();
  createSeries();
}

void BarChart::createSeries() {
  removeAllSeries();
  flightsHash = filter->filteredFlights<QString>();
  auto newSeries = new QBarSeries();
  for (const auto& destination : flightsHash.keys()) {
    auto set = new QBarSet(destination);
    *set << flightsHash[destination];
    // auto color = new QColor("red");
    // auto brush = new QBrush(static_cast<Qt::GlobalColor>(i));
    // slice->setBrush(*brush);
    newSeries->append(set);
  }
  newSeries->setLabelsVisible(true);
  addSeries(newSeries);
}

// void BarChart::update(QList<QFlight> flights){

// }
