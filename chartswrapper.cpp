#include "chartswrapper.h"

ChartsWrapper::ChartsWrapper(QList<QFlight>& flights, QWidget* parent)
    : flights(flights), QWidget{parent} {
  chartChooser = new QComboBox();

  chartChooser->addItems({"Круговая", "Столбчатая", "График"});
  stackedCharts = new QStackedWidget();
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
  chartChooser->setStyleSheet(styleSheet);
  createCharts();

  layout = new QGridLayout(this);
  layout->addWidget(chartChooser);
  layout->addWidget(stackedCharts);
  connect(chartChooser, SIGNAL(activated(int)) /*&QComboBox::activated*/,
          stackedCharts,
          SLOT(setCurrentIndex(
              int)) /* QOverload<int>::of(&QStackedWidget::setCurrentIndex)*/);
}

void ChartsWrapper::createCharts() {
  circleChart = new CircleChart(flights);
  barChart = new BarChart(flights);
  lineChart = new LineChart(flights);

  stackedCharts->addWidget(circleChart->chartView);
  stackedCharts->addWidget(barChart->chartView);
  stackedCharts->addWidget(lineChart->chartView);
}

void ChartsWrapper::updateCharts() {
  circleChart->createSeries();
  barChart->createSeries();
  lineChart->createSeries();
}
