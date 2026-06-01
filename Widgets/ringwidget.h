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
    void setId(int newId);

public slots:
    void diameter_changed();
    void thick_changed();
    void active_changed(Qt::CheckState state);

signals:
    void RingSize(int id, bool b_active, float diameter, float thickness, QString col="Red");

private:
    int m_id;  // Used to keep track of which ring is sending the update. This needs to be manually specified.
    bool m_active;
    float m_diameter;
    float m_thickness;
    QString m_col="Red";
};

#endif // RINGWIDGET_H
