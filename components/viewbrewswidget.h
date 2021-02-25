#ifndef VIEWBREWSWIDGET_H
#define VIEWBREWSWIDGET_H

#include "global.h"
#include "components/averagesview.h"
#include "components/individualview.h"
#include "components/viewbutton.h"

#include <QWidget>
#include <QtCharts>

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
        void startDate(const QDate &date);
        void endDate(const QDate &date);

    private:
        Ui::ViewBrewsWidget *_ui;
        QString _start;
        QString _end;
};

#endif // VIEWBREWSWIDGET_H
