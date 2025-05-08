#include "tablewrapper.h"

TableWrapper::TableWrapper(QList<QFlight>& flights, QWidget* parent)
    : flights(flights), QWidget{parent} {
  createWidgets();
  layoutSetting();
  setConnections();
}

void TableWrapper::createWidgets() {
  layout = new QGridLayout(this);
  table = new Table(flights);
  editButton = new QPushButton("BOOM BAM SWITCH ADMIN MOD BOOM BAM");
  deleteButton = new QPushButton("Удалить выбранные");
  addButton = new QPushButton("Добавить рейс");
  lastColumnVisibilityCheckbox =
      new QCheckBox("Показать промежуточные посадки");
  lastColumnVisibilityCheckbox->setChecked(true);
  filterToolBox = new FilterToolBox(table);
  searchField = new QLineEdit();
}

void TableWrapper::layoutSetting() {
  layout->addWidget(table, 0, 1);
  layout->addWidget(filterToolBox, 0, 0);
  layout->addWidget(searchField);
  layout->addWidget(editButton);
  layout->addWidget(deleteButton);
  layout->addWidget(addButton);
  layout->addWidget(lastColumnVisibilityCheckbox);
}

void TableWrapper::setConnections() {
  connect(editButton, &QPushButton::clicked,
          dynamic_cast<FlightTableModel*>(table->model()),
          &FlightTableModel::switchEditability);
  connect(deleteButton, &QPushButton::clicked, table,
          &Table::deleteSelectedRows);
  connect(addButton, &QPushButton::clicked, table, &Table::addRow);

  connect(searchField, &QLineEdit::textChanged, table->proxyModel(),
          &QSortFilterProxyModel::setFilterFixedString);
  connect(lastColumnVisibilityCheckbox, &QCheckBox::toggled, table,
          &Table::switchVisibilityLastColumn);
}
