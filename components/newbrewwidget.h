#ifndef NEWBREWWIDGET_H
#define NEWBREWWIDGET_H

#include "global.h"
#include "charts/livechart.h"
#include "charts/phchart.h"
#include "charts/temperaturechart.h"
#include "components/brewtimer.h"
#include "components/roastslider.h"
#include "database/brewsuggestion.h"
#include "simulation/dummydata.h"

#include <QWidget>

namespace Ui { class NewBrewWidget; }

class NewBrewWidget : public QWidget
{
    Q_OBJECT

    public:
        explicit NewBrewWidget(QWidget *parent = nullptr);
        ~NewBrewWidget();

    public slots:
        void storeRating(int value);
        void storeRegion(QString region);
        void storeRoastlevel(int level);
        void storeBeanAge(int age = 0);
        void updateBeanAgeUnits(QString units);
        void storeGrindLevel(int level);
        void storeWater(double water = 0);
        void updateWaterUnits(QString units);
        void storeDosage(double dosage = 0);
        void updateDosageUnits(QString units);
        void pushBackTemperature(double temperature);
        void pushBackAcidity(double pH);
        void updateTotals(int time_elapsed);
        void brewToggle(bool toggle);
        void receiveData(int time, double pH, double temp);
        void save();
        void clear();

    private:
        void buildSuggestions();

        Ui::NewBrewWidget *_ui;
        BrewData _data;
        pHChart _pHChart;
        TemperatureChart _tempChart;
        LiveChart _liveChart;
        DummyData _dummy;
};

#endif // NEWBREWWIDGET_H
