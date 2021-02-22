#ifndef INDIVIDUALVIEW_H
#define INDIVIDUALVIEW_H

#include <QWidget>
#include <QtCharts>

namespace Ui { class IndividualView; }

class IndividualView : public QWidget
{
    Q_OBJECT

public:
    explicit IndividualView(QWidget *parent = nullptr);
    ~IndividualView();

private:
    Ui::IndividualView *ui;
};

#endif // INDIVIDUALVIEW_H
