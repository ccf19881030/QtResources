#include "mygauge4.h"

LinearGradient::LinearGradient(QObject *parent) :
    QObject(parent)
{
}

QLinearGradient LinearGradient::GetGradient(const QPointF &startPos, const QPointF &endPos, const QColor &clr)
{
    QLinearGradient gradient(startPos,endPos);
    int red=clr.red();
    int green=clr.green();
    int blue=clr.blue();

    int startRed=red-INCREMENT2>=0 ? red-INCREMENT2 : 0;
    int startGreen=green-INCREMENT2>0 ? green-INCREMENT2 : 0;
    int startBlue=blue-INCREMENT2 >0? blue-INCREMENT2 : 0;

    QColor startClr(startRed,startGreen,startBlue);

    int endRed=red+INCREMENT2 < 255 ? red+INCREMENT2 : 255;
    int endGreen= green+INCREMENT2 < 255 ? green+INCREMENT2 : 255 ;
    int endBlue= blue+INCREMENT2 < 255 ? blue+INCREMENT2 : 255;

    QColor endClr(endRed,endGreen,endBlue);

    gradient.setColorAt(0.0,endClr);
    gradient.setColorAt(0.5,clr);
    gradient.setColorAt(1.0,endClr);

    return gradient;
}

myGauge4::myGauge4(QWidget *parent) :
    QWidget(parent)
{
    this->mylinecolor=Qt::red;
    m_rectHeight=0;
    m_markLength=0;
    m_value=0;
    m_currentValue=0;
    m_bReverse=false;
    updateTimer=new QTimer(this);
    updateTimer->setInterval(10);
    connect(updateTimer,SIGNAL(timeout()),this,SLOT(UpdateGraph()));
}

void myGauge4::setValue(qreal value)
{
    if(m_value<value)
    {
        m_bReverse=false;
    }
    else if(m_value>value)
    {
        m_bReverse=true;
    }
    else
    {
        return ;
    }
    m_value=value;
    updateTimer->start();
    update();
}

void myGauge4::paintEvent(QPaintEvent *)
{
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);
    drawTopBottomRects(&painter);
    drawMark(&painter);
    drawIndicator(&painter);
    painter.end();
}

void myGauge4::drawTopBottomRects(QPainter *painter)
{
    painter->save();
    m_rectHeight=height()/6;

    QPointF topLeftPot1(0,0);
    QPointF bottomRightPot1(width(),m_rectHeight);
    m_topRect=QRectF(topLeftPot1,bottomRightPot1);
    QLinearGradient topRectGradient(m_topRect.topLeft(),m_topRect.bottomLeft());    
    topRectGradient.setColorAt(0.0,QColor(180,180,180));
    topRectGradient.setColorAt(1.0,QColor(80,80,80));
    painter->setBrush(topRectGradient);
    painter->drawRect(m_topRect);

    QPointF topLeftPot2(0,height()-m_rectHeight);
    QPointF bottomRightPot2(width(),height());
    m_bottomRect=QRectF(topLeftPot2,bottomRightPot2);
    QLinearGradient bottomRectGradient(m_bottomRect.topLeft(),m_bottomRect.bottomLeft());
    bottomRectGradient.setColorAt(0.0,QColor(80,80,80));
    bottomRectGradient.setColorAt(1.0,QColor(180,180,180));
    painter->setBrush(bottomRectGradient);
    painter->drawRect(m_bottomRect);

    QPointF topLeftPot3(0,m_rectHeight);
    QPointF bottomRightPot3(width(),height()-m_rectHeight);
    m_middleRect=QRectF(topLeftPot3,bottomRightPot3);
    painter->setBrush(lg.GetGradient(m_middleRect.topLeft(),m_middleRect.bottomLeft(),QColor(90,90,90)));
    painter->drawRect(m_middleRect);

    painter->restore();
}

void myGauge4::SetmyLineColor(QColor c)
{
    this->mylinecolor=c;
}

void myGauge4::drawIndicator(QPainter *painter)
{
    painter->save();

    QPointF topPot(SPACE2+m_currentValue*m_increment,m_topY-TOP_SPACE2);
    QPointF bottomPot(SPACE2+m_currentValue*m_increment,m_bottomY+TOP_SPACE2);
    painter->setPen(this->mylinecolor);
    painter->drawLine(topPot,bottomPot);
    painter->restore();
}

void myGauge4::drawMark(QPainter *painter)
{
    painter->save();
    m_markLength=m_middleRect.width()-2*SPACE2;
    m_length=m_markLength;
    qreal middleRectY1=m_middleRect.topLeft().y();
    m_topY=middleRectY1+TOP_SPACE2;
    qreal middleRectY2=m_middleRect.bottomLeft().y();
    m_bottomY=middleRectY2-TOP_SPACE2;

    qreal startX=m_middleRect.x()+SPACE2;
    m_startX=startX;
    qreal endX=m_middleRect.bottomRight().x()-SPACE2;
    qreal dx=m_markLength/100;
    m_increment=dx;
    painter->setPen(Qt::black);
    // draw two horizontal lines
    QPointF topLeftPot(startX,m_topY);
    QPointF topRightPot(endX,m_topY);
    painter->drawLine(topLeftPot,topRightPot);

    QPointF bottomLeftPot(startX,m_bottomY);
    QPointF bottomRightPot(endX,m_bottomY);
    painter->drawLine(bottomLeftPot,bottomRightPot);

    int value=0;
    int fontHeight=fontMetrics().height();

    for(int i=0;i<=100;i++)
    {
        if(i%10==0)
        {
            QPointF topPot(startX,m_topY);
            QPointF bottomPot(startX,m_topY+LONG2);
            painter->drawLine(topPot,bottomPot);

            QPointF topPot1(startX,m_bottomY);
            QPointF bottomPot1(startX,m_bottomY-LONG2);
            painter->drawLine(topPot1,bottomPot1);

            QString strValue;
            strValue=tr("%1").arg(value);
            int fontWidth=fontMetrics().width(strValue)/2;
            painter->drawText(QPointF(startX-fontWidth,m_topY+fontHeight+LONG2),strValue);
            painter->drawText(QPointF(startX-fontWidth,m_bottomY-fontHeight),strValue);
            value+=10;

        }
        else  if(i%5==0)
        {
            QPointF topPot(startX,m_topY);
            QPointF bottomPot(startX,m_topY+OK2);
            painter->drawLine(topPot,bottomPot);
            QPointF topPot1(startX,m_bottomY);
            QPointF bottomPot1(startX,m_bottomY-OK2);
            painter->drawLine(topPot1,bottomPot1);

        }
        else
        {
            QPointF topPot(startX,m_topY);
            QPointF bottomPot(startX,m_topY+SHORT2);
            painter->drawLine(topPot,bottomPot);
            QPointF topPot1(startX,m_bottomY);
            QPointF bottomPot1(startX,m_bottomY-SHORT2);
            painter->drawLine(topPot1,bottomPot1);
        }
        startX+=dx;
    }
    painter->restore();
}

void myGauge4::UpdateGraph()
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
