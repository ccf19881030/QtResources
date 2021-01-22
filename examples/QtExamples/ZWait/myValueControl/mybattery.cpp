#include "mybattery.h"

myBattery::myBattery(QWidget *parent) :
        QWidget(parent)
{
    m_bReverse=false;
    m_value=100;
    updateTimer=new QTimer(this);
    updateTimer->setInterval(5);
    connect(updateTimer,SIGNAL(timeout()),this,SLOT(UpdateGraph()));
}

void myBattery::paintEvent(QPaintEvent *e)
{
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);
    drawFrame(&painter);
    drawBattery(&painter);
    painter.end();
}
void myBattery::drawFrame(QPainter *painter)
{
    painter->save();
    m_headWidth=width()/20;
    qreal batteryWidth=width()-m_headWidth;

    QPointF topLeftPot(0,0);
    QPointF bottomRightPot(batteryWidth,height());
    QRectF batteryRect(topLeftPot,bottomRightPot);
    m_batteryRect=batteryRect;
    painter->setBrush(Qt::NoBrush);
    painter->setPen(QPen(Qt::black,2));
    painter->drawRect(batteryRect);

    QPointF headRectTopLeft(batteryRect.topRight().x(),height()/4);
    QPointF headRectBottomRight(width(),height()-height()/4);
    QRectF headRect(headRectTopLeft,headRectBottomRight);
    QLinearGradient headRectGradient(headRect.topLeft(),headRect.bottomLeft());
    headRectGradient.setColorAt(0.0,QColor(150,150,150));
    headRectGradient.setColorAt(0.5,QColor(220,220,220));
    headRectGradient.setColorAt(1.0,QColor(150,150,150));

    painter->setBrush(headRectGradient);
    painter->drawRect(headRect);

    painter->restore();
}

void myBattery::drawBattery(QPainter *painter)
{
    painter->save();

    QLinearGradient batteryGradient(QPointF(0,0),QPointF(0,height()));

    if(m_value<20)
    {
        batteryGradient.setColorAt(0.0,QColor(220,220,220));
        batteryGradient.setColorAt(0.7,QColor(180,50,50));
        batteryGradient.setColorAt(1.0,QColor(120,50,50));

    }
    else
    {
        batteryGradient.setColorAt(0.0,QColor(220,220,220));
        batteryGradient.setColorAt(0.7,QColor(0,180,0));
        batteryGradient.setColorAt(1.0,QColor(0,120,0));
    }
    painter->setPen(Qt::NoPen);
    painter->setBrush(batteryGradient);
    QPointF topLeftPot(m_batteryRect.topLeft().x()+2,m_batteryRect.topLeft().y()+2);

    qreal unit=m_batteryRect.width()/100;
    qreal wid=m_value*unit;
    QPointF bottomRightPot(wid,m_batteryRect.bottomRight().y()-2);
    painter->drawRect(QRectF(topLeftPot,bottomRightPot));

    painter->restore();

}

void myBattery::UpdateGraph()
{
    if(m_bReverse)
    {
        m_value-=0.1;

        if(m_value<=m_currentValue)
        {
            updateTimer->stop();
        }
    }
    else
    {
        m_value+=0.1;
        if(m_value>=m_currentValue)
        {
            updateTimer->stop();
        }
    }
    emit valueChanged(m_value);

    update();
}

void myBattery::setValue(qreal value)
{
    if(value<0 || value>100)
    {
        qWarning() << "The value must be between 0 and 100 !";
        return ;
    }
    if(value > m_value)
    {
        m_bReverse=false;
    }
    else if(value<m_value)
    {
        m_bReverse=true;
    }
    else
    {
        return ;
    }
    updateTimer->start();
    m_currentValue=value;

    update();
}
