#ifndef BREWTIMER_H
#define BREWTIMER_H

#include <QLabel>
#include <QTimer>
#include <QElapsedTimer>

class BrewTimer : public QLabel
{
    Q_OBJECT

    public:
        BrewTimer(QWidget *parent = nullptr);
        int getTimeElapsed() const;

    public slots:
        void toggleTimer(bool toggle);
        void updateLabel();

    signals:
        void brewStopped(int elapsed);

    private:
        QTimer _trigger;
        QElapsedTimer _timer;
};

#endif // BREWTIMER_H
