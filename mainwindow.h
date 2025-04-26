#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QChart>
#include <QChartView>
#include <QDialog>
#include <QGridLayout>
#include <QMainWindow>
#include <QPieSeries>
#include <QTabWidget>
#include <string>

#include "addflight.h"
#include "barchart.h"
#include "circlechart.h"
#include "editflight.h"
#include "linechart.h"
#include "table.h"
// #include "requests.h"

#include "../CMAKESRC/FileInteractions/FileInteractions.h"
#include "../CMAKESRC/Flight/Flight.h"

using std::wstring;

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

 signals:
  void requestBtnClicked();

 private slots:
  void on_btnAdd_clicked();

  void on_diagramButton_clicked();

  void on_barchartButton_clicked();

  void on_deleteButton_clicked();

  void on_lineChartBtn_clicked();

  void on_intermediateBtn_clicked();

  void on_requestsButton_clicked();

 private:
  QTabWidget* tabs;
  Table* table;
  QWidget* charts;
  CircleChart* diagram;
  BarChart* barchart;
  LineChart* lineChart;
  EditFlight* editFlight;
  AddFlight* addFlight;
  // Requests* m_requests;

  Flight* flights;
  size_t flightsAmount{};
  FileInteractions* fileInteractions;

  void setTab();
  void initializeFlights();
};
#endif  // MAINWINDOW_H
