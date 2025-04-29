#ifndef TABLE_H
#define TABLE_H

#include <QDebug>
#include <QFont>
#include <QHeaderView>
#include <QList>
#include <QString>
#include <QStringList>
#include <QStyledItemDelegate>
#include <QTableView>

#include "flighttablemodel.h"
#include "qflight.h"
#include "tabledelegate.h"

#include <algorithm>

class Table : public QTableView {
  Q_OBJECT
 public:
  explicit Table(QList<QFlight>& flights, QWidget* parent = nullptr);

  FlightTableModel* model() const { return m_model; }

 public slots:
  void deleteSelectedRows();
  void addRow();

 private:
  QList<QFlight>& flights;
  FlightTableModel* m_model;

  QStringList* headers;
  TableDelegate* delegate;
};

#endif  // TABLE_H
