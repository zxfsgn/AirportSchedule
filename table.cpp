#include "table.h"

Table::Table(QList<QFlight>& flights, QWidget* parent)
    : flights(flights), QTableView(parent) {
  horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::Stretch);
  m_model = new FlightTableModel(flights);
  delegate = new TableDelegate(this);

  createProxy();
  setModel(proxyModel());
  setItemDelegate(delegate);

  setSelectionMode(QAbstractItemView::MultiSelection);
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
    proxyModel()->removeRows(index.row(), 1);
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
  m_proxyModel = new TableFilterProxy();
  m_proxyModel->setSourceModel(m_model);
  m_proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
  m_proxyModel->setFilterKeyColumn(-1);
}

void Table::filterController(QAbstractButton* button, bool checked) {
  // there is shit-code in this function as I have no
  // time to use subfunctions and enums
  //****//
  // think I should pass a enum value, not string
  // it feels like a bad practice
  Filters newFilters{proxyModel()->filters()};
  QString name = button->group()->objectName();
  QString text = button->text();
  if (name == "timeButtonGroup") {
    QTime time = QTime::fromString(text.left(5), "HH:mm");
    newFilters.time = time;
  } else if (name == "destinationButtonGroup") {
    if (checked)
      newFilters.destination.append(text);
    else
      newFilters.destination.removeAll(text);
  } else if (name == "aircraftButtonGroup") {
    if (checked)
      newFilters.aircraft.append(text);
    else
      newFilters.aircraft.removeAll(text);
  } else if (name == "seatsButtonGroup") {
    int seatsRange = -1;
    if (text == "0 - 100")
      seatsRange = 0;
    else if (text == "100 - 200")
      seatsRange = 100;
    else if (text == "200 - 300")
      seatsRange = 200;
    newFilters.seats = seatsRange;
  } else if (name == "intermediateButtonGroup") {
    if (checked)
      newFilters.intermediate.append(text);
    else
      newFilters.intermediate.removeAll(text);
  }
  proxyModel()->setFilters(newFilters);
}

void Table::switchVisibilityLastColumn(bool show) {
  int columnNumber = static_cast<int>(QColumns::Intermediate);
  setColumnHidden(columnNumber, !show);
}
