#ifndef TABLEWRAPPER_H
#define TABLEWRAPPER_H

#include <QVBoxLayout>
#include <QWidget>

#include "table.h"

class TableWrapper : public QWidget {
  Q_OBJECT
 public:
  explicit TableWrapper(Flight* flights,
                        size_t& flightsAmount,
                        QWidget* parent = nullptr);

 signals:

 private:
  QVBoxLayout* layout;
  Table* table;
  QWidget* toolBar;
  QWidget* header;

 protected:
  Flight* flights;
  size_t& flightsAmount;
};

#endif  // TABLEWRAPPER_H
