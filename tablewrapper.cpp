#include "tablewrapper.h"

TableWrapper::TableWrapper(Flight* flights,
                           size_t& flightsAmount,
                           QWidget* parent)
    : flights(flights), flightsAmount(flightsAmount), QWidget{parent} {
  // layout = new QVBoxLayout(this);
  // table = new Table(flights, flightsAmount);
  // layout->addWidget(table);
}
