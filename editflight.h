#ifndef EDITFLIGHT_H
#define EDITFLIGHT_H

#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include "../CMAKESRC/CUDFlight/cudflight.h"

#include "../CMAKESRC/Flight/Flight.h"
#include "../CMAKESRC/Manipulations.h"

class EditFlight : public QWidget {
  Q_OBJECT
 public:
  explicit EditFlight(Flight* flights,
                      size_t& flightsAmount,
                      QWidget* parent = nullptr);

  QPushButton* confirmDeleteBtnTrue;
  QPushButton* confirmDeleteBtnFalse;
  QLineEdit* chooseNumberField;
  QMessageBox* fullConfirmation;

 private slots:
  void deleteFlight();
  void fullConfirmationProcess();

 private:
  Flight* flights;
  size_t& flightsAmount;
  CUDFlight* cudflight;
};

#endif  // EDITFLIGHT_H
