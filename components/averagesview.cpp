#include "averagesview.h"
#include "ui_averagesview.h"

#include <QSqlQuery>
#include <vector>
using std::vector;

AveragesView::AveragesView(VIEW type, QString startDate, QString endDate, bool all, QWidget *parent) : QWidget(parent), _ui(new Ui::AveragesView)
{
    _ui->setupUi(this);

    _chart = new QChart;

    _y = new QValueAxis(_chart);
    _y->setTitleText("Cups");
    _y->setRange(0, 10);
    ((QValueAxis *)_y)->setTickCount(11);
    ((QValueAxis *)_y)->setLabelFormat("%i");

    switch (type)
    {
        case VIEW::Acidity:
            createAcidityView(startDate, endDate, all);
            break;
        case VIEW::Dosage:
            createDosageView(startDate, endDate, all);
            break;
        case VIEW::Rating:
            createRatingView(startDate, endDate, all);
            break;
        case VIEW::Region:
            createRegionView(startDate, endDate, all);
            break;
        case VIEW::Roast:
            createRoastView(startDate, endDate, all);
            break;
        case VIEW::Temperature:
            createTemperatureView(startDate, endDate, all);
            break;
        case VIEW::Time:
            createTimeView(startDate, endDate, all);
            break;
    }

    _chart->legend()->setVisible(false);
    _chart->addAxis(_x, Qt::AlignBottom);
    _chart->addAxis(_y, Qt::AlignLeft);
    _chart->addSeries(_data);
    _data->attachAxis(_x);
    _data->attachAxis(_y);
    _ui->view->setChart(_chart);
}

AveragesView::~AveragesView()
{
    delete _chart;
    delete _ui;
}

void AveragesView::createAcidityView(QString startDate, QString endDate, bool all)
{
    QBarSet *set = new QBarSet("pH", _chart);
    set->append(0);
    if (all)
    {
        for (int ii = 1; ii <= 14; ii++)
        {
            QString q =  QString("SELECT COUNT(*) FROM StaticData WHERE FinalAcidity BETWEEN %1.0 and %2.9").arg(ii).arg(ii);
            QSqlQuery query = DatabaseManager::database().query(q);

            query.first();
            set->append(query.value(0).toInt());
        }
    }
    else
    {
        for (int ii = 1; ii <= 14; ii++)
        {
            QString q = QString("SELECT COUNT(*) FROM StaticData WHERE FinalAcidity BETWEEN %1.0 and %2.9").arg(ii).arg(ii);
            QSqlQuery query = DatabaseManager::database().query(q, startDate, endDate);

            query.first();
            set->append(query.value(0).toInt());
        }
    }

    _x = new QValueAxis(_chart);
    _x->setTitleText("pH");
    _x->setRange(0, 14);
    ((QValueAxis *)_x)->setLabelFormat("%i");
    ((QValueAxis *)_x)->setTickCount(15);

    _data = new QBarSeries(_chart);
    ((QBarSeries *)_data)->append(set);
}

void AveragesView::createDosageView(QString startDate, QString endDate, bool all)
{
    _x = new QValueAxis(_chart);
    _x->setTitleText("Dosage (g)");
    _x->setRange(20, 100);
    _x->setLabelsAngle(90);
    ((QValueAxis *)_x)->setTickCount(9);
    _chart->addAxis(_x, Qt::AlignBottom);
}

void AveragesView::createRatingView(QString startDate, QString endDate, bool all)
{    
    _x = new QCategoryAxis(_chart);
    _x->setTitleText("Rating");
    _x->setRange(0, 6);
    ((QCategoryAxis *)_x)->setLabelsPosition(QCategoryAxis::AxisLabelsPosition::AxisLabelsPositionOnValue);
    QBarSet *set = new QBarSet("pH", _chart);
    set->append(0);

    if (all)
    {
        for (int ii = 1; ii <= 5; ii++)
        {
            QString q =  QString("SELECT COUNT(*) FROM StaticData WHERE Rating = %1").arg(ii);
            QSqlQuery query = DatabaseManager::database().query(q);

            query.first();
            set->append(query.value(0).toInt());
            ((QCategoryAxis *)_x)->append(QString("%1").arg(ii), ii);
        }
    }
    else
    {
        for (int ii = 1; ii <= 5; ii++)
        {
            QString q = QString("SELECT COUNT(*) FROM StaticData WHERE Rating = %1").arg(ii);
            QSqlQuery query = DatabaseManager::database().query(q, startDate, endDate);

            query.first();
            set->append(query.value(0).toInt());
            ((QCategoryAxis *)_x)->append(QString("%1").arg(ii), ii);
        }
    }

    _data = new QBarSeries(_chart);
    ((QBarSeries *)_data)->append(set);
}

