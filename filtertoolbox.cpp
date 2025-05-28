#include "filtertoolbox.h"

FilterToolBox::FilterToolBox(Table* table, QWidget* parent)
    : table(table),
      currentFilterDates(table->proxyModel()->filters().date),
      QToolBox{parent} {
  initAmountFilters();
  setDateChooser();
  setTimeRadio();
  setDestinatoinChooser();
  setAircraftChooser();
  setSeatsRadio();
  setIntermediateChooser();
  setAttribute(Qt::WA_Hover);
  setContentsMargins(0, 10, 0, 10);
  // setMouseTracking(true);
  // setCursor(Qt::PointingHandCursor);
  connect(this, &FilterToolBox::dateFilterChanged, table,
          &Table::dateFilterController);
  connect(table->model(), &FlightTableModel::dataChanged, this,
          &FilterToolBox::updateAmountFilters);
}

// void FilterToolBox::mouseMoveEvent(QMouseEvent *event) {
//     QStyleOptionToolBox option;
//     initStyleOption(&option, event->pos());
//     if (style()->subElementRect(QStyle::SE_ToolBoxTabContents, &option,
//     this).contains(event->pos())) {
//         setCursor(Qt::PointingHandCursor);
//     } else {
//         unsetCursor();
//     }
//     QToolBox::mouseMoveEvent(event);
// }

void FilterToolBox::setDateChooser() {
  dateList = new QWidget();
  dateListLayout = new QVBoxLayout(dateList);

  dateChooser = new QWidget();
  dateEdit = new QDateEdit();
  dateEdit->setCalendarPopup(true);
  dateEdit->setDate(QDate::currentDate());
  dateEdit->setCursor(Qt::PointingHandCursor);
  dateEdit->setStyleSheet(R"(
    QDateEdit {
        color: black;
    }
 QCalendarWidget QAbstractItemView:enabled {
        /* Normal date color */
        color: #333333;

        /* Alternate row color */
        alternate-background-color: #f5f5f5;
    }
    )");
  QPushButton* addDateButton = new QPushButton("Добавить дату");
  addDateButton->setCursor(Qt::PointingHandCursor);
  dateLayout = new QVBoxLayout(dateChooser);
  dateLayout->addWidget(dateEdit);
  addItem(dateChooser, "Даты");
  dateLayout->addWidget(addDateButton);
  dateLayout->addWidget(dateList);

  connect(addDateButton, &QPushButton::clicked, this,
          &FilterToolBox::onDateFilterButtonClick);
}

void FilterToolBox::onDateFilterButtonClick() {
  QDate newDate = dateEdit->date();
  if (!currentFilterDates.contains(newDate)) {
    emit dateFilterChanged(newDate, true);
    auto currentDateItem = new DateFilterToolBoxItem(newDate);
    connect(currentDateItem, &DateFilterToolBoxItem::deleteButtonClicked, this,
            &FilterToolBox::deleteDate);
    dateListLayout->addWidget(currentDateItem);
  }
}

void FilterToolBox::deleteDate(DateFilterToolBoxItem* item) {
  emit dateFilterChanged(item->date, false);
  currentFilterDates.removeAll(item->date);
  dateListLayout->removeWidget(item);
  delete item;
}

void FilterToolBox::initAmountFilters() {
  QColumns column = QColumns::Aircraft;
  initAmountFilter(column);
  column = QColumns::Destination;
  initAmountFilter(column);
  column = QColumns::Intermediate;
  initAmountFilter(column);
}

void FilterToolBox::updateAmountLabels(QColumns column) {
  QMap<QString, int> flightsHash = filters[column]->filteredFlights<QString>();
  for (const auto& key : flightsHash.keys()) {
    // 1. Verify column exists
    if (!amounts.contains(column)) {
      qCritical() << "Missing column in amounts:" << static_cast<int>(column);
      continue;
    }

    // 2. Verify key exists or create label
    if (!amounts[column].contains(key)) {
      qWarning() << "Creating missing label for:" << key;
      amounts[column][key] = new QLabel(this);  // Always specify parent
    }

    // 3. Verify label pointer
    if (!amounts[column][key]) {
      qCritical() << "Null label pointer for:" << key;
      amounts[column][key] = new QLabel(this);
      flightsHash[key] = 1;
    }
    QString text = setLabelText(column, flightsHash[key]);
    amounts[column][key]->setText(text);
  }
}

void FilterToolBox::updateAmountFilters() {
  updateAmountLabels(QColumns::Aircraft);
  updateAmountLabels(QColumns::Destination);
  updateAmountLabels(QColumns::Intermediate);
}

QString FilterToolBox::setLabelText(QColumns column, int amount) {
  QString text;
  if (column == QColumns::Intermediate) {
    double flightsAmount = table->model()->flights().size();
    text = QString("(%1%)").arg(amount / flightsAmount * 100, 0, 'f', 1);
  } else {
    text = '(' + QString::number(amount) + ')';
  }
  return text;
}

void FilterToolBox::initAmountFilter(QColumns column) {
  auto filter = new FlightsFilter(table->model()->flights(), column);
  filters[column] = filter;
  QMap<QString, int> flightsHash = filter->filteredFlights<QString>();
  QMap<QString, QLabel*> labelsHash;
  for (const auto& key : flightsHash.keys()) {
    QString text = setLabelText(column, flightsHash[key]);
    if (text == "")
      text = "Без промежуточных";
    labelsHash[key] = new QLabel(text);
  }
  amounts[column] = labelsHash;
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
  universalChooser<QCheckBox>(header, flightOptions::intermediate,
                              intermediateChooser);
  intermediateChooser->setObjectName("intermediateButtonGroup");
}
