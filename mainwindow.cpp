#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
  initializeFlights();
  setTab();
  QWidget* menu = new QWidget();
  setMenuWidget(menu);

  editButton = new QPushButton("BOOM BAM SWITCH ADMIN MOD BOOM BAM");
  deleteButton = new QPushButton("Удалить выбранные");
  addButton = new QPushButton("Добавить рейс");
  QLabel* filterLabel = new QLabel("Filter:");
  QLineEdit* filterEdit = new QLineEdit();

  auto layout = new QGridLayout();
  layout->addWidget(filterLabel);
  layout->addWidget(filterEdit);
  layout->addWidget(editButton);
  layout->addWidget(deleteButton);
  layout->addWidget(addButton);
  menu->setLayout(layout);
  connect(editButton, &QPushButton::clicked,
          dynamic_cast<FlightTableModel*>(table->model()),
          &FlightTableModel::switchEditability);
  connect(deleteButton, &QPushButton::clicked, table,
          &Table::deleteSelectedRows);
  connect(addButton, &QPushButton::clicked, table, &Table::addRow);
  connect(filterEdit, &QLineEdit::textChanged, table->proxyModel(),
          &QSortFilterProxyModel::setFilterFixedString);
}
// void MainWindow::setupConnections() {
//     connect(m_model, &CustomTableModel::editCompleted,
//             [](const QString &message) {
//                 QMessageBox::information(nullptr, "Operation Complete",
//                 message);
//             });
// }
MainWindow::~MainWindow() {}

// void MainWindow::on_intermediateBtn_clicked() {
//   if (ui->tableWidget_Item_Data->isColumnHidden(6)) {
//     ui->tableWidget_Item_Data->showColumn(6);
//     ui->intermediateBtn->setText("Скрыть промежуточные посадки");
//   } else {
//     ui->tableWidget_Item_Data->hideColumn(6);
//     ui->intermediateBtn->setText("Показать промежуточные посадки");
//   }
// }

// void MainWindow::on_requestsButton_clicked() {
//   emit requestBtnClicked();
// }

void MainWindow::initializeFlights() {
  Flight* fileFlights = new Flight[100];
  size_t flightsAmount = 0;
  fileInteractions = new FileInteractions(fileFlights, flightsAmount);
  fileInteractions->inputFromTextFile();
  for (int i = 0; i < flightsAmount; ++i) {
    flights.push_back(fileFlights[i]);
  }
}

void MainWindow::setTab() {
  tabs = new QTabWidget();
  table = new Table(flights);
  charts = new QWidget();
  auto chartsLayout = new QGridLayout();
  lineChart = new LineChart(flights);
  barChart = new BarChart(flights);
  circleChart = new CircleChart(flights);
  chartsLayout->addWidget(lineChart->chartView);
  chartsLayout->addWidget(barChart->chartView);
  chartsLayout->addWidget(circleChart->chartView);
  charts->setLayout(chartsLayout);
  tabs->addTab(table, "Таблица");
  tabs->addTab(charts, "Диаграммы");
  setCentralWidget(tabs);
}
