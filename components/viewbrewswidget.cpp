#include "viewbrewswidget.h"
#include "ui_viewbrewswidget.h"

ViewBrewsWidget::ViewBrewsWidget(QWidget *parent) : QWidget(parent), _ui(new Ui::ViewBrewsWidget)
{
    _ui->setupUi(this);
    _ui->widget_view->setLayout(new QHBoxLayout(_ui->widget_view));
    _ui->label_logo->setPixmap(QPixmap("C:\\Users\\rowan\\OneDrive\\Documents\\OIT\\Senior Project\\perfect-pour-over\\references\\logo_small.png"));
    _ui->button_acidity->setType(VIEW::Acidity);
    _ui->button_dosages->setType(VIEW::Dosage);
    _ui->button_ratings->setType(VIEW::Rating);
    _ui->button_regions->setType(VIEW::Region);
    _ui->button_roasts->setType(VIEW::Roast);
    _ui->button_temperature->setType(VIEW::Temperature);
    _ui->button_times->setType(VIEW::Time);

    connect(_ui->button_individual, &QPushButton::released, this, &ViewBrewsWidget::showIndividual);
    connect(_ui->button_acidity, &ViewButton::type, this, &ViewBrewsWidget::showAverage);
    connect(_ui->button_dosages, &ViewButton::type, this, &ViewBrewsWidget::showAverage);
    connect(_ui->button_ratings, &ViewButton::type, this, &ViewBrewsWidget::showAverage);
    connect(_ui->button_regions, &ViewButton::type, this, &ViewBrewsWidget::showAverage);
    connect(_ui->button_roasts, &ViewButton::type, this, &ViewBrewsWidget::showAverage);
    connect(_ui->button_temperature, &ViewButton::type, this, &ViewBrewsWidget::showAverage);
    connect(_ui->button_times, &ViewButton::type, this, &ViewBrewsWidget::showAverage);
}

ViewBrewsWidget::~ViewBrewsWidget()
{
    delete _ui;
}

void ViewBrewsWidget::showIndividual()
{
    QWidget *to = new IndividualView();

    if (_ui->widget_view->layout()->itemAt(0) != nullptr)
    {
        QWidget *from = _ui->widget_view->layout()->itemAt(0)->widget();
        _ui->widget_view->layout()->replaceWidget(from, to);
        delete from;
    }
    else
    {
        _ui->widget_view->layout()->addWidget(to);
    }
}

void ViewBrewsWidget::showAverage(VIEW type)
{
    QWidget *to = new AveragesView(type);

    if (_ui->widget_view->layout()->itemAt(0) != nullptr)
    {
        QWidget *from = _ui->widget_view->layout()->itemAt(0)->widget();
        _ui->widget_view->layout()->replaceWidget(from, to);
        delete from;
    }
    else
    {
        _ui->widget_view->layout()->addWidget(to);
    }
}
