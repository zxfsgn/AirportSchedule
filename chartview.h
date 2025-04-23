#ifndef CHARTVIEW_H
#define CHARTVIEW_H

#include <QChart>
#include <QChartView>

class ChartView : public QChartView
{
    Q_OBJECT
public:
    explicit ChartView(QChart *chart, QChartView *parent = nullptr);

signals:
};

#endif // CHARTVIEW_H
