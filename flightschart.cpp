#include "flightschart.h"

FlightsChart::FlightsChart(QList<QFlight>& flights,
                           QColumns column,
                           QGraphicsItem* parent)
    : flights(flights), column(column), QChart{parent} {
  filter = new FlightsFilter(flights, column);
  // connect(model, &FlightTableModel::dataChanged, this,
  //         &FlightsChart::createSeries);
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

// void FlightsChart::initializeModel(FlightTableModel* newModel) {
//   model = newModel;
// }
