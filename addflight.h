#ifndef ADDFLIGHT_H
#define ADDFLIGHT_H

#include <QDate>
#include <QDialog>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QSpinBox>
#include <QWidget>

#include "../CMAKESRC/CUDFlight/cudflight.h"
#include "../CMAKESRC/Flight/Flight.h"

class AddFlight : public QWidget {
  Q_OBJECT

  QFormLayout* form;
  QLineEdit* numberEdit;
  QLineEdit* destinationEdit;
  QLineEdit* intermediateEdit;
  QLineEdit* aircraftEdit;

  QSpinBox* seatsEdit;

  QSpinBox* dayEdit;

  QSpinBox* monthEdit;

  QSpinBox* yearEdit;

  QSpinBox* hourEdit;

  QSpinBox* minuteEdit;
  QHBoxLayout* dateLayout;
  QHBoxLayout* timeLayout;

 public:
  explicit AddFlight(Flight* flights,
                     size_t& flightsAmount,
                     QWidget* parent = nullptr);
  QDialog* dialog;
  QDialogButtonBox* buttonBox;
  void showDialog();

 public slots:
  void createFlight();

 signals:
  void added();

 private:
  Flight* flights;
  size_t& flightsAmount;
  CUDFlight* cudFlight;
};

#endif  // ADDFLIGHT_H
