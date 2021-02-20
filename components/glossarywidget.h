#ifndef GLOSSARYWIDGET_H
#define GLOSSARYWIDGET_H

#include <QWidget>

namespace Ui {
class GlossaryWidget;
}

class GlossaryWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GlossaryWidget(QWidget *parent = nullptr);
    ~GlossaryWidget();

private:
    Ui::GlossaryWidget *ui;
};

#endif // GLOSSARYWIDGET_H
