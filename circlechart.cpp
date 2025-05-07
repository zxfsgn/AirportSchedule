#include "circlechart.h"

CircleChart::CircleChart(QList<QFlight>& flights,
                         QColumns column,
                         QGraphicsItem* parent)
    : FlightsChart(flights, column, parent) {
  createSeries();
  // setSelector();
  setAnimation();
  connect(series, &QPieSeries::clicked, this, &CircleChart::highlightSlice);
  // aircraftSelector->textActivated(aircraftSelector->currentText());
  legend()->setVisible(false);
}

void CircleChart::createSeries() {
  removeAllSeries();
  flightsHash = filter->filteredFlights<QString>();
  series = new QPieSeries();
  for (const auto& aircraft : flightsHash.keys()) {
    auto slice = new QPieSlice(aircraft, flightsHash[aircraft]);
    series->append(slice);
  }
  series->setLabelsVisible(true);
  addSeries(series);
  connect(series, &QPieSeries::hovered, this, &CircleChart::highlightSlice);
}

void CircleChart::setSelector() {
  // make through table and delegate
  aircraftSelector = new QComboBox();
  QGridLayout* layout = new QGridLayout();
  layout->addWidget(aircraftSelector);
  layout->setAlignment(Qt::AlignTop);
  chartView->setLayout(layout);
  aircraftSelector->insertItems(0, possibleAircrafts);
}

void CircleChart::highlightSlice(QPieSlice* selectedSlice) {
  foreach (QPieSlice* slice, series->slices()) {
    slice->setExploded(false);
    slice->setPen(QPen());
  }
  selectedSlice->setExploded(true);
  selectedSlice->setPen(QPen(Qt::blue, 4));

  QToolTip::showText(QCursor::pos(),
                     QString("%1\nValue: %2\nPercentage: %3%")
                         .arg(selectedSlice->label())
                         .arg(selectedSlice->value())
                         .arg(selectedSlice->percentage() * 100, 0, 'f', 1));
}

void CircleChart::setAnimation() {
  QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect;
  effect->setBlurRadius(15);
  effect->setColor(Qt::yellow);
  effect->setOffset(0);
  chartView->setGraphicsEffect(effect);
}
