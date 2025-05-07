#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
  initializeFlights();
  setTab();
  QWidget* menu = new QWidget();
  setMenuWidget(menu);
  // why method pointer syntax doesn't work
  // and signal dataChanged doesn't work
  connect(tableWrapper->table->model(), SIGNAL(editCompleted(const QString&)),
          chartsWrapper, SLOT(updateCharts()));
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
  chartsWrapper = new ChartsWrapper(flights);
  tableWrapper = new TableWrapper(flights);

  tabs->addTab(tableWrapper, "Таблица");
  tabs->addTab(chartsWrapper, "Диаграммы");
  setCentralWidget(tabs);
}
