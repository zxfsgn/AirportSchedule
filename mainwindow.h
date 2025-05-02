#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include <QGridLayout>
#include <QMainWindow>
#include <QTabWidget>
#include <QToolBar>
#include <QList>
#include <QLabel>
#include <QPushButton>

#include "barchart.h"
#include "circlechart.h"
#include "linechart.h"
#include "qflight.h"
#include "table.h"
// #include "requests.h"

#include "../CMAKESRC/FileInteractions/FileInteractions.h"
#include "../CMAKESRC/Flight/Flight.h"

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

 private:
  QTabWidget* tabs;
  Table* table;
  QWidget* charts;
  QPushButton* editButton;
  QPushButton* deleteButton;
  QPushButton* addButton;
  CircleChart* circleChart;
  BarChart* barChart;
  LineChart* lineChart;
  //Requests* m_requests;

  QList<QFlight> flights;
  FileInteractions* fileInteractions;

  void setTab();
  void initializeFlights();
};
#endif  // MAINWINDOW_H
