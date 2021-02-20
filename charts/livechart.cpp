#include "livechart.h"

LiveChart::LiveChart(QChart *parent) : QChart(parent)
{
    _x.setRange(0,10);
    _x.setTickCount(11);
    _x.setTitleText("Time (sec)");

    _y_pH.setRange(0, 14);
    _y_pH.setTickCount(15);
    _y_pH.setTitleText("pH");
    _y_pH.setTitleVisible(true);

    _y_temp.setRange(40, 215);
    _y_temp.setTickCount(15);
    _y_temp.setTitleText("Temperature (°F)");
    _y_temp.setLabelFormat("%i");

    this->addAxis(&_x, Qt::AlignBottom);
    this->addAxis(&_y_pH, Qt::AlignLeft);
    this->addAxis(&_y_temp, Qt::AlignRight);
    this->addSeries(&_data_pH);
    this->addSeries(&_data_temp);

    _data_pH.setName("ph");
    _data_pH.attachAxis(&_x);
    _data_pH.attachAxis(&_y_pH);

    _data_temp.setName("temperature");
    _data_temp.attachAxis(&_x);
    _data_temp.attachAxis(&_y_temp);
}

void LiveChart::updateChart(int time, double pH, double temperature)
{
    if (time >= _x.max())
        _x.setRange(_x.min(), time + 1);

    if (temperature >= _y_temp.max())
        _y_temp.setRange(_y_temp.min(), temperature + (qRound(temperature) % 5));

    _data_pH.append(time, pH);
    _data_temp.append(time, temperature);
}
