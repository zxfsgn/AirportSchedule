#include "filtertoolbox.h"

FilterToolBox::FilterToolBox(Table* table, QWidget* parent)
    : table(table), QToolBox{parent} {
  setDateChooser();
  setTimeRadio();
  setDestinatoinChooser();
  setAircraftChooser();
  setSeatsRadio();
  setIntermediateChooser();
}

void FilterToolBox::setDateChooser() {
  dateChooser = new QWidget();
  QDateEdit* dateEdit = new QDateEdit();
  dateEdit->setCalendarPopup(true);
  QLabel* dates = new QLabel();
  QPushButton* addDateButton = new QPushButton("Добавить дату");
  QVBoxLayout* layout = new QVBoxLayout(dateChooser);
  layout->addWidget(dateEdit);
  layout->addWidget(dates);
  addItem(dateChooser, "Даты");
  layout->addWidget(addDateButton);
  currentDate = dateEdit->date();
  connect(addDateButton, &QPushButton::clicked, [dates, this]() {
    dates->setText(
        QString(dates->text() + '\n' + this->currentDate.toString()));
  });
}

void FilterToolBox::setTimeRadio() {
  QStringList ranges = {"00:00 - 07:59", "08:00 - 15:59", "16:00 - 23:59",
                        "Любое"};
  QString header = "Время";
  universalChooser<QRadioButton>(header, ranges, timeRange);
  timeRange->setObjectName("timeButtonGroup");
}

void FilterToolBox::setDestinatoinChooser() {
  QString header = "Пункты назначения";
  universalChooser<QCheckBox>(header, flightOptions::destinations,
                              destinationChooser);
  destinationChooser->setObjectName("destinationButtonGroup");
}

void FilterToolBox::setAircraftChooser() {
  QString header = "Самолёты";
  universalChooser<QCheckBox>(header, flightOptions::aircrafts,
                              aircraftChooser);
  aircraftChooser->setObjectName("aircraftButtonGroup");
}

void FilterToolBox::setSeatsRadio() {
  QStringList ranges = {"0 - 100", "100 - 200", "200 - 300", "Все"};
  QString header = "Количество пассажирских мест";
  universalChooser<QRadioButton>(header, ranges, seatsRange);
  seatsRange->setObjectName("seatsButtonGroup");
}

void FilterToolBox::setIntermediateChooser() {
  QString header = "Промежуточные пункты усадок";
  universalChooser<QCheckBox>(header, flightOptions::destinations,
                              intermediateChooser);
  intermediateChooser->setObjectName("intermediateButtonGroup");
}
