#include "gridlayoutdebugger.h"
#include <QFrame>

GridLayoutDebugger::GridLayoutDebugger(QGridLayout *layout)
    : m_layout(layout)
{
}

void GridLayoutDebugger::enable(bool on)
{
    if (on == m_enabled)
        return;

    m_enabled = on;

    if (m_enabled)
        buildOverlay();
    else
        clear();
}

void GridLayoutDebugger::clear()
{
    for (auto *w : m_debugWidgets)
    {
        m_layout->removeWidget(w);
        delete w;
    }

    m_debugWidgets.clear();
}

void GridLayoutDebugger::buildOverlay()
{
    if (!m_layout)
        return;

    clear();

    int rows = m_layout->rowCount();
    int cols = m_layout->columnCount();

    for (int r = 0; r < rows; ++r)
    {
        for (int c = 0; c < cols; ++c)
        {
            auto *label = new QLabel(QString("%1,%2").arg(r).arg(c));

            label->setAlignment(Qt::AlignCenter);
            label->setStyleSheet(
                "background: rgba(0, 255, 0, 40);"
                "border: 1px solid green;"
                "color: black;"
                "font-weight: bold;"
                );

            label->setMinimumSize(30, 20);

            m_layout->addWidget(label, r, c);
            m_debugWidgets.append(label);
        }
    }
}
