#include "phchart.h"
#include <QColor>

pHChart::pHChart(QChart *parent) : QChart(parent)
{
    _x.setRange(0,10);
    _x.setTickCount(11);
    _x.setTitleText("Time (sec)");

    _y.setRange(0, 14);
    _y.setTickCount(15);
    _y.setTitleText("pH");
    _y.setTitleVisible(true);
    _y.setVisible(true);

    this->addAxis(&_x, Qt::AlignBottom);
    this->addAxis(&_y, Qt::AlignLeft);
    this->addSeries(&_data);
    this->legend()->setVisible(false);

    _pen.setColor(QColor::fromRgb(9, 173, 53));
    _pen.setWidth(3);

    _data.attachAxis(&_x);
    _data.attachAxis(&_y);
    _data.setPen(_pen);
}

void pHChart::updateChart(int time, double value)
{
    if (time >= _x.max())
        _x.setRange(_x.min(), time + 1);

    _data.append(time, value);
}

void pHChart::clear()
{
    _data.clear();
}
