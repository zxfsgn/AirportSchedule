#ifndef REQUESTS_H
#define REQUESTS_H

#include <QComboBox>
#include <QLabel>
#include <QVBoxLayout>

#include "mainwindow.h"

class Requests : public QWidget {
  Q_OBJECT
  QVBoxLayout* m_layout;
  QComboBox* m_requestsComboBox;
  QLabel* m_requestContent;
  QLabel* m_response;

 public:
  explicit Requests(MainWindow* parent = nullptr);
  ~Requests();
};

#endif  // REQUESTS_H
