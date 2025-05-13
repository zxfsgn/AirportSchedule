#include "mainwindow.h"

#include <QApplication>
#include <QDebug>
#include <QPalette>
#include <QStyleFactory>

void setStyles(QApplication&);
void setDarkTheme(bool enabled);

int main(int argc, char* argv[]) {
  std::locale::global(std::locale(""));
  QApplication a(argc, argv);
  setDarkTheme(false);
  setStyles(a);
  MainWindow w;
  w.show();
  return a.exec();
}

void setStyles(QApplication& app) {
  app.setStyle(QStyleFactory::create("Fusion"));

  QPalette palette;
  palette.setColor(QPalette::Window, QColor(240, 240, 240));
  palette.setColor(QPalette::WindowText, Qt::black);
  palette.setColor(QPalette::Base, Qt::white);
  palette.setColor(QPalette::AlternateBase, QColor(245, 245, 245));
  palette.setColor(QPalette::Button, QColor(230, 230, 230));
  palette.setColor(QPalette::ButtonText, Qt::black);
  palette.setColor(QPalette::Highlight, QColor(61, 142, 255));
  palette.setColor(QPalette::HighlightedText, Qt::white);

  app.setPalette(palette);
}

void loadStyleSheet(QApplication& app, const QString& path) {
  QFile file(path);
  if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    QString styleSheet = QLatin1String(file.readAll());
    app.setStyleSheet(styleSheet);
    file.close();
  }
}

void setDarkTheme(bool enabled) {
  if (enabled) {
    QPalette darkPalette;
    darkPalette.setColor(QPalette::Window, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::WindowText, Qt::white);
    darkPalette.setColor(QPalette::Base, QColor(35, 35, 35));
    darkPalette.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::Button, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::ButtonText, Qt::white);
    darkPalette.setColor(QPalette::Highlight, QColor(61, 142, 255));
    darkPalette.setColor(QPalette::HighlightedText, Qt::white);
    qApp->setPalette(darkPalette);

    qApp->setStyleSheet(R"(
            QTableView {
                background-color: #232323;
                color: white;
                gridline-color: #444;
            }
            QHeaderView::section {
                background-color: #353535;
            }
        )");
  } else {
    qApp->setPalette(qApp->style()->standardPalette());
    qApp->setStyleSheet("");  // Reset to light theme
  }
}
