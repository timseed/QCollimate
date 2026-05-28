#include "ringwidget.h"
#include "gridlayoutdebugger.h"

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


    auto debugger = new GridLayoutDebugger(this->gridLayout);
    debugger->enable(true);

}
