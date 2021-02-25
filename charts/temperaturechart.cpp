#include "temperaturechart.h"
#include <QtMath>
#include <QColor>

TemperatureChart::TemperatureChart(QChart *parent) : QChart(parent)
{
    _x.setTitleText("Time (sec)");
    _x.setRange(0, 10);
    _x.setTickCount(11);

    _y.setRange(40, 215);
    _y.setTickCount(11);
    _y.setTickInterval(5);
    _y.setTitleText("Temperature (°F)");
    _y.setLabelFormat("%i");

    this->addAxis(&_x, Qt::AlignBottom);
    this->addAxis(&_y, Qt::AlignLeft);
    this->addSeries(&_data);
    this->legend()->setVisible(false);

    _pen.setColor(QColor::fromRgb(212, 12, 8));
    _pen.setWidth(3);

    _data.attachAxis(&_x);
    _data.attachAxis(&_y);
    _data.setPen(_pen);
}

void TemperatureChart::updateChart(int time, double value)
{
    if (time >= _x.max())
        _x.setRange(_x.min(), time + 1);

    if (value >= _y.max())
        _y.setRange(_y.min(), value + (qRound(value) % 5));

    _data.append(time, value);
}

void TemperatureChart::clear()
{
    _data.clear();
}

