#ifndef FLIGHTTABLEMODEL_H
#define FLIGHTTABLEMODEL_H

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

  // Header:
  QVariant headerData(int section,
                      Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const override;

  // Basic functionality:
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

  // Add data:
  void addFlight(const QFlight& flight);
  // bool insertRows(int row,
  //                 int count,
  //                 const QModelIndex& parent = QModelIndex()) override;

  // Remove data:
  bool removeRows(int row,
                  int count,
                  const QModelIndex& parent = QModelIndex()) override;

 public slots:
  void switchEditability();

 signals:
  void editCompleted(const QString& message);

 private:
  bool isEditable = false;
  QList<QFlight>& m_flights;
  size_t m_columnAmount;
};

#endif  // FLIGHTTABLEMODEL_H
