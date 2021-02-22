#ifndef AVERAGESVIEW_H
#define AVERAGESVIEW_H

#include <QWidget>
#include <QtCharts>
#include <QPen>

#include "brewdatastructure.h"

namespace Ui { class AveragesView; }

class AveragesView : public QWidget
{
    Q_OBJECT

    public:
        explicit AveragesView(VIEW type, QWidget *parent = nullptr);
        ~AveragesView();

    private:
        void createChart(VIEW type);

        Ui::AveragesView *_ui;
        QValueAxis *_x = new QValueAxis;
        QValueAxis *_y = new QValueAxis;
        QLineSeries *_data = new QLineSeries;
        QChart *_chart = new QChart;
        QPen _pen;
};

#endif // AVERAGESVIEW_H
