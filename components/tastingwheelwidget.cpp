#include "tastingwheelwidget.h"
#include "ui_tastingwheelwidget.h"

TastingWheelWidget::TastingWheelWidget(QWidget *parent) :
    QWidget(parent),
    _ui(new Ui::TastingWheelWidget)
{
    _ui->setupUi(this);
    _ui->label_wheel->setPixmap(QPixmap("C:\\Users\\rowan\\OneDrive\\Documents\\OIT\\Senior Project\\perfect-pour-over\\references\\flavor-wheel.png"));
}

TastingWheelWidget::~TastingWheelWidget()
{
    delete _ui;
}
