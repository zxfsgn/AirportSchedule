#include "tabledelegate.h"

TableDelegate::TableDelegate(QObject* parent) : QStyledItemDelegate{parent} {}

QWidget* TableDelegate::createEditor(QWidget* parent,
                                     const QStyleOptionViewItem& option,
                                     const QModelIndex& index) const {
  switch (static_cast<QColumns>(index.column())) {
    case QColumns::Date: {
      QDateEdit* dateEdit = new QDateEdit(parent);
      dateEdit->setCalendarPopup(true);
      dateEdit->setDate(QDate::currentDate());
      QString styleSheet = R"(
QDateEdit {
        background-color: white;
        border: 1px solid #ccc;
        border-radius: 4px;
        padding: 3px 18px 3px 8px;
        min-width: 6em;
        color: #333;
    }

    QDateEdit:hover {
        border: 1px solid #999;
    }

    QDateEdit:editable {
        background: white;
    }

    QDateEdit:!editable {
        background: #f8f8f8;
    }

    QDateEdit::drop-down {
        subcontrol-origin: padding;
        subcontrol-position: right center;
        width: 20px;
        border-left: 1px solid #ddd;
    }

    QDateEdit::down-arrow {
        image: url(:/icons/arrow-down.png);
        width: 10px;
        height: 10px;
    }

    QDateEdit QAbstractItemView {
        border: 1px solid #ddd;
        selection-background-color: #3d8eff;
        selection-color: white;
        background: white;
        outline: none;
    }
    )";
      dateEdit->setStyleSheet(styleSheet);
      return dateEdit;
    }

    case QColumns::Seats: {
      QSpinBox* spinBox = new QSpinBox(parent);
      spinBox->setRange(0, 200);
      spinBox->setFrame(false);
      return spinBox;
    }

    case QColumns::Destination: {
      QComboBox* comboBox = new QComboBox(parent);
      comboBox->addItems(flightOptions::destinations);
      QString styleSheet = R"(
QComboBox {
        background-color: white;
        border: 1px solid #ccc;
        border-radius: 4px;
        padding: 3px 18px 3px 8px;
        min-width: 6em;
        color: #333;
    }

    QComboBox:hover {
        border: 1px solid #999;
    }

    QComboBox:editable {
        background: white;
    }

    QComboBox:!editable {
        background: #f8f8f8;
    }

    QComboBox::drop-down {
        subcontrol-origin: padding;
        subcontrol-position: right center;
        width: 20px;
        border-left: 1px solid #ddd;
    }

    QComboBox::down-arrow {
        image: url(:/icons/arrow-down.png);
        width: 10px;
        height: 10px;
    }

    QComboBox QAbstractItemView {
        border: 1px solid #ddd;
        selection-background-color: #3d8eff;
        selection-color: white;
        background: white;
        outline: none;
    }
    )";
      comboBox->setStyleSheet(styleSheet);
      return comboBox;
    }

    case QColumns::Aircraft: {
      QComboBox* comboBox = new QComboBox(parent);
      comboBox->addItems(
          flightOptions::aircrafts);  // place in some other place
      QString styleSheet = R"(
QComboBox {
        background-color: white;
        border: 1px solid #ccc;
        border-radius: 4px;
        padding: 3px 18px 3px 8px;
        min-width: 6em;
        color: #333;
    }

    QComboBox:hover {
        border: 1px solid #999;
    }

    QComboBox:editable {
        background: white;
    }

    QComboBox:!editable {
        background: #f8f8f8;
    }

    QComboBox::drop-down {
        subcontrol-origin: padding;
        subcontrol-position: right center;
        width: 20px;
        border-left: 1px solid #ddd;
    }

    QComboBox::down-arrow {
        image: url(:/icons/arrow-down.png);
        width: 10px;
        height: 10px;
    }

    QComboBox QAbstractItemView {
        border: 1px solid #ddd;
        selection-background-color: #3d8eff;
        selection-color: white;
        background: white;
        outline: none;
    }
    )";
      comboBox->setStyleSheet(styleSheet);
      return comboBox;
    }

    case QColumns::Intermediate: {
      QComboBox* comboBox = new QComboBox(parent);
      comboBox->addItems(flightOptions::intermediate);
      QString styleSheet = R"(
QComboBox {
        background-color: white;
        border: 1px solid #ccc;
        border-radius: 4px;
        padding: 3px 18px 3px 8px;
        min-width: 6em;
        color: #333;
    }

    QComboBox:hover {
        border: 1px solid #999;
    }

    QComboBox:editable {
        background: white;
    }

    QComboBox:!editable {
        background: #f8f8f8;
    }

    QComboBox::drop-down {
        subcontrol-origin: padding;
        subcontrol-position: right center;
        width: 20px;
        border-left: 1px solid #ddd;
    }

    QComboBox::down-arrow {
        image: url(:/icons/arrow-down.png);
        width: 10px;
        height: 10px;
    }

    QComboBox QAbstractItemView {
        border: 1px solid #ddd;
        selection-background-color: #3d8eff;
        selection-color: white;
        background: white;
        outline: none;
    }
    )";
      comboBox->setStyleSheet(styleSheet);
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

void TableDelegate::paint(QPainter* painter,
                          const QStyleOptionViewItem& option,
                          const QModelIndex& index) const {
  // if (index.column() == 4) {  // Aircraft column
  //   QStyleOptionViewItem opt = option;
  //   initStyleOption(&opt, index);

  //   // Custom drawing
  //   painter->save();
  //   painter->setRenderHint(QPainter::Antialiasing);

  //   // Draw background
  //   painter->fillRect(opt.rect, QColor(240, 248, 255));

  //   // Draw aircraft icon
  //   // QRect iconRect = opt.rect.adjusted(4, 4, -4, -4);
  //   // QPixmap icon(":/icons/airplane.png");
  //   // painter->drawPixmap(iconRect, icon);

  //   // Draw text
  //   painter->setPen(Qt::black);
  //   painter->drawText(opt.rect.adjusted(30, 0, 0, 0), Qt::AlignVCenter,
  //                     index.data().toString());

  //   painter->restore();
  // } else {
  QStyledItemDelegate::paint(painter, option, index);
  // }
}
