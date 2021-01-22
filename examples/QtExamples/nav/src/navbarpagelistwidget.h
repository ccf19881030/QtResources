#ifndef NAVBARPAGELIST_H
#define NAVBARPAGELIST_H

#include <QWidget>
#include <QList>
#include <QToolButton>

class NavBar;

class NavBarButton: public QToolButton
{
    Q_OBJECT

public:
    explicit NavBarButton(QWidget *parent);
};

class NavBarPageListWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int rowHeight READ rowHeight WRITE setRowHeight)

public:
    explicit NavBarPageListWidget(NavBar *parent);
    ~NavBarPageListWidget();

    int  rowHeight() const;
    void setRowHeight(int newHeight);
    void layoutButtons(int width);

signals:
    void buttonVisibilityChanged(int visCount);

protected:
    void resizeEvent(QResizeEvent *e);

private:
    NavBar *navBar;
    int     pageButtonHeight;
};

#endif // NAVBARPAGELIST_H
