#ifndef TABLEFILTERPROXY_H
#define TABLEFILTERPROXY_H

#include <type_traits>

#include <QDate>
#include <QDebug>
#include <QSortFilterProxyModel>
#include <QTime>

#include "flighttablemodel.h"

struct Filters {
  static const int filtersAmount = 6;
  QList<QDate> date;
  QTime time;
  QStringList destination;
  QStringList aircraft;
  int seats = -1;
  QStringList intermediate;
};

class TableFilterProxy : public QSortFilterProxyModel {
  Q_OBJECT
 public:
  explicit TableFilterProxy(QObject* parent = nullptr);

  void setFilters(const Filters& filters);
  Filters& filters();
  const Filters& filters() const;

 protected:
  bool filterAcceptsRow(int sourceRow,
                        const QModelIndex& sourceParent) const override;

 private:
  Filters m_filters;

  template <typename T, typename U>
  bool isCellMatch(T& data, U Filters::*pFilter) const {
    const int seatsRange = 100;
    const QTime timeRange{7, 59};
    const int secsRange = timeRange.hour() * 3600 + timeRange.minute() * 60;
    const U filter = filters().*pFilter;

    if constexpr (std::is_same_v<T, quint32>) {
      return filter == -1 || data >= filter && data <= filter + seatsRange;
    }
    if constexpr (std::is_same_v<T, QString> || std::is_same_v<T, QDate>) {
      return filter.isEmpty() || filter.contains(data);
    }

    if constexpr (std::is_same_v<T, QTime>) {
      return !filter.isValid() ||
             data >= filter && data <= filter.addSecs(secsRange);
    }
    return false;
  }
};

#endif  // TABLEFILTERPROXY_H
