#include "left_widget.h"
#include <QPainter>
#include <QMouseEvent>

LeftWidget::LeftWidget(QWidget *parent)
    : QWidget(parent)
{ 
    currentIndex = 0;

    tabNames.insert(0, "词典");
    tabNames.insert(1, "翻译");
    tabNames.insert(2, "关于");

    setFixedWidth(120);
}

void LeftWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.setPen(QPen(QColor("#FFFFFF")));
    painter.setBrush(QColor("#FFFFFF"));
    painter.drawRect(rect());

    QPainterPath separationLinePath;
    separationLinePath.addRect(QRectF(119, 0, 1, this->height()));
    painter.fillPath(separationLinePath, QColor("#E6E6E6"));

    int tabY = 0;
    for (int i=0; i<tabNames.length(); ++i) {
        QString tabName = tabNames.at(i);
        int width = 120;
        int height = 30;

        if (i == currentIndex) {
            QPainterPath tabBackgroundPath;
            tabBackgroundPath.addRect(QRectF(0, tabY, width, height));
            painter.fillPath(tabBackgroundPath, QColor("#D5EDFE"));

            QPainterPath tabLeftLinePath;
            tabLeftLinePath.addRect(QRectF(117, tabY, 2, height));
            painter.fillPath(tabLeftLinePath, QColor("#2CA7F8"));

            painter.setPen(QPen(QColor("#2CA7F8")));
        }else
            painter.setPen(QPen(QColor("#000000")));

        painter.drawText(QRect(40, tabY + 4, width, height), Qt::AlignTop, tabName);

        tabY += height;
    }
}

void LeftWidget::mousePressEvent(QMouseEvent *event)
{
    int prevIndex = currentIndex;

    if (event->y() < 30)
        currentIndex = 0;
    else if (event->y() < 60)
        currentIndex = 1;
    else if (event->y() < 90)
        currentIndex = 2;

    if (prevIndex != currentIndex) {
        emit currentIndexChanged(currentIndex);

        repaint();
    }
}
