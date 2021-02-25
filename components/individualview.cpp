#include "individualview.h"
#include "ui_individualview.h"

IndividualView::IndividualView(QString startDate, QString endDate, bool all, QWidget *parent) : QWidget(parent), _ui(new Ui::IndividualView)
{
    _ui->setupUi(this);
    _ui->listView->setModel(&_records);
    _ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    _ui->chart_all->setChart(&_all);
    _ui->chart_temp->setChart(&_temp);
    _ui->chart_ph->setChart(&_ph);

    connect(_ui->listView, &QListView::pressed, this, &IndividualView::showData);

    if (all)
        getData();
    else
        getData(startDate, endDate);
}

IndividualView::~IndividualView()
{
    delete _ui;
}

void IndividualView::showData(QModelIndex index)
{
    int i = index.row();

    _ui->label_age_input->setText(QString("%1 days").arg(_data[i].age));
    _ui->label_dosage_input->setText(QString("%1 g").arg(_data[i].dosage));
    _ui->label_grind_input->setText(QString("%1 g").arg(_data[i].grind));
    _ui->label_region_input->setText(_data[i].region);
    _ui->label_time_input->setText(_data[i].brew_time);
    _ui->label_water_input->setText(QString("%1 g").arg(_data[i].water));

    _ui->label_ph_input->setText(QString("%1").arg(_data[i].pH.back()));
    _ui->label_temp_input->setText(QString("%1").arg(_data[i].temperature.back()));;

    _ui->label_roast_input->setText(QString("%1").arg(convertRoastToString(_data[i].roast)));

    createAllChart(i);
    createPHChart(i);
    createTemperatureChart(i);
}

void IndividualView::getData()
{
    _data = DatabaseManager::database().getData();

    QStringList dates;

    for (int ii = 0; ii < (int)_data.size(); ii++)
        dates << _data[ii].run;

    _records.setStringList(dates);
}

void IndividualView::getData(QString startDate, QString endDate)
{
    _data = DatabaseManager::database().getData(startDate, endDate);

    QStringList dates;

    for (int ii = 0; ii < (int)_data.size(); ii++)
        dates << _data[ii].run;

    _records.setStringList(dates);
}

void IndividualView::createAllChart(int index)
{
    _all.clear();

    for (int ii = 0; ii < (int)_data[index].pH.size(); ii++)
        _all.updateChart(ii, _data[index].pH[ii], _data[index].temperature[ii]);
}

void IndividualView::createTemperatureChart(int index)
{
    _temp.clear();

    for (int ii = 0; ii < (int)_data[index].temperature.size(); ii++)
        _temp.updateChart(ii, _data[index].temperature[ii]);
}

void IndividualView::createPHChart(int index)
{
    _ph.clear();

    for (int ii = 0; ii < (int)_data[index].pH.size(); ii++)
        _ph.updateChart(ii, _data[index].pH[ii]);
}

QString IndividualView::convertRoastToString(int roast)
{
    QString r;

    switch (roast)
    {
        case ROAST_LIGHT:
            r = "Light";
        break;
        case ROAST_MEDIUM_LIGHT:
            r = "Medium Light";
        break;
        case ROAST_MEDIUM:
            r = "Medium";
        break;
        case ROAST_MEDIUM_DARK:
            r = "Medium Dark";
        break;
        case ROAST_DARK:
            r = "Dark";
        break;
    }

    return r;
}
