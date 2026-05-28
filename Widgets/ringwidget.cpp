#include "ringwidget.h"

#ifdef UI_DEBUG
#include "gridlayoutdebugger.h"
#endif


RingWidget::RingWidget(QWidget *parent)
    : QWidget(parent)
{
    setupUi(this);
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
