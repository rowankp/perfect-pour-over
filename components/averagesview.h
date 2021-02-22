#ifndef AVERAGESVIEW_H
#define AVERAGESVIEW_H

#include <QWidget>

#include "brewdatastructure.h"

namespace Ui { class AveragesView; }

class AveragesView : public QWidget
{
    Q_OBJECT

    public:
        explicit AveragesView(QWidget *parent = nullptr);
        ~AveragesView();

    private:
        Ui::AveragesView *ui;
};

#endif // AVERAGESVIEW_H
