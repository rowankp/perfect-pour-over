#include "brewtimer.h"
#include <QDebug>

BrewTimer::BrewTimer(QWidget *parent): QLabel(parent)
{
    connect(&_trigger, &QTimer::timeout, this, &BrewTimer::updateLabel);
    _timer.start();
}

int BrewTimer::getTimeElapsed() const
{
    return _timer.nsecsElapsed();
}

void BrewTimer::toggleTimer(bool toggle)
{
    if (toggle)
        _trigger.start(1000);
    else
    {
        _trigger.stop();
        emit brewStopped(_timer.elapsed());
    }

    _timer.restart();
}

void BrewTimer::updateLabel()
{
    int elapsed = _timer.elapsed() / 1000;
    int elapsed_mins = elapsed / 60;
    int elapsed_secs = elapsed % 60;

    QString minutes = elapsed / 60 < 10 ? QString("0%1").arg(elapsed_mins) : QString("%1").arg(elapsed_mins);
    QString seconds = elapsed % 60 < 10 ? QString(":0%1").arg(elapsed_secs) : QString(":%1").arg(elapsed_secs);
    this->setText(minutes + seconds);
}
