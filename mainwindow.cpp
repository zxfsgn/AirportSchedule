#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
  initializeFlights();
  setTab();
  QWidget* menu = new QWidget();
  setMenuWidget(menu);
  editButton = new QPushButton("BOOM BAM SWITCH ADMIN MOD BOOM BAM");
  deleteButton = new QPushButton("Удалить выбранные");
  addButton = new QPushButton("Добавить рейс");
  auto layout = new QGridLayout();
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
  // editFlight = new EditFlight(flights, flightsAmount);
  // connect(editFlight->confirmDeleteBtnTrue, &QPushButton::clicked, table,
  //         &Table::populateTable);
  // connect(editFlight->confirmDeleteBtnFalse, &QPushButton::clicked, table,
  //         &Table::populateTable);
  // QToolBar* toolBar = addToolBar("Actions");

  // QAction* addAction = toolBar->addAction("Add Row");
  // QAction* deleteAction = toolBar->addAction("Delete Row");
  // QAction* sampleDataAction = toolBar->addAction("Add Sample Data");
  // connect(sampleDataAction, &QAction::triggered,
  //         m_controller, &TableController::addSampleData);
  // lineChart = new LineChart(flights, flightsAmount);
  // barchart = new BarChart(flights, flightsAmount);
  // diagram = new CircleChart(flights, flightsAmount);
  // addFlight = new AddFlight(flights, flightsAmount);
  // connect(addFlight, &AddFlight::added, table, &Table::populateTable);
}
// void MainWindow::setupConnections() {
//     connect(m_model, &CustomTableModel::editCompleted,
//             [](const QString &message) {
//                 QMessageBox::information(nullptr, "Operation Complete",
//                 message);
//             });
// }
MainWindow::~MainWindow() {}

// void MainWindow::on_btnAdd_clicked() {
//   addFlight->showDialog();
// }

// void MainWindow::on_diagramButton_clicked() {
//   diagram = new CircleChart(flights, flightsAmount);
//   diagram->show();
// }

// void MainWindow::on_barchartButton_clicked() {
//   barchart = new BarChart(flights, flightsAmount);
//   barchart->show();
// }

// void MainWindow::on_lineChartBtn_clicked() {
//   lineChart = new LineChart(flights, flightsAmount);
//   lineChart->show();
// }

// void MainWindow::on_deleteButton_clicked() {
//   editFlight->show();
// }

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
  tabs->addTab(table, "Таблица");
  tabs->addTab(charts, "Диаграммы");
  setCentralWidget(tabs);
}