void AveragesView::createRegionView(QString startDate, QString endDate, bool all)
{    
    _x = new QCategoryAxis(_chart);
    _x->setTitleText("Region");
    _x->setLabelsAngle(90);
    ((QCategoryAxis *)_x)->append("Blend", 1);
    ((QCategoryAxis *)_x)->append("Africa", 2);
    ((QCategoryAxis *)_x)->append("Asia", 3);
    ((QCategoryAxis *)_x)->append("Central America", 4);
    ((QCategoryAxis *)_x)->append("South America", 5);
    ((QCategoryAxis *)_x)->append("Other", 6);
    ((QCategoryAxis *)_x)->setMin(0);
    ((QCategoryAxis *)_x)->setMax(7);
    ((QCategoryAxis *)_x)->setRange(0,7);
    ((QCategoryAxis *)_x)->setLabelsPosition(QCategoryAxis::AxisLabelsPosition::AxisLabelsPositionOnValue);

    QBarSet *set = new QBarSet("Region", _chart);
    set->append(0);
    if (all)
    {
        foreach(const QString &region, ((QCategoryAxis *)_x)->categoriesLabels())
        {
            QString q = QString("SELECT COUNT(*) FROM StaticData WHERE Region = '%1'").arg(region);
            QSqlQuery query = DatabaseManager::database().query(q);

            query.first();
            set->append(query.value(0).toInt());
        }
    }
    else
    {
        foreach(const QString &region, ((QCategoryAxis *)_x)->categoriesLabels())
        {
            QString q = QString("SELECT COUNT(*) FROM StaticData WHERE Region = '%1'").arg(region);
            QSqlQuery query = DatabaseManager::database().query(q, startDate, endDate);

            query.first();
            set->append(query.value(0).toInt());
        }
    }

    _data = new QBarSeries(_chart);
    ((QBarSeries *)_data)->append(set);
}

void AveragesView::createRoastView(QString startDate, QString endDate, bool all)
{
    _x = new QCategoryAxis(_chart);
    _x->setTitleText("Roast");
    _x->setLabelsAngle(90);
    _x->setRange(0,6);
    ((QCategoryAxis *)_x)->append("Light", 1);
    ((QCategoryAxis *)_x)->append("Medium Light", 2);
    ((QCategoryAxis *)_x)->append("Medium", 3);
    ((QCategoryAxis *)_x)->append("Medium Dark", 4);
    ((QCategoryAxis *)_x)->append("Dark", 5);
    ((QCategoryAxis *)_x)->setLabelsPosition(QCategoryAxis::AxisLabelsPosition::AxisLabelsPositionOnValue);

    QBarSet *set = new QBarSet("Roast", _chart);
    set->append(0);
    if (all)
    {
        for (int ii = 0; ii < 5; ++ii)
        {
            QString q = QString("SELECT COUNT(*) FROM StaticData WHERE Roast = %1").arg(ii);
            QSqlQuery query = DatabaseManager::database().query(q);

            query.first();
            set->append(query.value(0).toInt());
        }
    }
    else
    {
        for (int ii = 0; ii < 5; ++ii)
        {
            QString q = QString("SELECT COUNT(*) FROM StaticData WHERE Roast = %1").arg(ii);
            QSqlQuery query = DatabaseManager::database().query(q, startDate, endDate);

            query.first();
            set->append(query.value(0).toInt());
        }
    }

    _data = new QBarSeries(_chart);
    ((QBarSeries *)_data)->append(set);
}

void AveragesView::createTemperatureView(QString startDate, QString endDate, bool all)
{
    _x = new QValueAxis(_chart);
    _x->setTitleText("Final Temperature (F)");
    _x->setRange(40, 200);
    _x->setLabelsAngle(90);
    ((QValueAxis *)_x)->setTickCount(10);

    _data = new QLineSeries(_chart);

    if (all)
    {
        QSqlQuery query = DatabaseManager::database().query("SELECT DISTINCT FinalTemperature FROM StaticData");
        query.first();

        do
        {

        } while (query.next());

        QString qString = QString("SELECT COUNT(*) FROM StaticData WHERE FinalTemperature = %1").arg(query.value(0).toReal());
        QSqlQuery q = DatabaseManager::database().query(qString);
        qDebug() << q.lastQuery();
        q.first();
        ((QLineSeries *)_data)->append(q.value(0).toInt(), query.value(0).toReal());
    }
    else
    {
        QSqlQuery query = DatabaseManager::database().query("SELECT DISTINCT FinalTemperature FROM StaticData", startDate, endDate);
        query.first();
        do
        {
            QString qString = QString("SELECT COUNT(*) FROM StaticData WHERE FinalTemperature = %1").arg(query.value(0).toReal());
            QSqlQuery q = DatabaseManager::database().query(qString);
            q.first();
            ((QLineSeries *)_data)->append(q.value(0).toInt(), query.value(0).toReal());
        } while (query.next());
    }
}

void AveragesView::createTimeView(QString startDate, QString endDate, bool all)
{
    _x = new QValueAxis(_chart);
    _x->setTitleText("Total Brew Time (min)");
    _x->setRange(0, 8);
    _x->setLabelsAngle(90);
    ((QValueAxis *)_x)->setTickCount(17);
}
