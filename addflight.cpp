#include "addflight.h"

AddFlight::AddFlight(Flight* flights, size_t& flightsAmount, QWidget* parent)
    : flights(flights), flightsAmount(flightsAmount), QWidget{parent} {
  dialog = new QDialog(this);
  dialog->setWindowTitle("Добавить новую запись");
  form = new QFormLayout(dialog);

  numberEdit = new QLineEdit(dialog);
  destinationEdit = new QLineEdit(dialog);
  intermediateEdit = new QLineEdit(dialog);
  aircraftEdit = new QLineEdit(dialog);

  seatsEdit = new QSpinBox(dialog);
  seatsEdit->setRange(0, 300);

  dayEdit = new QSpinBox(dialog);
  dayEdit->setRange(1, 31);
  dayEdit->setValue(QDate::currentDate().day());

  monthEdit = new QSpinBox(dialog);
  monthEdit->setRange(1, 12);
  monthEdit->setValue(QDate::currentDate().month());

  yearEdit = new QSpinBox(dialog);
  yearEdit->setRange(2000, 2100);
  yearEdit->setValue(QDate::currentDate().year());

  hourEdit = new QSpinBox(dialog);
  dayEdit->setRange(0, 23);
  dayEdit->setValue(QTime::currentTime().hour());

  minuteEdit = new QSpinBox(dialog);
  dayEdit->setRange(0, 59);
  dayEdit->setValue(QTime::currentTime().minute());

  // form.addRow("№ рейса:", lastNameEdit);

  dateLayout = new QHBoxLayout();
  dateLayout->addWidget(new QLabel("Дата:"));
  dateLayout->addWidget(dayEdit);
  dateLayout->addWidget(new QLabel("."));
  dateLayout->addWidget(monthEdit);
  dateLayout->addWidget(new QLabel("."));
  dateLayout->addWidget(yearEdit);
  form->addRow(dateLayout);

  timeLayout = new QHBoxLayout();
  timeLayout->addWidget(new QLabel("Время:"));
  timeLayout->addWidget(hourEdit);
  timeLayout->addWidget(new QLabel(":"));
  timeLayout->addWidget(minuteEdit);
  form->addRow(timeLayout);

  form->addRow("Пункт назначения:", destinationEdit);
  form->addRow("Тип самолёта:", aircraftEdit);
  form->addRow("Количество посадочных мест:", seatsEdit);

  form->addRow("Промежуточные посадки:", intermediateEdit);

  buttonBox = new QDialogButtonBox(
      QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, dialog);

  form->addRow(buttonBox);

  connect(buttonBox, &QDialogButtonBox::accepted, dialog, &QDialog::accept);
  connect(buttonBox, &QDialogButtonBox::rejected, dialog, &QDialog::reject);
}

void AddFlight::showDialog() {
  if (dialog->exec() == QDialog::Accepted) {
    // if (lastNameEdit->text().isEmpty()  routeStartEdit->text().isEmpty()
    //     routeFinishEdit->text().isEmpty()) {
    //   QMessageBox::warning(this, "Ошибка", "Заполните обязательные поля!");
    //   return;
    // }

    Flight newFlight;
    newFlight.number = numberEdit->text().toInt();
    newFlight.intermediate = intermediateEdit->text().toStdWString();
    newFlight.aircraft = aircraftEdit->text().toStdWString();
    newFlight.destination = destinationEdit->text().toStdWString();
    newFlight.date =
        QDate(yearEdit->value(), monthEdit->value(), dayEdit->value())
            .toString()
            .toStdWString();
    newFlight.time =
        QTime(hourEdit->value(), minuteEdit->value()).toString().toStdWString();
    newFlight.seats = seatsEdit->value();
    cudFlight = new CUDFlight(flights, flightsAmount);
    cudFlight->createOne(newFlight);

    QMessageBox::information(this, "Успех", "Запись успешно добавлена!");
    //      this->close();
  }
}
