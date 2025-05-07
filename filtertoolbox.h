#ifndef FILTERTOOLBOX_H
#define FILTERTOOLBOX_H

#include <QButtonGroup>
#include <QCalendar>
#include <QCalendarWidget>
#include <QCheckBox>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QRadioButton>
#include <QToolBox>
#include <QVBoxLayout>

#include "qflight.h"
#include "table.h"

class FilterToolBox : public QToolBox {
  Q_OBJECT
 public:
  explicit FilterToolBox(Table* table, QWidget* parent = nullptr);
  QWidget* dateChooser;
  QButtonGroup* timeRange;
  QButtonGroup* destinationChooser;
  QButtonGroup* aircraftChooser;
  QButtonGroup* seatsRange;
  QButtonGroup* intermediateChooser;

  Table* table;

 private:
  QDate currentDate;

  void setDateChooser();
  void setTimeRadio();
  void setDestinatoinChooser();
  void setAircraftChooser();
  void setSeatsRadio();
  void setIntermediateChooser();

  template <typename T>
  void universalChooser(const QString& header,
                        const QStringList& variants,
                        QButtonGroup*& buttonGroup) {
    QGroupBox* groupBox = new QGroupBox();
    auto layout = new QVBoxLayout;

    buttonGroup = new QButtonGroup(this);
    if (typeid(T) == typeid(QCheckBox)) {
      buttonGroup->setExclusive(false);
    }

    int index = 0;
    for (auto& variant : variants) {
      T* button = new T(variant);
      layout->addWidget(button);
      buttonGroup->addButton(button, ++index);
    }

    groupBox->setLayout(layout);
    addItem(groupBox, header);
    connect(buttonGroup, &QButtonGroup::buttonToggled, table,
            &Table::filterController);
  }
};

#endif  // FILTERTOOLBOX_H
