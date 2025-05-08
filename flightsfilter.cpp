#include "flightsfilter.h"

FlightsFilter::FlightsFilter(QList<QFlight>& flights, QColumns column)
    : flights(flights), column(column) {}
