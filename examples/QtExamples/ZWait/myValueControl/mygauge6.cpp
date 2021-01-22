#include "mygauge6.h"

myGauge6::myGauge6(QWidget *parent) :
    QWidget(parent)
{
    graphcolor=Qt::darkGreen;
    m_currentValue=0;
    m_value=0;
    m_bReverse=false;
    m_bUseAntialiasing=false;
    m_bAnimate=true;
    m_nMin=0;
    m_nMax=100;

    updateTimer=new QTimer(this);
    updateTimer->setInterval(30);
    connect(updateTimer,SIGNAL(timeout()),this,SLOT(UpdateGraph()));

}

void myGauge6::paintEvent(QPaintEvent *)
{
    QPainter painter;
    painter.begin(this);

    if(m_bUseAntialiasing)
    {
        painter.setRenderHints(QPainter::Antialiasing|QPainter::TextAntialiasing);
    }

    drawVariables(&painter);
    drawBackground(&painter);
    drawMark(&painter);
    drawTextRect(&painter);
    drawUnderRect(&painter);
    drawGauge(&painter);

}

void myGauge6::drawVariables(QPainter *painter)
{
   m_leftSpace=(qreal)width()/7;
   m_topSpace=(qreal)height()/10;
   m_long=m_leftSpace/4;
   m_ok=m_long/3;
   m_short=m_long/2;
}

void myGauge6::drawBackground(QPainter *painter)
{
    painter->save();
    QLinearGradient bgGradient(QPointF(0,0),QPointF(0,height()));
    bgGradient.setColorAt(0.0,QColor(30,30,30));
    bgGradient.setColorAt(0.1,QColor(30,30,30));
    bgGradient.setColorAt(0.9,QColor(30,30,30));
    bgGradient.setColorAt(1.0,QColor(30,30,30));

    painter->setPen(Qt::NoPen);
    painter->setBrush(bgGradient);
    painter->drawRect(rect());

    painter->restore();
}

void myGauge6::SetGraphColor(QColor c)
{
    this->graphcolor=c;
}

void myGauge6::drawGauge(QPainter *painter)
{
    painter->save();

    QRectF gaugeRect(m_gaugeTopLeftPot,m_gaugeBottomRightPot);
    QLinearGradient gaugeGradient(gaugeRect.topLeft(),gaugeRect.bottomLeft());
    gaugeGradient.setColorAt(0.0,graphcolor);
    painter->setPen(Qt::NoPen);
    painter->setBrush(gaugeGradient);

    qreal length=gaugeRect.height();
    qreal increment=(qreal)length/(m_nMax-m_nMin);

    qreal value=m_currentValue*increment;

    QPointF graphTopLeftPot(m_gaugeTopLeftPot.x(),m_gaugeBottomRightPot.y()-value);
    QRectF graphRect(graphTopLeftPot,m_gaugeBottomRightPot);
    painter->drawRect(graphRect);
    painter->restore();
}

void myGauge6::drawMark(QPainter *painter)
{
    painter->save();
    // draw vertical line
    painter->setPen(Qt::white);
    QPointF topPot(width()-2*m_leftSpace,m_topSpace);
    m_markX=topPot.x();
    m_markY=topPot.y();
    QPointF bottomPot(width()-2*m_leftSpace,height()-2*m_topSpace);
    m_markBottom=bottomPot.y();
    painter->drawLine(topPot,bottomPot);
    int length=m_nMax-m_nMin;
    qreal increment=(qreal)(height()-3*m_topSpace)/length;

    int value=m_nMax;
    QString strValue;
    qreal startY=topPot.y();

    for(int i=value;i>=m_nMin;i--)
    {
        if(i%10==0)
        {
            strValue=tr("%1").arg(value);
            //qreal textWidth=fontMetrics().width(strValue);
            qreal textHeight=fontMetrics().height();

            QPointF rightPot(topPot.x(),startY);
            QPointF leftPot(topPot.x()-m_long,startY);
            painter->drawLine(rightPot,leftPot);

            QPointF textPot(topPot.x()+m_long,startY+textHeight/2);
            painter->drawText(textPot,strValue);
            value-=10;
        }
        else if(i%5==0)
        {
            QPointF rightPot(topPot.x(),startY);
            QPointF leftPot(topPot.x()-m_ok,startY);
            painter->drawLine(rightPot,leftPot);
        }
        else
        {
            QPointF rightPot(topPot.x(),startY);
            QPointF leftPot(topPot.x()-m_short,startY);
            painter->drawLine(rightPot,leftPot);
        }
        startY+=increment;
    }
    painter->restore();
}

