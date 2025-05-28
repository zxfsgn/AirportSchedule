#ifndef FILTERTOOLBOX_H
#define FILTERTOOLBOX_H

#include <algorithm>

#include <QButtonGroup>
#include <QCalendar>
#include <QCalendarWidget>
#include <QCheckBox>
#include <QGroupBox>
#include <QLabel>
#include <QListWidget>
#include <QMap>
#include <QPushButton>
#include <QRadioButton>
#include <QStringList>
#include <QStringListModel>
#include <QToolBox>
#include <QVBoxLayout>

#include "datefiltertoolboxitem.h"
#include "flightsfilter.h"
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
 signals:
  bool dateFilterChanged(const QDate&, bool);

 private slots:
  void deleteDate(DateFilterToolBoxItem* item);
  void updateAmountFilters();
  // void updateFilterDatesList();

 private:
  QMap<QColumns, FlightsFilter*> filters;
  QDateEdit* dateEdit;
  QList<QDate>& currentFilterDates;
  QVBoxLayout* dateLayout;
  QWidget* dateList;
  QVBoxLayout* dateListLayout;
  QMap<QColumns, QMap<QString, QLabel*>> amounts;

  void setDateChooser();
  void onDateFilterButtonClick();

  void setTimeRadio();
  void setDestinatoinChooser();
  void setAircraftChooser();
  void setSeatsRadio();
  void setIntermediateChooser();
  void initAmountFilter(QColumns column);
  void initAmountFilters();
  void updateAmountLabels(QColumns column);
  QString setLabelText(QColumns column, int amount);

  template <typename T>
  void universalChooser(const QString& header,
                        const QStringList& variants,
                        QButtonGroup*& buttonGroup) {
    QGroupBox* groupBox = new QGroupBox();
    auto layout = new QVBoxLayout(groupBox);

    buttonGroup = new QButtonGroup(this);
    int index = 0;
    if (typeid(T) == typeid(QCheckBox)) {
      buttonGroup->setExclusive(false);
      QColumns column = QColumns::Intermediate;
      if (header == "Пункты назначения") {
        column = QColumns::Destination;
      } else if (header == "Самолёты") {
        column = QColumns::Aircraft;
      }
      for (auto& variant : variants) {
        QWidget* groupBoxItem = new QWidget();
        auto itemLayout = new QHBoxLayout(groupBoxItem);
        QString text = variant;
        if (variant == "NULL")
          text = "Без промежуточных";
        T* button = new T(text);
        button->setStyleSheet(R"(
QCheckBox {
    spacing: 8px;
}
QCheckBox::indicator {
    width: 18px;
    height: 18px;
    border: 2px solid #a0aec0;
    border-radius: 4px;
}
QCheckBox::indicator:checked {
    background-color: #4299e1;
    border-color: #4299e1;
    image: url(check.png);
}
        )");
        button->setObjectName(QString("%1_%2").arg(header).arg(index));
        itemLayout->addWidget(button);
        if (!amounts[column].contains(variant))
          amounts[column][variant] = new QLabel("(0)");
        itemLayout->addWidget(amounts[column][variant]);
        layout->addWidget(groupBoxItem);
        buttonGroup->addButton(button, ++index);
      }
    } else {
      for (auto& variant : variants) {
        T* button = new T(variant);
        if (variant == "Все" || variant == "Любое")
          button->setChecked(true);
        button->setStyleSheet(R"(
QRadioButton::indicator {
    width: 16px;
    height: 16px;
    border-radius: 8px;
    border: 2px solid #a0aec0;
}

QRadioButton::indicator:checked {
    border-color: #4299e1;
    background-color: #4299e1;
}
        )");
        layout->addWidget(button);
        buttonGroup->addButton(button, ++index);
      }
    }
    addItem(groupBox, header);
    connect(buttonGroup,
            QOverload<QAbstractButton*, bool>::of(&QButtonGroup::buttonToggled),
            table, &Table::filterController);
  }

 protected:
  QSize sizeHint() const override {
    QSize size = QToolBox::sizeHint();
    size.setHeight(100);
    return size;
  }
};

#endif  // FILTERTOOLBOX_H
