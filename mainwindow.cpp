#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
  initializeFlights();
  setTab();
  editFlight = new EditFlight(flights, flightsAmount);
  connect(editFlight->confirmDeleteBtnTrue, &QPushButton::clicked, table,
          &Table::populateTable);
  connect(editFlight->confirmDeleteBtnFalse, &QPushButton::clicked, table,
          &Table::populateTable);

  lineChart = new LineChart(flights, flightsAmount);
  barchart = new BarChart(flights, flightsAmount);
  diagram = new CircleChart(flights, flightsAmount);
  addFlight = new AddFlight(flights, flightsAmount);
  connect(addFlight, &AddFlight::added, table, &Table::populateTable);
  // m_requests = new Requests(this);
  table->populateTable();

  // layout = new QGridLayout(this);

  // setLayout(layout);
}

MainWindow::~MainWindow() {}

void MainWindow::on_btnAdd_clicked() {
  addFlight->showDialog();
}

void MainWindow::on_diagramButton_clicked() {
  diagram = new CircleChart(flights, flightsAmount);
  diagram->show();
}

void MainWindow::on_barchartButton_clicked() {
  barchart = new BarChart(flights, flightsAmount);
  barchart->show();
}

void MainWindow::on_lineChartBtn_clicked() {
  lineChart = new LineChart(flights, flightsAmount);
  lineChart->show();
}

void MainWindow::on_deleteButton_clicked() {
  editFlight->show();
}

void MainWindow::on_intermediateBtn_clicked() {
  // if (ui->tableWidget_Item_Data->isColumnHidden(6)) {
  //   ui->tableWidget_Item_Data->showColumn(6);
  //   ui->intermediateBtn->setText("Скрыть промежуточные посадки");
  // } else {
  //   ui->tableWidget_Item_Data->hideColumn(6);
  //   ui->intermediateBtn->setText("Показать промежуточные посадки");
  // }
}

void MainWindow::on_requestsButton_clicked() {
  emit requestBtnClicked();
}

void MainWindow::initializeFlights() {
  flights = new Flight[100];
  fileInteractions = new FileInteractions(flights, flightsAmount);
  fileInteractions->inputFromTextFile();
}

void MainWindow::setTab() {
  tabs = new QTabWidget();
  table = new Table(flights, flightsAmount);
  charts = new QWidget();
  tabs->addTab(table, "Таблица");
  tabs->addTab(charts, "Диаграммы");
  setCentralWidget(tabs);
}
