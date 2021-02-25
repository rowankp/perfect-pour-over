#ifndef ROASTSLIDER_H
#define ROASTSLIDER_H

#include "global.h"

#include <QSlider>

class RoastSlider : public QSlider
{
    Q_OBJECT

    public:
        RoastSlider(QWidget *parent);
        ~RoastSlider();

    private:
        void paintEvent(QPaintEvent *e);
};

#endif // ROASTSLIDER_H
