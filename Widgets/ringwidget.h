#ifndef RINGWIDGET_H
#define RINGWIDGET_H

#include "ui_ringwidget.h"
//#include <QFrame>   // For Setting the
#include <QDebug>

struct RingDef {
    int id;
    bool b_active;
    float diameter;
    float thickness;
    QString col;
};

class RingWidget : public QWidget, private Ui::RingWidget
{
    Q_OBJECT

public:
    explicit RingWidget(QWidget *parent = nullptr);
    void setId(int newId);
    void gui_start_values(float diam, float thick);

public slots:
    void diameter_changed();
    void thick_changed();
    void diameter_changed(int newvalue);
    void thick_changed(int newvalue);
    void active_changed(Qt::CheckState state);
    void dump();
signals:
    void RingSize(RingDef rd);

private:
    int m_id;  // Used to keep track of which ring is sending the update. This needs to be manually specified.
    bool m_active;
    float m_diameter;
    float m_thickness;
    QString m_col="Red";
};

#endif // RINGWIDGET_H
