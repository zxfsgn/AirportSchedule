#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include <QFile>
#include <QGridLayout>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLabel>
#include <QList>
#include <QMainWindow>
#include <QMessageBox>
#include <QPushButton>
#include <QTabWidget>
#include <QToolBar>

#include "chartswrapper.h"
#include "qflight.h"
#include "tablewrapper.h"
// #include "requests.h"

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

 signals:
  void jsonParsed(QList<QFlight>);

 protected:
  void closeEvent(QCloseEvent* event) override;

 private:
  const QString FILE_NAME = "Flights.txt";

  QTabWidget* tabs;
  TableWrapper* tableWrapper;
  ChartsWrapper* chartsWrapper;
  // Requests* m_requests;

  QList<QFlight> flights;

  void setTab();
  void setStyles();
  bool loadFlightsFromBinary();
  bool saveFlightsToBinary();
  bool wannaSave();
  void parseFlightsFromJson(const QString& filePath);
  void generateRandomFlights(int amount);
};
#endif  // MAINWINDOW_H
