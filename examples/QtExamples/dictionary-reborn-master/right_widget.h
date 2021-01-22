#ifndef RIGHTWIDGET_H
#define RIGHTWIDGET_H

#include <QWidget>
#include <QStackedLayout>
#include "home_page.h"
#include "translate_page.h"
#include "about_page.h"

class RightWidget : public QWidget
{
    Q_OBJECT

public:
    RightWidget(QWidget *parent = 0);

    QStackedLayout *layout;

protected:
    void paintEvent(QPaintEvent *);

private:
    HomePage *homePage;
    TranslatePage *translatePage;
    AboutPage *aboutPage;
};

#endif // RIGHTWIDGET_H
