#include "ringwidget.h"

#ifdef UI_DEBUG
#include "gridlayoutdebugger.h"
#endif


RingWidget::RingWidget(QWidget *parent)
    : QWidget(parent)
{
    setupUi(this);

    /* Signal and Slot time */
    connect(diameter,SIGNAL(sliderReleased()),this,SLOT(diameter_changed()));
    connect(thick, SIGNAL(sliderReleased()),this,SLOT(thick_changed()));
    connect(active, SIGNAL(checkStateChanged(Qt::CheckState)),this,SLOT(active_changed(Qt::CheckState)));
    this->setStyleSheet(
        "background-color: light-red;"
        );
/*    this->setStyleSheet(
        "border: 1px solid red;"
        "background-color: black;"
        "border-radius: 10px;"
        );
  */
    setAttribute(Qt::WA_StyledBackground, true);

    /* This allows you to see the Grid Placement of the items.
     * It is very useful when trying to compress a UI
     */
#ifdef UI_DEBUG
    auto debugger = new GridLayoutDebugger(this->gridLayout);
    debugger->enable(true);
#endif
}

void RingWidget::diameter_changed()
{
    qDebug() << "Diameter Changed triggered";
    m_diameter = diameter->value();
    lb_diam->setText(QString("width: %1").arg(diameter->value()));
    emit RingSize(RingDef{m_id, m_active, m_diameter, m_thickness,m_col});
}

void RingWidget::thick_changed()
{
    qDebug() << "Thickness Changed triggered";
    m_thickness = thick->value();
    lb_width->setText(QString("width: %1").arg(thick->value()));
    emit RingSize(RingDef{m_id, m_active, m_diameter, m_thickness,m_col});
}

void RingWidget::active_changed(Qt::CheckState state)
{
    qDebug() << "Active Changed triggered";
    if (state==Qt::Checked)
        m_active=true;
    else
        m_active=false;
    emit RingSize(RingDef{m_id, m_active, m_diameter, m_thickness,m_col});
}

void RingWidget::dump()
{

    QString dbg_info = QString("id: %1 active: %2 diam: %3 thick: %4").arg(m_id).arg(m_active).arg(m_diameter).arg(m_thickness);
    qDebug() << dbg_info;
}

void RingWidget::setId(int newId)
{
    m_id = newId;
    emit RingSize(RingDef{m_id, m_active, m_diameter, m_thickness,m_col});
}

void RingWidget::gui_start_values(float d, float t)
{
    diameter->setValue(d);
    m_diameter=d;
    thick->setValue(t);
    m_thickness=t;
    lb_width->setText(QString("width: %1").arg(thick->value()));
    lb_diam->setText(QString("width: %1").arg(diameter->value()));
}
