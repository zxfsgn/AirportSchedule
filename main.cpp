#include "mainwindow.h"

#include <QApplication>

int main(int argc, char* argv[]) {
  std::locale::global(std::locale(""));
  QApplication a(argc, argv);
  MainWindow w;
  w.show();
  return a.exec();
}
