#include <QMouseEvent>
#include "navbarsplitter.h"

/**
 * @class NavBarSplitter
 * @brief Splitter, used inside navigation bar.
 */
/**
 * @property NavBarSplitter::increment
 * This property holds increment, used to move splitter handle. This value must be equal to NavBar::rowHeight property.
 */

/**
 * Constructs new splitter with the parent argument passed on to the QFrame constructor.
 * @param parent Parent widget
 */
NavBarSplitter::NavBarSplitter(QWidget *parent):
    QSplitter(parent)
{
}

int NavBarSplitter::increment() const
{
    return qobject_cast<NavBarSplitterHandle *>(handle(1))->increment;
}

void NavBarSplitter::setIncrement(int inc)
{
    qobject_cast<NavBarSplitterHandle *>(handle(1))->increment = inc;
}

QSplitterHandle *NavBarSplitter::createHandle()
{
    return new NavBarSplitterHandle(orientation(), this);
}


NavBarSplitterHandle::NavBarSplitterHandle(Qt::Orientation orientation, QSplitter *parent):
    QSplitterHandle(orientation, parent)
{
    mouseOffset = 0;
    pressed     = false;
    increment   = 32;
}

void NavBarSplitterHandle::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        mouseOffset = e->pos().y();
        pressed = true;
        update();
    }
}

void NavBarSplitterHandle::mouseMoveEvent(QMouseEvent *e)
{
    if(!(e->buttons() & Qt::LeftButton))
        return;

    int sh         = splitter()->height();
    int pos        = parentWidget()->mapFromGlobal(e->globalPos()).y() - mouseOffset;
    int reversePos = sh - pos;
    int newPos     = sh - (reversePos - (reversePos % increment)) - height();

    moveSplitter(newPos);
}
