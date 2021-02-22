#include "viewbrewswidget.h"
#include "ui_viewbrewswidget.h"
#include "components/individualview.h"
#include "components/averagesview.h"

ViewBrewsWidget::ViewBrewsWidget(QWidget *parent) : QWidget(parent), ui(new Ui::ViewBrewsWidget)
{
    ui->setupUi(this);
    ui->label_logo->setPixmap(QPixmap("C:\\Users\\rowan\\OneDrive\\Documents\\OIT\\Senior Project\\perfect-pour-over\\references\\logo_small.png"));
    ui->button_acidity->setType(VIEW::Acidity);
    ui->button_dosages->setType(VIEW::Dosage);
    ui->button_ratings->setType(VIEW::Rating);
    ui->button_regions->setType(VIEW::Region);
    ui->button_roasts->setType(VIEW::Roast);
    ui->button_temperature->setType(VIEW::Temperature);
    ui->button_times->setType(VIEW::Time);

    connect(ui->button_individual, &QPushButton::released, this, &ViewBrewsWidget::showIndividual);
    connect(ui->button_acidity, &ViewButton::type, this, &ViewBrewsWidget::showAverage);
    connect(ui->button_dosages, &ViewButton::type, this, &ViewBrewsWidget::showAverage);
    connect(ui->button_ratings, &ViewButton::type, this, &ViewBrewsWidget::showAverage);
    connect(ui->button_regions, &ViewButton::type, this, &ViewBrewsWidget::showAverage);
    connect(ui->button_roasts, &ViewButton::type, this, &ViewBrewsWidget::showAverage);
    connect(ui->button_temperature, &ViewButton::type, this, &ViewBrewsWidget::showAverage);
    connect(ui->button_times, &ViewButton::type, this, &ViewBrewsWidget::showAverage);
}

ViewBrewsWidget::~ViewBrewsWidget()
{
    delete ui;
}

void ViewBrewsWidget::showIndividual()
{
    delete ui->frame_widget->layout();
    QBoxLayout *layout = new QBoxLayout(QBoxLayout::LeftToRight, ui->frame_widget);

    ui->frame_widget->setLayout(layout);
    ui->frame_widget->layout()->addWidget(new IndividualView());
}

void ViewBrewsWidget::showAverage(VIEW type)
{
    delete ui->frame_widget->layout();
    QBoxLayout *layout = new QBoxLayout(QBoxLayout::LeftToRight, ui->frame_widget);

    ui->frame_widget->setLayout(layout);
}
