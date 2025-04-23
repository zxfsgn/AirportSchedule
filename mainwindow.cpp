#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  // Need add stackLayout to show diagram in the same window

  flights = new Flight[100];
  fileInteractions = new FileInteractions(flights, flightsAmount);

  fileInteractions->inputFromTextFile();

  ui->tableWidget_Item_Data->horizontalHeader()->setSectionResizeMode(
      QHeaderView::ResizeMode::Stretch);

  editFlight = new EditFlight(flights, flightsAmount);
  connect(editFlight->confirmDeleteBtnTrue, SIGNAL(clicked()), this,
          SLOT(updateInfo()));
  connect(editFlight->confirmDeleteBtnFalse, SIGNAL(clicked()), this,
          SLOT(updateInfo()));

  lineChart = new LineChart(flights, flightsAmount);
  barchart = new BarChart(flights, flightsAmount);
  diagram = new Diagram(flights, flightsAmount);
  addFlight = new AddFlight(flights, flightsAmount);
  connect(addFlight->dialog, SIGNAL(accepted()), this, SLOT(updateInfo()));
  // m_requests = new Requests(this);
  updateInfo();
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::on_tableWidget_Item_Data_cellDoubleClicked(int row,
                                                            int column) {
  qDebug() << ui->tableWidget_Item_Data->item(row, column)->text();
}

void MainWindow::on_btnAdd_clicked() {
  addFlight->showDialog();
}

void MainWindow::on_diagramButton_clicked() {
  diagram = new Diagram(flights, flightsAmount);
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

void MainWindow::updateInfo() {
  diagram->chartView->update();
  diagram->chart->update();
  barchart->update();
  lineChart->update();
  ui->tableWidget_Item_Data->setRowCount(flightsAmount);
  for (int i = 0; i < flightsAmount; ++i) {
    wstring nullStr = L"NULL";
    if (flights[i].intermediate == nullStr) {
      flights[i].intermediate = L" ";
    }
    ui->tableWidget_Item_Data->setItem(
        i, 0, new QTableWidgetItem(QString::number(flights[i].number)));
    ui->tableWidget_Item_Data->setItem(
        i, 1, new QTableWidgetItem(QString::fromStdWString(flights[i].date)));
    ui->tableWidget_Item_Data->setItem(
        i, 2, new QTableWidgetItem(QString::fromStdWString(flights[i].time)));
    ui->tableWidget_Item_Data->setItem(
        i, 3,
        new QTableWidgetItem(QString::fromStdWString(flights[i].destination)));
    ui->tableWidget_Item_Data->setItem(
        i, 4,
        new QTableWidgetItem(QString::fromStdWString(flights[i].aircraft)));
    ui->tableWidget_Item_Data->setItem(
        i, 5, new QTableWidgetItem(QString::number(flights[i].seats)));
    ui->tableWidget_Item_Data->setItem(
        i, 6,
        new QTableWidgetItem(QString::fromStdWString(flights[i].intermediate)));
  }
  ui->tableWidget_Item_Data->hideColumn(6);
}

void MainWindow::on_intermediateBtn_clicked() {
  if (ui->tableWidget_Item_Data->isColumnHidden(6)) {
    ui->tableWidget_Item_Data->showColumn(6);
    ui->intermediateBtn->setText("Скрыть промежуточные посадки");
  } else {
    ui->tableWidget_Item_Data->hideColumn(6);
    ui->intermediateBtn->setText("Показать промежуточные посадки");
  }
}

void MainWindow::on_requestsButton_clicked() {
  emit requestBtnClicked();
}

void MainWindow::on_updateButton_clicked() {
  updateInfo();
}
