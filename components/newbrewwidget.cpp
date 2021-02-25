#include "newbrewwidget.h"
#include "ui_newbrewwidget.h"

#include <QDateTime>

NewBrewWidget::NewBrewWidget(QWidget *parent) : QWidget(parent), _ui(new Ui::NewBrewWidget)
{
    _ui->setupUi(this);
    _ui->graphicsView_pH->setChart(&_pHChart);
    _ui->graphicsView_temperature->setChart(&_tempChart);
    _ui->graphicsView_all->setChart(&_liveChart);

    connect(&_dummy, SIGNAL(sendData(int, double, double)), this, SLOT(receiveData(int, double, double)));

    connect(_ui->slider_rating, &QSlider::valueChanged, this, &NewBrewWidget::storeRating);
    connect(_ui->button_brewToggle, &QPushButton::toggled, this, &NewBrewWidget::brewToggle);
    connect(_ui->button_brewToggle, &QPushButton::toggled, _ui->label_timer, &BrewTimer::toggleTimer);
    connect(_ui->button_save, &QPushButton::pressed, this, &NewBrewWidget::save);
    connect(_ui->button_clear, &QPushButton::pressed, this, &NewBrewWidget::clear);
    connect(_ui->label_timer, &BrewTimer::brewStopped, this, &NewBrewWidget::updateTotals);
    connect(_ui->comboBox_region, &QComboBox::currentTextChanged, this, &NewBrewWidget::storeRegion);
    connect(_ui->slider_roast, &QSlider::valueChanged, this, &NewBrewWidget::storeRoastlevel);
    connect(_ui->spinBox_age, SIGNAL(valueChanged(int)), this, SLOT(storeBeanAge(int)));
    connect(_ui->comboBox_age, &QComboBox::currentTextChanged, this, &NewBrewWidget::updateBeanAgeUnits);
    connect(_ui->comboBox_grind, SIGNAL(currentIndexChanged(int)), this, SLOT(storeGrindLevel(int)));
    connect(_ui->spinBox_water, SIGNAL(valueChanged(double)), this, SLOT(storeWater(double)));
    connect(_ui->comboBox_water, &QComboBox::currentTextChanged, this, &NewBrewWidget::updateWaterUnits);
    connect(_ui->spinBox_dosage, SIGNAL(valueChanged(double)), this, SLOT(storeDosage(double)));
    connect(_ui->comboBox_dosage, &QComboBox::currentTextChanged, this, &NewBrewWidget::updateDosageUnits);
}

NewBrewWidget::~NewBrewWidget()
{
    delete _ui;
}

void NewBrewWidget::storeRating(int value)
{
    _data.rating = value;
}

void NewBrewWidget::storeRegion(QString region)
{
    _data.region = region;
}

void NewBrewWidget::storeRoastlevel(int level)
{
    _data.roast = level;
}

void NewBrewWidget::storeBeanAge(int age)
{
    if (_ui->comboBox_age->currentText() == "days")
        _data.age = age;
    else if (_ui->comboBox_age->currentText() == "weeks")
        _data.age = age * 7;
    else
        _data.age = age * 30;
}

void NewBrewWidget::updateBeanAgeUnits(QString units)
{
    if (units == "days")
        _data.age = _ui->spinBox_age->value();
    else if (units == "weeks")
        _data.age = _ui->spinBox_age->value() * 7;
    else
        _data.age = _ui->spinBox_age->value() * 30;
}

void NewBrewWidget::storeGrindLevel(int level)
{
    _data.grind = level;
}

void NewBrewWidget::storeWater(double water)
{
    _data.water = water;
}

void NewBrewWidget::updateWaterUnits(QString units)
{
    Q_UNUSED(units);
    _data.water = _ui->spinBox_water->value();
}

void NewBrewWidget::storeDosage(double dosage)
{
    _data.dosage = dosage;
}

void NewBrewWidget::updateDosageUnits(QString units)
{
    Q_UNUSED(units);
    _data.water = _ui->spinBox_dosage->value();
}

