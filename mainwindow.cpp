#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
  setWindowTitle("Расписание рейсов[*]");
  loadFlightsFromBinary();
  parseFlightsFromJson("Flights.json");
  setTab();
  QWidget* menu = new QWidget();
  setMenuWidget(menu);
  // why method pointer syntax doesn't work
  // and signal dataChanged doesn't work
  connect(tableWrapper->table->model(), SIGNAL(editCompleted(const QString&)),
          chartsWrapper, SLOT(updateCharts()));
  connect(tableWrapper->table->model(), &FlightTableModel::editCompleted, this,
          [this]() { setWindowModified(true); });
  setStyles();
  connect(this, &MainWindow::jsonParsed, tableWrapper->table->model(),
          &FlightTableModel::initializeDefaultFlights);
}

MainWindow::~MainWindow() {}

// void MainWindow::setupConnections() {
//     connect(m_model, &CustomTableModel::editCompleted,
//             [](const QString &message) {
//                 QMessageBox::information(nullptr, "Operation Complete",
//                 message);
//             });
// }

void MainWindow::parseFlightsFromJson(const QString& filePath) {
  QList<QFlight> flights;

  QFile file(filePath);
  if (!file.open(QIODevice::ReadOnly)) {
    qWarning() << "Couldn't open file:" << filePath;
    return;
  }

  // 2. Parse JSON document
  QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
  if (doc.isNull()) {
    qWarning() << "Invalid JSON format";
    return;
  }

  // 3. Extract flights array
  QJsonArray flightsArray = doc.object()["flights"].toArray();

  // 4. Convert each JSON object to QFlight
  for (const QJsonValue& value : flightsArray) {
    QJsonObject obj = value.toObject();

    QFlight flight;
    flight.number = obj["number"].toString();
    flight.date = QDate::fromString(obj["date"].toString(), "yyyy-MM-dd");
    flight.time = QTime::fromString(obj["time"].toString(), "hh:mm");
    flight.destination = obj["destination"].toString();
    flight.aircraft = obj["aircraft"].toString();
    flight.seats = obj["seats"].toInt();
    flight.intermediate = obj["intermediate"].toString();

    flights.append(flight);
  }
  emit jsonParsed(flights);
}

void MainWindow::setStyles() {
  // Apply this to your main window or app
  QString styleSheet = R"(
    /* Main window */
    QMainWindow {
        background-color: #f5f5f5;
    }

    /* Table styling */
    QTableView {
        background-color: white;
        alternate-background-color: #f9f9f9;
        gridline-color: #e0e0e0;
        font: 11pt "Segoe UI";
    }

    QHeaderView::section {
        background-color: #3d8eff;
        color: white;
        padding: 6px;
        border: none;
        font-weight: bold;
    }

    /* Buttons */
    QPushButton {
        background-color: #3d8eff;
        color: white;
        border-radius: 4px;
        padding: 6px 12px;
        min-width: 80px;
    }

    QPushButton:hover {
        background-color: #2a7ae9;
    }

    QPushButton:pressed {
        background-color: #1a6ad9;
    }

    /* Combo boxes */
    QComboBox {
        padding: 5px;
        border: 1px solid #ccc;
        border-radius: 4px;
        min-width: 120px;
    }

    /* Line edits */
    QLineEdit {
        border: 1px solid #ccc;
        border-radius: 4px;
        padding: 5px;
    }

    /* Tabs */
    QTabWidget::pane {
        border: 1px solid #ddd;
    }

    QTabBar::tab {
        background: #e0e0e0;
        padding: 8px 12px;
    }

    QTabBar::tab:selected {
        background: white;
        border-bottom: 2px solid #3d8eff;
    }

)";

  setStyleSheet(styleSheet);
}

void MainWindow::closeEvent(QCloseEvent* event) {
  if (wannaSave()) {
    event->accept();
  } else {
    event->ignore();
  }
}

bool MainWindow::wannaSave() {
  if (!isWindowModified())
    return true;

  const QMessageBox::StandardButton ret = QMessageBox::warning(
      this, tr("Сохранить изменения?"),
      tr("Таблица была изменена.\n"
         "Вы хотите сохранить вот это всё?"),
      QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
  switch (ret) {
    case QMessageBox::Save:
      return saveFlightsToBinary();
    case QMessageBox::Cancel:
      return false;
    default:
      break;
  }
  return true;
}

bool MainWindow::loadFlightsFromBinary() {
  QFile file(FILE_NAME);
  if (!file.open(QIODevice::ReadOnly)) {
    qWarning() << "Could not open file for reading:" << FILE_NAME;
    return false;
  }
  QDataStream in(&file);

  // in.setVersion(QDataStream::Qt_DefaultCompiledVersion);

  in >> flights;

  file.close();
  return true;
}

bool MainWindow::saveFlightsToBinary() {
  QFile file(FILE_NAME);
  if (!file.open(QIODevice::WriteOnly)) {
    qWarning() << "Could not open file for writing:" << FILE_NAME;
    return false;
  }
  QDataStream out(&file);

  // out.setVersion(QDataStream::Qt_DefaultCompiledVersion);

  out << flights;

  file.close();
  return true;
}

void MainWindow::setTab() {
  tabs = new QTabWidget();
  chartsWrapper = new ChartsWrapper(flights);
  tableWrapper = new TableWrapper(flights);

  tabs->addTab(tableWrapper, "Таблица");
  tabs->addTab(chartsWrapper, "Диаграммы");
  setCentralWidget(tabs);
}
