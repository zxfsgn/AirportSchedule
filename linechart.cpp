#include "linechart.h"
#include <QDebug>

LineChart::LineChart(QList<QFlight>& flights,
                     QColumns column,
                     QGraphicsItem* parent)
    : FlightsChart(flights, column, parent) {
  createAxis();
  createSeries();
}

void LineChart::createSeries() {
  removeAllSeries();
  series = new QLineSeries();
  flightsHash = filter->filteredFlights<int>();
  for (int i = 1; i < 13; ++i) {
    if (!flightsHash.contains(i)) {
      flightsHash[i] = 0;
    }
  }

  QList<int> sortedKeys = flightsHash.keys();
  std::sort(sortedKeys.begin(), sortedKeys.end());

  for (const auto& monthNumber : sortedKeys) {
    series->append(monthNumber, flightsHash[monthNumber]);
  }
  QList<int> values = flightsHash.values();
  int maxValue = *std::max_element(values.begin(), values.end());

  axisY->setRange(0, maxValue + 1);
  axisY->setTickCount(maxValue + 2);

  QPen pen(Qt::blue);
  pen.setWidth(3);
  series->setPen(pen);

  addSeries(series);
  series->attachAxis(axisX);
  series->attachAxis(axisY);
}

void LineChart::createAxis() {
  axisX = new QCategoryAxis();
  axisY = new QValueAxis();

  // Configure X axis (months)
  axisX->setTitleText("Месяц");
  axisX->setRange(0, 12);
  axisX->setTickCount(12);
  for (int i = 1; i < 13; ++i) {
    QDate date(2000, i, 1);
    QString month = date.toString("MMM");
    axisX->append(month, i);
  }

  // Configure Y axis (flight count)
  axisY->setTitleText("Количество вылетов");

  // Add axes to chart

  addAxis(axisX, Qt::AlignBottom);
  addAxis(axisY, Qt::AlignLeft);
}
