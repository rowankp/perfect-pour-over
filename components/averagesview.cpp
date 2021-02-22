#include "averagesview.h"
#include "ui_averagesview.h"

AveragesView::AveragesView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AveragesView)
{
    ui->setupUi(this);
}

AveragesView::~AveragesView()
{
    delete ui;
}
