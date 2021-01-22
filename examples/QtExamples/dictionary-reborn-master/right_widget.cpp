#include "right_widget.h"
#include <QPainter>

RightWidget::RightWidget(QWidget *parent)
    : QWidget(parent)
{
    layout = new QStackedLayout(this);
    homePage = new HomePage();
    translatePage = new TranslatePage();
    aboutPage = new AboutPage();

    layout->addWidget(homePage);
    layout->addWidget(translatePage);
    layout->addWidget(aboutPage);

    layout->setCurrentIndex(0);
}

void RightWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.setPen(QPen(QColor("#FFFFFF")));
    painter.setBrush(QColor("#FFFFFF"));
    painter.drawRect(rect());
}
