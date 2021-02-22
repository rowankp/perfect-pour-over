#include "viewbrewswidget.h"
#include "ui_viewbrewswidget.h"
#include "components/individualview.h"
#include "components/averagesview.h"

ViewBrewsWidget::ViewBrewsWidget(QWidget *parent) : QWidget(parent), ui(new Ui::ViewBrewsWidget)
{
    ui->setupUi(this);
    ui->label_logo->setPixmap(QPixmap("C:\\Users\\rowan\\OneDrive\\Documents\\OIT\\Senior Project\\perfect-pour-over\\references\\logo_small.png"));

    connect(ui->button_individual, &QPushButton::released, this, &ViewBrewsWidget::showIndividual);
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
