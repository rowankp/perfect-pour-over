#include "averagesview.h"
#include "ui_averagesview.h"

AveragesView::AveragesView(VIEW type, QWidget *parent) : QWidget(parent), _ui(new Ui::AveragesView)
{
    _ui->setupUi(this);

    _x->setRange(0,10);
    _x->setTickCount(11);

    _y->setRange(0, 14);
    _y->setTickCount(15);

    _pen.setWidth(3);

    _data->setPen(_pen);

    createChart(type);
}

AveragesView::~AveragesView()
{
    delete _chart;
    delete _ui;
}

void AveragesView::createChart(VIEW type)
{
    switch (type)
    {
        case VIEW::Acidity:
            _y->setTitleText("pH");
            break;
        case VIEW::Dosage:
            _y->setTitleText("Dosage (g)");
            break;
        case VIEW::Rating:
            _y->setTitleText("Rating");
            break;
        case VIEW::Region:
            _y->setTitleText("Region");
            break;
        case VIEW::Roast:
            _y->setTitleText("Roast");
            break;
        case VIEW::Temperature:
            _y->setTitleText("Final Temperature (F)");
            break;
        case VIEW::Time:
            _y->setTitleText("Total Brew Time");
            break;
    }

    _chart->addAxis(_x, Qt::AlignBottom);
    _chart->addAxis(_y, Qt::AlignLeft);
    _chart->legend()->setVisible(false);

    _ui->view->setChart(_chart);
}
