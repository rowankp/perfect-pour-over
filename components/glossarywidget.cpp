#include "glossarywidget.h"
#include "ui_glossarywidget.h"

GlossaryWidget::GlossaryWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GlossaryWidget)
{
    ui->setupUi(this);
}

GlossaryWidget::~GlossaryWidget()
{
    delete ui;
}
