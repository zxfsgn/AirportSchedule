#include "table.h"

Table::Table(QList<QFlight>& flights, QWidget* parent)
    : flights(flights), QTableView(parent) {
  horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::Stretch);
  m_model = new FlightTableModel(flights);
  delegate = new TableDelegate(this);
  setModel(m_model);
  setItemDelegate(delegate);
  setSelectionMode(QAbstractItemView::SingleSelection);
  setSelectionBehavior(QAbstractItemView::SelectRows);
  setMinimumSize(750, 500);
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
