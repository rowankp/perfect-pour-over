#include "viewbrewswidget.h"
#include "ui_viewbrewswidget.h"

ViewBrewsWidget::ViewBrewsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ViewBrewsWidget)
{
    ui->setupUi(this);
}

ViewBrewsWidget::~ViewBrewsWidget()
{
    delete ui;
}
