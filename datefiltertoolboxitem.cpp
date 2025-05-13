#include "datefiltertoolboxitem.h"

DateFilterToolBoxItem::DateFilterToolBoxItem(const QDate date, QWidget* parent)
    : date(date), QWidget{parent} {
  layout = new QHBoxLayout();
  auto dateText = new QLabel(date.toString());
  deleteButton = new QPushButton("Убрать");
  layout->addWidget(dateText);
  layout->addWidget(deleteButton);
  setLayout(layout);

  connect(deleteButton, &QPushButton::clicked,
          [this]() { emit deleteButtonClicked(this, this->date, false); });
}
