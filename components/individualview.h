#ifndef INDIVIDUALVIEW_H
#define INDIVIDUALVIEW_H

#include "global.h"
#include "charts/livechart.h"
#include "charts/phchart.h"
#include "charts/temperaturechart.h"

#include <QtCharts>
#include <QWidget>
#include <vector>
using std::vector;

namespace Ui { class IndividualView; }

class IndividualView : public QWidget
{
    Q_OBJECT

    public:
        explicit IndividualView(QString startDate, QString endDate, bool all = false, QWidget *parent = nullptr);
        ~IndividualView();

    public slots:
        void showData(QModelIndex index);

    private:
        void getData();
        void getData(QString startDate, QString endDate);
        void createAllChart(int index);
        void createTemperatureChart(int index);
        void createPHChart(int index);
        QString convertRoastToString(int roast);

        Ui::IndividualView *_ui;
        QStringListModel _records;
        vector<BrewData> _data;
        LiveChart _all;
        TemperatureChart _temp;
        pHChart _ph;
};

#endif // INDIVIDUALVIEW_H