void NewBrewWidget::pushBackTemperature(double temperature)
{
    _data.temperature.push_back(temperature);
}

void NewBrewWidget::pushBackAcidity(double pH)
{
    _data.pH.push_back(pH);
}

void NewBrewWidget::updateTotals(int time_elapsed)
{
    int elapsed = time_elapsed / 1000;
    int elapsed_mins = elapsed / 60;
    int elapsed_secs = elapsed % 60;

    _data.elapsed = elapsed;

    QString minutes = elapsed / 60 < 10 ? QString("0%1").arg(elapsed_mins) : QString("%1").arg(elapsed_mins);
    QString seconds = elapsed % 60 < 10 ? QString(":0%1").arg(elapsed_secs) : QString(":%1").arg(elapsed_secs);

    _data.brew_time = QString(minutes + seconds);
    _ui->label_totalBrewTimeInput->setText(_data.brew_time);

    if (_data.temperature.empty())
        _ui->label_finalTemperatureInput->setText("UNDEFINED");
    else
        _ui->label_finalTemperatureInput->setText(QString("%1°F").arg(_data.temperature.back()));

    if (_data.pH.empty())
        _ui->label_finalpHInput->setText("UNDEFINED");
    else
        _ui->label_finalpHInput->setText(QString("%1").arg(_data.pH.back()));

    this->save();
}

void NewBrewWidget::brewToggle(bool toggle)
{
    if (toggle)
    {
        _dummy.start();
        _data.run = QDateTime::currentDateTime().toString("MM-dd-yyyy hh:mm:ss");
        DatabaseManager::database().addRun(_data);
        _ui->button_brewToggle->setText("Stop");
    }
    else
    {
        _dummy.stop();
        _ui->button_brewToggle->setText("Start");
        buildSuggestions();
    }
}

void NewBrewWidget::receiveData(int time, double pH, double temp)
{
    _liveChart.updateChart(time, pH, temp);
    _pHChart.updateChart(time, pH);
    _tempChart.updateChart(time, temp);

    _data.pH.push_back(pH);
    _data.temperature.push_back(temp);
}

void NewBrewWidget::save()
{
    _data.age = _ui->spinBox_age->value();
    _data.brew_time = _ui->label_totalBrewTimeInput->text();
    _data.dosage = _ui->spinBox_dosage->value();
    _data.grind = _ui->comboBox_grind->currentIndex();
    _data.region = _ui->comboBox_region->currentText();
    _data.roast = _ui->slider_roast->value();
    _data.water = _ui->spinBox_water->value();

    DatabaseManager::database().updateRecord(_data);
}

void NewBrewWidget::clear()
{
    _ui->comboBox_region->setCurrentIndex(0);
    _ui->slider_roast->setValue(0);
    _ui->spinBox_age->setValue(0);
    _ui->comboBox_age->setCurrentIndex(0);
    _ui->comboBox_grind->setCurrentIndex(0);
    _ui->spinBox_water->setValue(0);
    _ui->comboBox_water->setCurrentIndex(0);
    _ui->spinBox_dosage->setValue(0);
    _ui->comboBox_dosage->setCurrentIndex(0);
}

void NewBrewWidget::buildSuggestions()
{
    _ui->label_suggestion_ageInput->setText(BrewSuggestion::suggestion().age(_data.age));
    _ui->label_suggestion_grindInput->setText(BrewSuggestion::suggestion().grind(_data.grind));
    _ui->label_suggestion_ratioInput->setText(BrewSuggestion::suggestion().brewRatio(_data.dosage, _data.water));
    _ui->label_suggestion_timeInput->setText(BrewSuggestion::suggestion().time(_data.elapsed));
    _ui->label_suggestion_tempInput->setText(BrewSuggestion::suggestion().temperature(_data.temperature.back()));
    _ui->label_suggestion_pHInput->setText(BrewSuggestion::suggestion().acidity(_data.pH.back()));
}
