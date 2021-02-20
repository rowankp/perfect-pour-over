#ifndef LIVECHART_H
#define LIVECHART_H

#include <QtCharts>

class LiveChart : public QChart
{
    Q_OBJECT
    public:
        LiveChart(QChart *parent = nullptr);

    public slots:
        void updateChart(int time, double pH, double temperature);

    private:
        QValueAxis _x;
        QValueAxis _y_pH;
        QValueAxis _y_temp;
        QSplineSeries _data_pH;
        QSplineSeries _data_temp;
        QPen _penPh;
        QPen _penTemp;
};

#endif // LIVECHART_H
