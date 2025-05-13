#ifndef FLIGHTTABLEMODEL_H
#define FLIGHTTABLEMODEL_H

#include <algorithm>

#include <QAbstractTableModel>
#include <QColor>
#include <QFont>
#include <QList>
#include <QString>
#include <QVariant>

#include "qflight.h"

class FlightTableModel : public QAbstractTableModel {
  Q_OBJECT

 public:
  explicit FlightTableModel(QList<QFlight>& flights, QObject* parent = nullptr);

  QVariant headerData(int section,
                      Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const override;

  int rowCount(const QModelIndex& parent = QModelIndex()) const override;
  int columnCount(const QModelIndex& parent = QModelIndex()) const override;

  // Fetch data dynamically:
  //

  QVariant data(const QModelIndex& index,
                int role = Qt::DisplayRole) const override;

  // Editable:
  bool setData(const QModelIndex& index,
               const QVariant& value,
               int role = Qt::EditRole) override;

  Qt::ItemFlags flags(const QModelIndex& index) const override;

  void addFlight(const QFlight& flight);

  bool removeRows(int row,
                  int count,
                  const QModelIndex& parent = QModelIndex()) override;

  void sort(int column, Qt::SortOrder order = Qt::AscendingOrder) override;

  QList<QFlight>& flights();
  QList<QFlight> defaultFlights;
 public slots:
  void switchEditability();
  void initializeDefaultFlights(QList<QFlight>);

 signals:
  void editCompleted(const QString& message);
  void created(FlightTableModel* model);

 private:
  bool isEditable = false;
  QList<QFlight>& m_flights;
  size_t m_columnAmount;
};

bool fieldCompare(QColumns column,
                  const QFlight& a,
                  const QFlight& b,
                  bool isAscending);

template <typename T>
bool valueCompare(const T& a, const T& b, bool isAscending) {
  if (isAscending)
    return a < b;
  return a > b;
}

#endif  // FLIGHTTABLEMODEL_H
