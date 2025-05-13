#include "tablewrapper.h"

TableWrapper::TableWrapper(QList<QFlight>& flights, QWidget* parent)
    : flights(flights), QWidget{parent} {
  createWidgets();
  layoutSetting();
  setConnections();
}

void TableWrapper::createToolButton(QToolButton*& button, QString iconSrc) {
  QPixmap originalEdit(iconSrc);
  int editSize = 32;
  QPixmap scaledEdit = originalEdit.scaled(
      editSize, editSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
  QIcon editIcon(scaledEdit);
  button = new QToolButton();
  button->setIcon(editIcon);
  button->setCursor(Qt::PointingHandCursor);
  button->setIconSize(QSize(editSize, editSize));
  button->setAutoRaise(true);
}

void TableWrapper::createWidgets() {
  layout = new QGridLayout(this);
  table = new Table(flights);

  createToolButton(editButton, "edit.png");
  createToolButton(deleteButton, "trash.png");
  createToolButton(addButton, "plus.png");

  lastColumnVisibilityCheckbox =
      new QCheckBox("Показать промежуточные посадки");
  lastColumnVisibilityCheckbox->setCursor(Qt::PointingHandCursor);
  lastColumnVisibilityCheckbox->setChecked(true);
  lastColumnVisibilityCheckbox->setStyleSheet(R"(
QCheckBox {
    spacing: 8px;
}
QCheckBox::indicator {
    width: 18px;
    height: 18px;
    border: 2px solid #a0aec0;
    border-radius: 4px;
}
QCheckBox::indicator:checked {
    background-color: #4299e1;
    border-color: #4299e1;
    image: url(check.png);
}
    )");

  filterToolBox = new FilterToolBox(table);
  filterToolBox->setStyleSheet(R"(
QToolBox {
    background-color: #f8fafc;
    border: 1px solid #e2e8f0;
    border-radius: 8px;
    padding: 6px;
}

QToolBox::tab {
    min-height: 100px;
    background-color: #edf2f7;
    color: #2d3748;
    border: 1px solid #e2e8f0;
    border-radius: 6px;
    cursor: pointer;

    padding: 0px 16px;
    margin: 2px;
    font-weight: 600;
}

FilterToolBox::tab:hover {
    cursor: pointer;
}

QToolBox::tab:selected {
    background-color: #4299e1;
    color: white;
}
    )");

  searchField = new QLineEdit(this);
  editButton->setObjectName("adminButton");
  deleteButton->setObjectName("deleteButton");
  addButton->setObjectName("addButton");
  lastColumnVisibilityCheckbox->setObjectName("visibilityCheckbox");

  searchField->setObjectName("searchField");
  searchField->setPlaceholderText("Поиск рейсов...");
  searchField->setStyleSheet(R"(
QLineEdit {
    border: 2px solid #cbd5e0;
    border-radius: 20px;
    padding: 8px 12px;
    color: #385861;
    font-size: 14px;
}
QLineEdit:focus {
    border-color: #4299e1;
}
)");
}

void TableWrapper::layoutSetting() {
  layout->setColumnStretch(0, 1);
  layout->setColumnStretch(1, 4);
  layout->setHorizontalSpacing(10);
  layout->addWidget(table, 1, 1);
  layout->addWidget(filterToolBox, 0, 0, 2, 1);
  QHBoxLayout* controlsLayout = new QHBoxLayout();

  controlsLayout->addWidget(searchField);
  controlsLayout->addWidget(editButton);
  controlsLayout->setStretch(1, 0);

  controlsLayout->addWidget(deleteButton);
  controlsLayout->addWidget(addButton);
  controlsLayout->addWidget(lastColumnVisibilityCheckbox);
  controlsLayout->setSpacing(30);

  layout->addLayout(controlsLayout, 0, 1);
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
