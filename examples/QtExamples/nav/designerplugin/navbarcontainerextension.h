#ifndef NAVBARCONTAINEREXTENSION_H
#define NAVBARCONTAINEREXTENSION_H

#include <QtDesigner/QDesignerContainerExtension>

class NavBar;

class NavBarContainerExtension : public QObject, public QDesignerContainerExtension
{
    Q_OBJECT
    Q_INTERFACES(QDesignerContainerExtension)

public:
    explicit NavBarContainerExtension(NavBar *widget, QObject *parent);

    void     addWidget(QWidget *widget);
    int      count() const;
    int      currentIndex() const;
    void     insertWidget(int index, QWidget *widget);
    void     remove(int index);
    void     setCurrentIndex(int index);
    QWidget *widget(int index) const;

private:
    NavBar *navBar;
};

#endif // NAVBARCONTAINEREXTENSION_H
