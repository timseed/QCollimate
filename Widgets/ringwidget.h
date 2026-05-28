#ifndef RINGWIDGET_H
#define RINGWIDGET_H

#include "ui_ringwidget.h"

class RingWidget : public QWidget, private Ui::RingWidget
{
    Q_OBJECT

public:
    explicit RingWidget(QWidget *parent = nullptr);
};

#endif // RINGWIDGET_H
