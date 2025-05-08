#ifndef TABLEWRAPPER_H
#define TABLEWRAPPER_H

#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QToolBox>

#include "filtertoolbox.h"
#include "table.h"

class TableWrapper : public QWidget {
  Q_OBJECT
 public:
  explicit TableWrapper(QList<QFlight>& flights, QWidget* parent = nullptr);

  Table* table;
 signals:
  void updated();

 private:
  QGridLayout* layout;
  QWidget* toolBar;
  QWidget* header;

  QPushButton* editButton;
  QPushButton* deleteButton;
  QPushButton* addButton;
  QCheckBox* lastColumnVisibilityCheckbox;

  QLineEdit* searchField;
  FilterToolBox* filterToolBox;

  void createWidgets();
  void layoutSetting();
  void setConnections();

 protected:
  QList<QFlight>& flights;
};

#endif  // TABLEWRAPPER_H
