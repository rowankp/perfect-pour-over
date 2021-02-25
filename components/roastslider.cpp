#include "roastslider.h"

#include <QPainter>
#include <QStyleOptionSlider>
#include <QStyle>
#include <QStylePainter>

RoastSlider::RoastSlider(QWidget *parent) : QSlider(parent)
{
    this->setTickInterval(1);
    this->setRange(0,4);
    this->setTickPosition(TickPosition::TicksBelow);
}

RoastSlider::~RoastSlider()
{ }

void RoastSlider::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QStylePainter p1(this);
    QStyleOptionSlider opt;
    initStyleOption(&opt);

    opt.subControls = QStyle::SC_SliderTickmarks;
    p1.drawComplexControl(QStyle::CC_Slider, opt);
    opt.subControls = QStyle::SC_SliderGroove;
    p1.drawComplexControl(QStyle::CC_Slider, opt);
    opt.subControls = QStyle::SC_SliderHandle;
    p1.drawComplexControl(QStyle::CC_Slider, opt);

    int rightLast = 0;
    QRect rr;
    p1.drawText(rect(), Qt::TextDontPrint, QString("MediumLight"), &rr);

    for (int v = this->minimum(); v <= this->maximum(); v += tickInterval())
    {
        QStyle *st = style();
        QStyleOptionSlider slider;
        slider.init(this);

        int available = st->pixelMetric(QStyle::PM_SliderSpaceAvailable, &slider, this);

        int len = st->pixelMetric(QStyle::PM_SliderLength, &slider, this);
        int left = QStyle::sliderPositionFromValue(minimum(), maximum(), v, available) + len;

        QString label = "";
        switch(v)
        {
            case ROAST_LIGHT:
                label = QString("Light");
                break;
            case ROAST_MEDIUM:
                label = QString("Medium");
                break;
            case ROAST_DARK:
                label = QString("Dark");
            break;
        }

        if (qAbs(maximum() - v) < tickInterval())
             left -= 2 * len;

        QPoint pos(left, rect().bottom());
        QRect r;
          if (left < available && rightLast <= left - len)
          {
             rr.setX(pos.x());
             rr.setY(pos.y());
             p1.drawText(rr, Qt::TextDontPrint, label, &r);
             p1.drawText(pos, label);
          }
          rightLast = left + r.width();
       }
    }
