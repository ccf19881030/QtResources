#include <QResizeEvent>
#include <QDebug>
#include "navbar.h"
#include "navbarpagelistwidget.h"

NavBarPageListWidget::NavBarPageListWidget(NavBar *parent) :
    QWidget(parent)
{
    navBar = parent;
    pageButtonHeight = 32;
}

NavBarPageListWidget::~NavBarPageListWidget()
{
}

int NavBarPageListWidget::rowHeight() const
{
    return pageButtonHeight;
}

void NavBarPageListWidget::setRowHeight(int newHeight)
{
    pageButtonHeight = newHeight;
    setMaximumHeight(navBar->visiblePages().size() * pageButtonHeight);
}

void NavBarPageListWidget::layoutButtons(int width)
{
    for(int i = 0; i < navBar->visiblePages().size(); i++)
    {
        navBar->visiblePages()[i].button->setGeometry(0, i * pageButtonHeight, width, pageButtonHeight);
        navBar->visiblePages()[i].button->setToolTip("");
    }
}

void NavBarPageListWidget::resizeEvent(QResizeEvent *e)
{
    int rows = e->size().height() / pageButtonHeight;

    layoutButtons(e->size().width());

    if(e->oldSize().height() != e->size().height())
        emit buttonVisibilityChanged(rows);

    QWidget::resizeEvent(e);
}

NavBarButton::NavBarButton(QWidget *parent):
    QToolButton(parent)
{
}
