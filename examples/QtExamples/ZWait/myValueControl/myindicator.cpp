#include "myindicator.h"

myIndicator::myIndicator(QWidget *parent) :
        QWidget(parent)
{
    this->initVariables();
}

void myIndicator::initVariables()
{
    for(int i = 0;i < INDICATOR_COUNT; i++)
    {
        lcd[i]=new myLCDNumber(this);
    }
    m_value=0;
    m_currValue=0;
    m_bReverse=false;

    m_topSpace=0;
    m_leftSpace=0;
    m_lcdWidth=0;
    m_lcdHeight=0;
    forecolor=Qt::darkGreen;

    updateTimer=new QTimer(this);
    updateTimer->setInterval(10);
    connect(updateTimer,SIGNAL(timeout()),this,SLOT(UpdateData()));
}


void myIndicator::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);
    drawVariables(&painter);
    drawBackground(&painter);
    drawLCDNums(&painter);
    drawRect(&painter);
    drawGraph(&painter);
    drawBars(&painter);
}

void myIndicator::drawVariables(QPainter *painter)
{
    m_leftSpace=width()/10;
    m_topSpace=height()/25;
    m_lcdWidth=(width()-(width()/5))/3;
    m_lcdHeight=height()/12;

    QPointF topLeftPot(m_leftSpace,m_topSpace);
    m_rectTopLeft=topLeftPot;
    QPointF bottomRightPot(width()-m_leftSpace,height()-2*m_topSpace-m_lcdHeight);
    m_rectBottomRight=bottomRightPot;
}

void myIndicator::drawBackground(QPainter* painter)
{
    painter->save();

    QLinearGradient bgGradient(QPointF(0,0),QPointF(width(),0));
    bgGradient.setColorAt(0.0,QColor(30,30,30));
    bgGradient.setColorAt(0.1,QColor(30,30,30));
    bgGradient.setColorAt(0.9,QColor(30,30,30));
    bgGradient.setColorAt(1.0,QColor(30,30,30));

    painter->setPen(Qt::NoPen);
    painter->setBrush(bgGradient);
    painter->drawRect(rect());
    painter->restore();
}

void myIndicator::drawLCDNums(QPainter* painter)
{
    painter->save();

    int topLeftX=width()/10;
    int topLeftY=height()-m_topSpace-m_lcdHeight;
    QPointF topLeft(topLeftX,topLeftY);

    for(int i=0;i<INDICATOR_COUNT;i++)
    {
        lcd[i]->resize(m_lcdWidth,m_lcdHeight);
        lcd[i]->move(QPoint(topLeftX,topLeftY));
        topLeftX+=m_lcdWidth;
    }
    painter->restore();
}

void myIndicator::drawRect(QPainter* painter)
{
    painter->save();
    QRectF theRect(m_rectTopLeft,m_rectBottomRight);
    painter->setPen(QPen(INDICATOR_FRAME_COLOR,INDICATOR_PEN_WIDTH));
    painter->setBrush(QBrush(INDICATOR_FRAME_COLOR,Qt::Dense4Pattern));
    painter->drawRect(theRect);
    painter->restore();
}

void myIndicator::SetForeColor(QColor c)
{
    this->forecolor=c;
}

void myIndicator::drawGraph(QPainter *painter)
{
    painter->save();
    painter->setPen(QPen(Qt::transparent,INDICATOR_PEN_WIDTH));

    QLinearGradient graphGradient(m_rectTopLeft,QPointF(m_rectTopLeft.x(),m_rectBottomRight.y()));
    graphGradient.setColorAt(0.0,forecolor);
    painter->setBrush(graphGradient);

    qreal dY=(qreal)(m_rectTopLeft.y()-m_rectBottomRight.y())/100;

    qreal yValue=dY*m_currValue;

    QPointF topLeftPot(m_rectTopLeft.x()+INDICATOR_PEN_WIDTH,m_rectBottomRight.y()+yValue);
    QPointF bottomRightPot(m_rectBottomRight.x()-INDICATOR_PEN_WIDTH,m_rectBottomRight.y());
    QRectF graphRect(topLeftPot,bottomRightPot);
    painter->drawRect(graphRect);

    QString strCurrValue;
    strCurrValue=tr("%1").arg((m_currValue));
    if(m_currValue<10)
    {
        lcd[0]->setNumber(0);
        lcd[1]->setNumber(0);
        lcd[2]->setNumber(m_currValue);
    }
    else if(m_currValue < 100 && m_currValue >= 10)
    {
        lcd[0]->setNumber(0);
        lcd[1]->setNumber(strCurrValue.at(0).digitValue());
        lcd[2]->setNumber(strCurrValue.at(1).digitValue());
    }
    else
    {
        lcd[0]->setNumber(1);
        lcd[1]->setNumber(0);
        lcd[2]->setNumber(0);
    }
    painter->restore();
}

void myIndicator::drawBars(QPainter* painter)
{
    painter->save();
    painter->setPen(QPen(INDICATOR_FRAME_COLOR,INDICATOR_PEN_WIDTH));

    qreal left=m_rectTopLeft.x();
    qreal right=m_rectBottomRight.x();

    qreal top=m_rectTopLeft.y();
    qreal bottom=m_rectBottomRight.y();
    qreal increment=(bottom-top)/10;

    while(top<bottom)
    {
        QPointF leftPot(left,top);
        QPointF rightPot(right,top);
        painter->drawLine(leftPot,rightPot);
        top+=increment;
    }
    painter->restore();

}

void myIndicator::UpdateData()
{
    if(m_bReverse)
    {
        m_currValue--;

        if(m_currValue<=m_value)
        {
            updateTimer->stop();
        }
    }
    else
    {
        m_currValue++;

        if(m_currValue>=m_value)
        {
            updateTimer->stop();
        }
    }
    update();
}


void myIndicator::setValue(int value)
{
    if(m_value==value)
    {
        return ;
    }

    if(value>m_value)
    {
        m_bReverse=false;
    }else{
        m_bReverse=true;
    }
    m_value=value;

    updateTimer->start();
}
