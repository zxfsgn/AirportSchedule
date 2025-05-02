#include "editflight.h"

EditFlight::EditFlight(Flight* flights, size_t& flightsAmount, QWidget* parent)
    : flights(flights), flightsAmount(flightsAmount), QWidget(parent) {
  cudflight = new CUDFlight(flights, flightsAmount);
  chooseNumberField = new QLineEdit();
  confirmDeleteBtnTrue = new QPushButton();
  confirmDeleteBtnFalse = new QPushButton();

  auto layout = new QVBoxLayout(this);
  layout->addWidget(chooseNumberField);
  layout->addWidget(confirmDeleteBtnTrue);
  layout->addWidget(confirmDeleteBtnFalse);
  confirmDeleteBtnTrue->setStyleSheet("background-color:green");
  confirmDeleteBtnTrue->setText("✓");
  confirmDeleteBtnFalse->setStyleSheet("background-color:red");
  confirmDeleteBtnFalse->setText("⨉");

  connect(confirmDeleteBtnTrue, SIGNAL(clicked()), this,
          SLOT(fullConfirmationProcess()));

  // connect(confirmDeleteBtnTrue, SIGNAL(clicked()), this,
  // SLOT(deleteFlight()));
  connect(confirmDeleteBtnFalse, SIGNAL(clicked()), chooseNumberField,
          SLOT(clear()));
}

void EditFlight::deleteFlight() {
  int flightNumber = chooseNumberField->text().toInt() - 1;
  cudflight->deleteOne(flightNumber);
}

void EditFlight::fullConfirmationProcess() {
  fullConfirmation = new QMessageBox();
  fullConfirmation->setText("Уничтожение рейса");
  fullConfirmation->setInformativeText("Вы уверены, что люди не полетят?");
  fullConfirmation->setStandardButtons(QMessageBox::Apply |
                                       QMessageBox::Cancel);
  fullConfirmation->setDefaultButton(QMessageBox::Apply);
  int ret = fullConfirmation->exec();
  switch (ret) {
    case QMessageBox::Apply:
      deleteFlight();
      break;
    case QMessageBox::Cancel:
      this->close();
      break;
    default:
      break;
  }
}
