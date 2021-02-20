#include "dummydata.h"
#include <stdlib.h>
#include <time.h>

DummyData::DummyData(QObject *parent) : QObject(parent), _trigger(parent), _timer(nullptr)
{
    srand (time(NULL));
    connect(&_trigger, &QTimer::timeout, this, &DummyData::createData);
}

void DummyData::start()
{
    _trigger.start(1000);

    _timer = new QElapsedTimer();
    _timer->start();
}

void DummyData::stop()
{
    createData();
    _trigger.stop();
    delete _timer;
}

void DummyData::createData()
{
    int time = _timer->elapsed() / 1000;
    double pH = (rand() % 12 + 1);
    double temp = (rand() % 200 + 60);

    emit sendData(time, pH, temp);
}
