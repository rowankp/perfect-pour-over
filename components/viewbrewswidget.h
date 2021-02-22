#ifndef VIEWBREWSWIDGET_H
#define VIEWBREWSWIDGET_H

#include <QWidget>
#include <QtCharts>

#include "brewdatastructure.h"
#include "components/viewbutton.h"

namespace Ui { class ViewBrewsWidget; }

class ViewBrewsWidget : public QWidget
{
    Q_OBJECT

    public:
        explicit ViewBrewsWidget(QWidget *parent = nullptr);
        ~ViewBrewsWidget();

    public slots:
        void showIndividual();
        void showAverage(VIEW type);

    private:
        Ui::ViewBrewsWidget *ui;
};

#endif // VIEWBREWSWIDGET_H
