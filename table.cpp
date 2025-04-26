#include "table.h"

Table::Table(Flight* flights, size_t& flightsAmount, QWidget* parent)
    : flights(flights),
      flightsAmount(flightsAmount),
      QTableWidget(flightsAmount, 7, parent) {
  horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::Stretch);
  populateTable();
  setMinimumSize(1000, 500);
}

void Table::populateTable() {
  setRowCount(flightsAmount);
  for (int i = 0; i < flightsAmount; ++i) {
    wstring nullStr = L"NULL";
    if (flights[i].intermediate == nullStr) {
      flights[i].intermediate = L" ";
    }
    setItem(i, 0, new QTableWidgetItem(QString::number(flights[i].number)));
    setItem(i, 1,
            new QTableWidgetItem(QString::fromStdWString(flights[i].date)));
    setItem(i, 2,
            new QTableWidgetItem(QString::fromStdWString(flights[i].time)));
    setItem(
        i, 3,
        new QTableWidgetItem(QString::fromStdWString(flights[i].destination)));
    setItem(i, 4,
            new QTableWidgetItem(QString::fromStdWString(flights[i].aircraft)));
    setItem(i, 5, new QTableWidgetItem(QString::number(flights[i].seats)));
    setItem(
        i, 6,
        new QTableWidgetItem(QString::fromStdWString(flights[i].intermediate)));
  }
  hideColumn(6);
}
