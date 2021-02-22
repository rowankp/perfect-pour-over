#ifndef VIEWBREWSWIDGET_H
#define VIEWBREWSWIDGET_H

#include <QWidget>

namespace Ui { class ViewBrewsWidget; }

class ViewBrewsWidget : public QWidget
{
    Q_OBJECT

    public:
        explicit ViewBrewsWidget(QWidget *parent = nullptr);
        ~ViewBrewsWidget();

    public slots:
        void showIndividual();

    private:
        Ui::ViewBrewsWidget *ui;
};

#endif // VIEWBREWSWIDGET_H
