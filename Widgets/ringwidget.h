#ifndef RINGWIDGET_H
#define RINGWIDGET_H

#include "ui_ringwidget.h"
//#include <QFrame>   // For Setting the
#include <QDebug>
class RingWidget : public QWidget, private Ui::RingWidget
{
    Q_OBJECT

public:
    explicit RingWidget(QWidget *parent = nullptr);
public slots:
    void diameter_changed();
    void thick_changed();
    void active_changed(Qt::CheckState state);
};

#endif // RINGWIDGET_H
