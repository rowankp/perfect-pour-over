#include "viewbutton.h"

ViewButton::ViewButton(QWidget *parent) : QPushButton(parent)
{
    connect(this, &QPushButton::released, this, &ViewButton::chosen);
}

void ViewButton::setType(VIEW type)
{
   _type = type;
}

VIEW ViewButton::getType() const
{
    return _type;
}

void ViewButton::chosen()
{
    emit type(_type);
}
