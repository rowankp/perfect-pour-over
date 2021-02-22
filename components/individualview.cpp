#include "individualview.h"
#include "ui_individualview.h"

IndividualView::IndividualView(QWidget *parent) : QWidget(parent), ui(new Ui::IndividualView)
{
    ui->setupUi(this);
}

IndividualView::~IndividualView()
{
    delete ui;
}
