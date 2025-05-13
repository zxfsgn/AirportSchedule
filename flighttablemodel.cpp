#include "flighttablemodel.h"

FlightTableModel::FlightTableModel(QList<QFlight>& flights, QObject* parent)
    : m_flights(flights),
      m_columnAmount(static_cast<size_t>(QColumns::COLUMN_COUNT)),
      QAbstractTableModel(parent) {
  emit created(this);
}

QVariant FlightTableModel::headerData(int section,
                                      Qt::Orientation orientation,
                                      int role) const {
  if (role != Qt::DisplayRole) {
    return QVariant();
  }

  if (orientation == Qt::Horizontal) {
    switch (static_cast<QColumns>(section)) {
      case QColumns::Number:
        return "Номер";
      case QColumns::Date:
        return "Дата";
      case QColumns::Time:
        return "Время";
      case QColumns::Destination:
        return "Пункт назначения";
      case QColumns::Aircraft:
        return "Самолёт";
      case QColumns::Seats:
        return "Места";
      case QColumns::Intermediate:
        return "Промежуточные";
      default:
        return QVariant();
    }
  }
  return QVariant();
}

int FlightTableModel::rowCount(const QModelIndex& parent) const {
  if (parent.isValid())
    return 0;
  return m_flights.size();
}

int FlightTableModel::columnCount(const QModelIndex& parent) const {
  if (parent.isValid())
    return 0;
  return m_columnAmount;
}

QVariant FlightTableModel::data(const QModelIndex& index, int role) const {
  if (!index.isValid())
    return QVariant();

  if (index.row() >= m_flights.size() || index.column() >= m_columnAmount) {
    return QVariant();
  }

  const QFlight* flight = &m_flights[index.row()];

  switch (role) {
    case Qt::DisplayRole:
    case Qt::EditRole:
      switch (static_cast<QColumns>(index.column())) {
        case QColumns::Number:
          return flight->number;
        case QColumns::Date:
          return flight->date;
        case QColumns::Time:
          return flight->time;
        case QColumns::Destination:
          return flight->destination;
        case QColumns::Aircraft:
          return flight->aircraft;
        case QColumns::Seats:
          return flight->seats;
        case QColumns::Intermediate: {
          QString intermediate = flight->intermediate;
          if (intermediate == "NULL")
            intermediate = "";
          return intermediate;
        }
        default:
          break;
      }
      break;
    case Qt::FontRole:
      if (index.column() == 0) {
        return QFont("Arial", 10, QFont::Bold);
      }
      break;
    // case Qt::BackgroundRole:
    //   // if (index.row() % 2 == 0) {
    //   return QColor("black-pink");
    //   //}
    //   break;
    case Qt::TextAlignmentRole:
      if (index.column() == 1 || index.column() == 2) {
        return Qt::AlignCenter;
      }
    default:
      break;
  }

  return QVariant();
}

bool FlightTableModel::setData(const QModelIndex& index,
                               const QVariant& value,
                               int role) {
  if (!index.isValid() || role != Qt::EditRole) {
    return false;
  }

  if (data(index, role) != value) {
    QFlight* flight = &m_flights[index.row()];
    // if (index.column() == EMAIL_COLUMN && !isValidEmail(value.toString()))
    // {
    //     return false;
    // }
    // if (index.column() == 1) {
    //     bool ok;
    //     int age = value.toInt(&ok);
    //     if (!ok || age < 18 || age > 100)
    //         return false; // Validate age
    // }
    switch (static_cast<QColumns>(index.column())) {
      case QColumns::Number:
        flight->number = value.toString();
        break;
      case QColumns::Date:
        flight->date = value.toDate();
        break;
      case QColumns::Time:
        flight->time = value.toTime();
        break;
      case QColumns::Destination:
        flight->destination = value.toString();
        break;
      case QColumns::Aircraft:
        flight->aircraft = value.toString();
        break;
      case QColumns::Seats:
        flight->seats = value.toUInt();
        break;
      case QColumns::Intermediate: {
        QString intermediate = value.toString();
        if (intermediate == "")
          intermediate = "NULL";
        flight->intermediate = intermediate;
        break;
      }
      default:
        break;
    }
    emit editCompleted(QString("dataChanged"));
    emit dataChanged(index, index, {role});
    return true;
  }
  return false;
}

Qt::ItemFlags FlightTableModel::flags(const QModelIndex& index) const {
  if (!index.isValid())
    return Qt::NoItemFlags;
  Qt::ItemFlags flags = Qt::ItemIsEnabled;
  if (isEditable) {
    flags |= Qt::ItemIsSelectable | Qt::ItemIsEditable;
  }
  return flags;
}

void FlightTableModel::addFlight(const QFlight& flight) {
  beginInsertRows(QModelIndex(), m_flights.size(), m_flights.size());
  m_flights.push_back(flight);
  endInsertRows();
  emit editCompleted(QString("Строка была добавлена"));
}

bool FlightTableModel::removeRows(int row,
                                  int count,
                                  const QModelIndex& parent) {
  if (row < 0 || row + count > m_flights.size() || count < 0)
    return false;

  beginRemoveRows(parent, row, row + count - 1);
  m_flights.remove(row, count);
  endRemoveRows();

  emit editCompleted(QString("%1 строк(а)(и) было(и) удалены на позиции %2")
                         .arg(count)
                         .arg(row));
  return true;
}

void FlightTableModel::switchEditability() {
  isEditable = !isEditable;
  beginResetModel();
  endResetModel();
}

void FlightTableModel::sort(int column, Qt::SortOrder order) {
  emit layoutAboutToBeChanged();
  std::sort(m_flights.begin(), m_flights.end(),
            [column, order](const auto& a, const auto& b) {
              QColumns qColumn = static_cast<QColumns>(column);
              bool isAscending = order == Qt::AscendingOrder;
              return fieldCompare(qColumn, a, b, isAscending);
            });
  emit layoutChanged();
}

bool fieldCompare(QColumns column,
                  const QFlight& a,
                  const QFlight& b,
                  bool isAscending) {
  switch (column) {
    case QColumns::Number:
      return valueCompare<QString>(a.number, b.number, isAscending);
    case QColumns::Date:
      return valueCompare<QDate>(a.date, b.date, isAscending);
    case QColumns::Time:
      return valueCompare<QTime>(a.time, b.time, isAscending);
    case QColumns::Destination:
      return valueCompare<QString>(a.destination, b.destination, isAscending);
    case QColumns::Aircraft:
      return valueCompare<QString>(a.aircraft, b.aircraft, isAscending);
    case QColumns::Seats:
      return valueCompare<quint32>(a.seats, b.seats, isAscending);
    case QColumns::Intermediate:
      return valueCompare<QString>(a.intermediate, b.intermediate, isAscending);
    default:
      break;
  }
  return true;
}

QList<QFlight>& FlightTableModel::flights() {
  return m_flights;
}

void FlightTableModel::initializeDefaultFlights(QList<QFlight> flights) {
  defaultFlights = flights;
}
