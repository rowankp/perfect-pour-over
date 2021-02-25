#ifndef AVERAGESVIEW_H
#define AVERAGESVIEW_H

#include "global.h"

#include <QWidget>
#include <QtCharts>

namespace Ui { class AveragesView; }

class AveragesView : public QWidget
{
    Q_OBJECT

    public:
    explicit AveragesView(VIEW type, QString startDate, QString endDate, bool all = false, QWidget *parent = nullptr);
    ~AveragesView();

    private:
    void createAcidityView(QString startDate, QString endDate, bool all);
    void createDosageView(QString startDate, QString endDate, bool all);
    void createRatingView(QString startDate, QString endDate, bool all);
    void createRegionView(QString startDate, QString endDate, bool all);
    void createRoastView(QString startDate, QString endDate, bool all);
    void createTemperatureView(QString startDate, QString endDate, bool all);
    void createTimeView(QString startDate, QString endDate, bool all);

    Ui::AveragesView *_ui;
    QAbstractAxis *_x;
    QAbstractAxis *_y;
    QAbstractSeries *_data;
    QChart *_chart;
};

#endif // AVERAGESVIEW_H
