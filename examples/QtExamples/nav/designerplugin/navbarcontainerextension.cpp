#include "navbarcontainerextension.h"
#include "navbar.h"

NavBarContainerExtension::NavBarContainerExtension(NavBar *widget, QObject *parent) :
    QObject(parent)
{
    navBar = widget;
}

void NavBarContainerExtension::addWidget(QWidget *widget)
{
    navBar->addPage(widget);
}

int NavBarContainerExtension::count() const
{
    return navBar->count();
}

int NavBarContainerExtension::currentIndex() const
{
    return navBar->currentIndex();
}

void NavBarContainerExtension::insertWidget(int index, QWidget *widget)
{
    navBar->insertPage(index, widget);
}

void NavBarContainerExtension::remove(int index)
{
    navBar->removePage(index);
}

void NavBarContainerExtension::setCurrentIndex(int index)
{
    navBar->setCurrentIndex(index);
}

QWidget *NavBarContainerExtension::widget(int index) const
{
    return navBar->widget(index);
}
