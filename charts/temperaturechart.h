#ifndef TEMPERATURECHART_H
#define TEMPERATURECHART_H

#include <QtCharts>
#include <QPen>

class TemperatureChart : public QChart
{
    Q_OBJECT

    public:
        TemperatureChart(QChart *parent = nullptr);

    public slots:
        void updateChart(int time, double value);
        void clear();

    private:
        QValueAxis _x;
        QValueAxis _y;
        QSplineSeries _data;
        QPen _pen;
};

#endif // TEMPERATURECHART_H
