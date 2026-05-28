#ifndef COLVIEW_H
#define COLVIEW_H

#include "ui_colview.h"

class ColView : public QWidget, private Ui::ColView
{
    Q_OBJECT

public:
    explicit ColView(QWidget *parent = nullptr);
};

#endif // COLVIEW_H
