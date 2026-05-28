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
}

void RingWidget::thick_changed()
{
     qDebug() << "thick Changed triggered";
}

void RingWidget::active_changed(Qt::CheckState state)
{
    qDebug() << "Active Changed triggered";
}
