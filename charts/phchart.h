#ifndef PHCHART_H
#define PHCHART_H

#include <QWidget>
#include <QtCharts>
#include <QPen>

class pHChart : public QChart
{
    Q_OBJECT

    public:
        explicit pHChart(QChart *parent = nullptr);

    public slots:
        void updateChart(int time, double value);

    private:
    QValueAxis _x;
    QValueAxis _y;
    QSplineSeries _data;
    QPen _pen;

};

#endif // PHCHART_H
