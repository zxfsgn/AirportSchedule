#include "table.h"

Table::Table(QList<QFlight>& flights, QWidget* parent)
    : flights(flights), QTableView(parent) {
  horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::Stretch);
  m_model = new FlightTableModel(flights);
  delegate = new TableDelegate(this);
  createProxy();
  setModel(proxyModel());
  setItemDelegate(delegate);
  setSelectionMode(QAbstractItemView::SingleSelection);
  setSelectionBehavior(QAbstractItemView::SelectRows);
  setMinimumSize(750, 500);
  setSortingEnabled(true);
  sortByColumn(0, Qt::AscendingOrder);
  horizontalHeader()->setSortIndicatorShown(true);
}

void Table::deleteSelectedRows() {
  QModelIndexList selected = this->selectionModel()->selectedRows();
  std::sort(selected.begin(), selected.end(),
            [](const QModelIndex& a, const QModelIndex& b) {
              return a.row() > b.row();
            });
  for (const QModelIndex& index : selected) {
    model()->removeRows(index.row(), 1);
  }
}

void Table::addRow() {
  model()->addFlight(*(new QFlight()));
  QModelIndex index = model()->index(flights.size() - 1, 0);
  // selectionModel()->setCurrentIndex(index,
  // QItemSelectionModel::ClearAndSelect);
  edit(index);
}

void Table::createProxy() {
  m_proxyModel = new QSortFilterProxyModel();
  m_proxyModel->setSourceModel(m_model);
  m_proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
  m_proxyModel->setFilterKeyColumn(-1);
}
