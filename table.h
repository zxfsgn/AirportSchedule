#ifndef TABLE_H
#define TABLE_H

#include <QDebug>
#include <QHeaderView>
#include <QString>
#include <QTableWidget>

#include <map>
#include <string>

#include "../CMAKESRC/Flight/Flight.h"

using std::map;
using std::wstring;

class Table : public QTableWidget {
  Q_OBJECT
 public:
  explicit Table(Flight* flights,
                 size_t& flightsAmount,
                 QWidget* parent = nullptr);

 public slots:
  void populateTable();

 signals:

 private:
  Flight* flights;
  size_t& flightsAmount;
};

#endif  // TABLE_H
