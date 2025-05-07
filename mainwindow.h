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

#include "chartswrapper.h"
#include "qflight.h"
#include "tablewrapper.h"
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
  TableWrapper* tableWrapper;
  ChartsWrapper* chartsWrapper;
  //Requests* m_requests;

  QList<QFlight> flights;
  FileInteractions* fileInteractions;

  void setTab();
  void initializeFlights();
};
#endif  // MAINWINDOW_H
