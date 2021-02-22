#ifndef TASTINGWHEELWIDGET_H
#define TASTINGWHEELWIDGET_H

#include <QWidget>

namespace Ui { class TastingWheelWidget; }

class TastingWheelWidget : public QWidget
{
    Q_OBJECT

    public:
        explicit TastingWheelWidget(QWidget *parent = nullptr);
        ~TastingWheelWidget();

    private:
        Ui::TastingWheelWidget *_ui;
};

#endif // TASTINGWHEELWIDGET_H