void myGauge6::drawUnderRect(QPainter *painter)
{
    painter->save();
    QLinearGradient rectGradient(m_underRect.topLeft(),m_underRect.topRight());
    rectGradient.setColorAt(0.0,QColor(150,150,150));
    rectGradient.setColorAt(0.1,QColor(100,100,100));
    rectGradient.setColorAt(0.9,QColor(100,100,100));
    rectGradient.setColorAt(1.0,QColor(150,150,150));

    painter->setPen(Qt::NoPen);
    painter->setBrush(rectGradient);
    painter->drawRect(m_underRect);

    painter->restore();
}

void myGauge6::drawTextRect(QPainter *painter)
{
    painter->save();

    QPointF topLeftPot(m_markX-3*m_long-m_leftSpace,m_markBottom+m_long);
    QPointF bottomRightPot(m_markX-2*m_long,m_markBottom+m_leftSpace);

    m_textRect=QRectF(topLeftPot,bottomRightPot);
    painter->setPen(Qt::NoPen);

    QLinearGradient textRectGradient(m_textRect.topLeft(),m_textRect.bottomLeft());
    textRectGradient.setColorAt(0.0,QColor(180,180,180));
    textRectGradient.setColorAt(0.2,QColor(100,100,100));
    textRectGradient.setColorAt(0.8,QColor(100,100,100));
    textRectGradient.setColorAt(1.0,QColor(180,180,180));
    painter->setBrush(textRectGradient);
    painter->drawRect(m_textRect);

    painter->save();
    painter->setPen(Qt::green);
    painter->drawText(m_textRect,Qt::AlignVCenter|Qt::AlignHCenter,tr("%1").arg(m_currentValue));
    painter->restore();

    m_underRect=QRectF(QPointF(topLeftPot.x(),m_markY),QPointF(bottomRightPot.x(),m_markBottom));

    m_gaugeTopLeftPot=QPointF(m_textRect.topLeft().x(),m_markY);
    m_gaugeBottomRightPot=QPointF(m_textRect.bottomRight().x(),m_markBottom);

    painter->restore();
}

void myGauge6::UpdateGraph()
{
    if(m_bReverse)
    {
        m_currentValue-=0.5;
        if(m_currentValue<=m_value)
        {
            updateTimer->stop();
        }
    }
    else
    {
        m_currentValue+=0.5;
        if(m_currentValue>=m_value)
        {
           updateTimer->stop();
        }
    }
    update();
}

void myGauge6::setValue(qreal value)
{
    if(value>m_value)
    {
        m_bReverse=false;
        m_value=value;
    }
    else if(value<m_value)
    {
        m_bReverse=true;
        m_value=value;
    }
    else
    {
        return ;
    }

    if(!m_bAnimate)
    {
        m_currentValue=value;
        update();
        return ;
    }
    updateTimer->start();
}

void myGauge6::setUseAntialiasing(bool use)
{
    m_bUseAntialiasing=use;
    update();
}


void myGauge6::setRange(int min, int max)
{
    m_nMin=min;
    m_nMax=max;
    update();
}

void myGauge6::setAnimating(bool animate)
{
    m_bAnimate=animate;
    update();
}
