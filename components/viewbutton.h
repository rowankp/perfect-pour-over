#ifndef VIEWBUTTON_H
#define VIEWBUTTON_H

#include <QPushButton>
#include "brewdatastructure.h"

class ViewButton : public QPushButton
{
    Q_OBJECT

    public:
        ViewButton(QWidget *parent = nullptr);
        void setType(VIEW type);
        VIEW getType() const;

    private:
        VIEW _type = VIEW::Time;

    public slots:
        void chosen();

    signals:
        void type(VIEW type);
};

#endif // VIEWBUTTON_H
