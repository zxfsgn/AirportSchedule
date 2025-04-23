#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QChart>
#include <QChartView>
#include <QDialog>
#include <QMainWindow>
#include <QPieSeries>
#include <string>

#include "addflight.h"
#include "barchart.h"
#include "diagram.h"
#include "editflight.h"
#include "linechart.h"
// #include "requests.h"

#include "../CMAKESRC/FileInteractions/FileInteractions.h"
#include "../CMAKESRC/Flight/Flight.h"

using std::wstring;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

 signals:
  void requestBtnClicked();

 private slots:
  void on_tableWidget_Item_Data_cellDoubleClicked(int row, int column);

  void on_btnAdd_clicked();

  void on_diagramButton_clicked();

  void on_barchartButton_clicked();

  void on_deleteButton_clicked();

  void updateInfo();

  void on_lineChartBtn_clicked();

  void on_intermediateBtn_clicked();

  void on_requestsButton_clicked();

  void on_updateButton_clicked();

 private:
  Ui::MainWindow* ui;
  Diagram* diagram;
  BarChart* barchart;
  LineChart* lineChart;
  EditFlight* editFlight;
  AddFlight* addFlight;
  // Requests* m_requests;

  Flight* flights;
  size_t flightsAmount{};
  FileInteractions* fileInteractions;
};
#endif  // MAINWINDOW_H
