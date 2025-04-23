#include "requests.h"

Requests::Requests(MainWindow* parent) : QWidget{parent} {
  m_layout = new QVBoxLayout(this);
  m_requestsComboBox = new QComboBox;
  m_requestContent = new QLabel;
  m_response = new QLabel;
  m_layout->addWidget(m_requestsComboBox);
  m_layout->addWidget(m_requestContent);
  m_layout->addWidget(m_response);

  connect(parent, SIGNAL(requestBtnClicked()), this->m_layout, SLOT(show()));
}

Requests::~Requests() {
  delete m_layout;
  delete m_requestsComboBox;
  delete m_requestContent;
  delete m_response;
}
