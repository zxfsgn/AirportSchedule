#ifndef TABLE_H
#define TABLE_H

#include <QButtonGroup>
#include <QCheckBox>
#include <QDebug>
#include <QFont>
#include <QGraphicsOpacityEffect>
#include <QHeaderView>
#include <QList>
#include <QMessageBox>
#include <QPropertyAnimation>
#include <QRadioButton>
#include <QSortFilterProxyModel>
#include <QString>
#include <QStringList>
#include <QStyledItemDelegate>
#include <QTableView>

#include "flighttablemodel.h"
#include "qflight.h"
#include "tabledelegate.h"
#include "tablefilterproxy.h"

#include <algorithm>

class Table : public QTableView {
  Q_OBJECT
 public:
  explicit Table(QList<QFlight>& flights, QWidget* parent = nullptr);

  FlightTableModel* model() const { return m_model; }
  TableFilterProxy* proxyModel() const { return m_proxyModel; }

 public slots:
  void deleteSelectedRows();
  void addRow();
  void filterController(QAbstractButton* button, bool checked);
  void switchVisibilityLastColumn(bool show);
  void dateFilterController(const QDate& date, bool add);

 private:
  QList<QFlight>& flights;
  FlightTableModel* m_model;
  TableFilterProxy* m_proxyModel;

  QStringList* headers;
  TableDelegate* delegate;

  void createProxy();
  void setStyles();
};

#endif  // TABLE_H
