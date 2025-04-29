#include "tabledelegate.h"

TableDelegate::TableDelegate(QObject* parent) : QStyledItemDelegate{parent} {}

QWidget* TableDelegate::createEditor(QWidget* parent,
                                     const QStyleOptionViewItem& option,
                                     const QModelIndex& index) const {
  switch (static_cast<QColumns>(index.column())) {
    case QColumns::Seats: {
      QSpinBox* spinBox = new QSpinBox(parent);
      spinBox->setRange(0, 200);
      spinBox->setFrame(false);
      return spinBox;
    }

    case QColumns::Destination: {
      QComboBox* comboBox = new QComboBox(parent);
      comboBox->addItems({"Хабаровск", "Железногорск", "Горнозаводск", "Москва",
                          "Санкт-Петербург", "Красноярск", "Псков",
                          "Новосибирск"});
      return comboBox;
    }

    case QColumns::Aircraft: {
      QComboBox* comboBox = new QComboBox(parent);
      comboBox->addItems({"A320", "Boeing737", "B737NG", "Bombardier_Dash-8",
                          "Sukhoi_Superjet_100", "Embraer", "Boeing777",
                          "Ан-24"});
      return comboBox;
    }

    default:
      return QStyledItemDelegate::createEditor(parent, option, index);
  }
}

void TableDelegate::setEditorData(QWidget* editor,
                                  const QModelIndex& index) const {
  switch (static_cast<QColumns>(index.column())) {
    case QColumns::Seats:
      if (QSpinBox* spinBox = qobject_cast<QSpinBox*>(editor)) {
        spinBox->setValue(index.data(Qt::EditRole).toUInt());
      }
      break;

    case QColumns::Destination:
      if (QComboBox* comboBox = qobject_cast<QComboBox*>(editor)) {
        comboBox->setCurrentText(index.data(Qt::EditRole).toString());
      }
      break;
    default:
      QStyledItemDelegate::setEditorData(editor, index);
  }
}

void TableDelegate::setModelData(QWidget* editor,
                                 QAbstractItemModel* model,
                                 const QModelIndex& index) const {
  switch (static_cast<QColumns>(index.column())) {
    case QColumns::Seats:
      if (QSpinBox* spinBox = qobject_cast<QSpinBox*>(editor)) {
        model->setData(index, spinBox->value());
      }
      break;

    case QColumns::Destination:
      if (QComboBox* comboBox = qobject_cast<QComboBox*>(editor)) {
        model->setData(index, comboBox->currentText());
      }
      break;
    default:
      QStyledItemDelegate::setModelData(editor, model, index);
  }
}

void TableDelegate::updateEditorGeometry(QWidget* editor,
                                         const QStyleOptionViewItem& option,
                                         const QModelIndex& index) const {
  editor->setGeometry(option.rect);
}
