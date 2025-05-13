#include "table.h"

Table::Table(QList<QFlight>& flights, QWidget* parent)
    : flights(flights), QTableView(parent) {
  horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::Stretch);
  horizontalHeader()->setStyleSheet(R"(

    )");
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
  setStyles();
}

void Table::deleteSelectedRows() {
  QModelIndexList selected = this->selectionModel()->selectedRows();
  if (selected.isEmpty()) {
    return;
  }
  QMessageBox box(this);
  box.setText("Есть уверенность?");
  box.setIcon(QMessageBox::Question);
  box.addButton(QMessageBox::Apply);
  box.addButton(QMessageBox::Cancel);
  if (box.exec() == QMessageBox::Cancel)
    return;
  std::sort(selected.begin(), selected.end(),
            [](const QModelIndex& a, const QModelIndex& b) {
              return a.row() > b.row();
            });
  for (const QModelIndex& index : selected) {
    proxyModel()->removeRows(index.row(), 1);
  }
}

void Table::setStyles() {
  // Special styling for flight table
  QString tableStyle = R"(
    QTableView {
        font: 11pt "Segoe UI";
        color: #3d8eff;
        selection-background-color: #3d8eff;
        selection-color: white;
    }

    QTableView::item {
        padding: 6px;
    }

    QTableView::item:selected {
        background: #3d8eff;
        color: white;
    }

    /* Color coding for different aircraft types */
    QTableView::item[aircraft="Boeing737"] {
        background: #e3f2fd;
    }

    QTableView::item[aircraft="A320"] {
        background: #e8f5e9;
    }

    /* Highlight today's flights */
    QTableView::item[date=today] {
        border-left: 3px solid #ff9800;
    }
)";

  // QGraphicsOpacityEffect* effect = new QGraphicsOpacityEffect(this);
  // setGraphicsEffect(effect);

  // QPropertyAnimation* animation = new QPropertyAnimation(effect, "opacity");
  // animation->setDuration(300);
  // animation->setStartValue(0);
  // animation->setEndValue(1);
  // animation->start(QPropertyAnimation::DeleteWhenStopped);

  setStyleSheet(tableStyle);
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
  // there is a shit-code in this function as I have no
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

void Table::dateFilterController(const QDate& date, bool add) {
  Filters newFilters{proxyModel()->filters()};
  if (add)
    newFilters.date.append(date);
  else
    newFilters.date.removeAll(date);
  proxyModel()->setFilters(newFilters);
}
