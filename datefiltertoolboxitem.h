#ifndef DATEFILTERTOOLBOXITEM_H
#define DATEFILTERTOOLBOXITEM_H

#include <QDate>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

class DateFilterToolBoxItem : public QWidget {
  Q_OBJECT
 public:
  explicit DateFilterToolBoxItem(const QDate date, QWidget* parent = nullptr);

  const QDate date;
  QPushButton* deleteButton;
  QHBoxLayout* layout;

 signals:
  void deleteButtonClicked(DateFilterToolBoxItem*, const QDate&, bool);
};

#endif  // DATEFILTERTOOLBOXITEM_H
