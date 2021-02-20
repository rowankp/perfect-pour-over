#include "tastingwheelwidget.h"
#include "ui_tastingwheelwidget.h"

TastingWheelWidget::TastingWheelWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TastingWheelWidget)
{
    ui->setupUi(this);
}

TastingWheelWidget::~TastingWheelWidget()
{
    delete ui;
}
