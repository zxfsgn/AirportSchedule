#include "tablefilterproxy.h"

TableFilterProxy::TableFilterProxy(QObject* parent)
    : QSortFilterProxyModel{parent} {
  setFilters(Filters());
}

void TableFilterProxy::setFilters(const Filters& newFilters) {
  m_filters = newFilters;
  invalidateFilter();
}

const Filters& TableFilterProxy::filters() const {
  return m_filters;
}

Filters& TableFilterProxy::filters() {
  return m_filters;
}

bool TableFilterProxy::filterAcceptsRow(int sourceRow,
                                        const QModelIndex& sourceParent) const {
  int i = 0;
  if (!QSortFilterProxyModel::filterAcceptsRow(sourceRow, sourceParent))
    return false;
  // if (!sourceModel())
  //   return false;
  QFlight rowFlight{
      0,
      sourceModel()
          ->data(sourceModel()->index(sourceRow, ++i, sourceParent))
          .toDate(),
      sourceModel()
          ->data(sourceModel()->index(sourceRow, ++i, sourceParent))
          .toTime(),
      sourceModel()
          ->data(sourceModel()->index(sourceRow, ++i, sourceParent))
          .toString(),
      sourceModel()
          ->data(sourceModel()->index(sourceRow, ++i, sourceParent))
          .toString(),
      sourceModel()
          ->data(sourceModel()->index(sourceRow, ++i, sourceParent))
          .toUInt(),
      sourceModel()
          ->data(sourceModel()->index(sourceRow, ++i, sourceParent))
          .toString()};
  bool dateMatch =
      isCellMatch<QDate, QList<QDate>>(rowFlight.date, &Filters::date);
  bool timeMatch = isCellMatch<QTime, QTime>(rowFlight.time, &Filters::time);
  bool destinationMatch = isCellMatch<QString, QList<QString>>(
      rowFlight.destination, &Filters::destination);
  bool aircraftMatch = isCellMatch<QString, QList<QString>>(rowFlight.aircraft,
                                                            &Filters::aircraft);
  bool seatsMatch = isCellMatch<quint32, int>(rowFlight.seats, &Filters::seats);
  bool intermediateMatch = isCellMatch<QString, QList<QString>>(
      rowFlight.intermediate, &Filters::intermediate);

  return dateMatch && timeMatch && destinationMatch && aircraftMatch &&
         seatsMatch && intermediateMatch;
}
