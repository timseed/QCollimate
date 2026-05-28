#ifndef GRIDLAYOUTDEBUGGER_H
#define GRIDLAYOUTDEBUGGER_H
#include <QGridLayout>
#include <QLabel>
#include <QVector>

class GridLayoutDebugger
{
public:

    explicit GridLayoutDebugger(QGridLayout *layout);

    void enable(bool on = true);
    void clear();

private:
    void buildOverlay();

    QGridLayout *m_layout;
    QVector<QWidget*> m_debugWidgets;
    bool m_enabled = false;


};

#endif // GRIDLAYOUTDEBUGGER_H
