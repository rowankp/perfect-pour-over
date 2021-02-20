#ifndef DUMMYDATA_H
#define DUMMYDATA_H

#include <QObject>
#include <QTimer>
#include <QElapsedTimer>

class DummyData : public QObject
{
    Q_OBJECT

    public:
        DummyData(QObject *parent = nullptr);

    public slots:
        void start();
        void stop();
        void createData();

    signals:
        void sendData(int time, double ph, double temp);

    private:
        QTimer _trigger;
        QElapsedTimer *_timer;
};

#endif // DUMMYDATA_H
