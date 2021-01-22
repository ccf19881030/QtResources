#include "mygauge2.h"

myGauge2::myGauge2(QWidget *parent) :
        QWidget(parent)
{
    this->initVariables();
}

void myGauge2::initVariables()
{
    m_outerRadius=width()>height() ? height()/2: width()/2;
    m_innerRadius=m_outerRadius/8*7;
    m_coverCircleRadius=m_outerRadius/8*4+10;
    m_colorCircleRadius=m_outerRadius/8*5;
    m_center=rect().center();
    m_value=0;
    m_currentValue=0;
    updateTimer=new QTimer(this);
    updateTimer->setInterval(10);
    connect(updateTimer,SIGNAL(timeout()),this,SLOT(UpdateGraph()));
    singleTimer=new QTimer(this);
    singleTimer->setInterval(100);
    connect(singleTimer,SIGNAL(timeout()),this,SLOT(update()));
    singleTimer->start();
}

void myGauge2::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing|QPainter::TextAntialiasing);
    resetVariables(&painter);
    drawOuterCircle(&painter);
    drawInnerCircle(&painter);
    drawColorPie(&painter);
    drawCoverCircle(&painter);
    drawMark(&painter);
    drawIndicator(&painter);
    drawCoverBall(&painter);
    drawTextRect(&painter);
    painter.end();
}

void myGauge2::drawOuterCircle(QPainter *painter)
{
    painter->save();

    QRadialGradient outerGradient(m_center,m_outerRadius,m_center);
    outerGradient.setColorAt(0.0,QColor(200,200,200));
    outerGradient.setColorAt(0.9,QColor(80,80,80));
    outerGradient.setColorAt(0.95,QColor(180,180,180));
    outerGradient.setColorAt(1.0,QColor(80,80,80));

    painter->setPen(Qt::NoPen);
    painter->setBrush(outerGradient);
    painter->drawEllipse(m_center,m_outerRadius,m_outerRadius);
    painter->restore();
}

void myGauge2::drawInnerCircle(QPainter *painter)
{
    painter->save();
    QRadialGradient innerGradient(m_center,m_innerRadius,m_center);
    innerGradient.setColorAt(0.0,QColor(130,130,130));
    innerGradient.setColorAt(0.7,QColor(130,130,130));
    innerGradient.setColorAt(1.0,QColor(80,80,80));
    painter->setPen(Qt::NoPen);
    painter->setBrush(innerGradient);
    painter->drawEllipse(m_center,m_innerRadius,m_innerRadius);

    painter->restore();
}

void myGauge2::drawMark(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::white);
    painter->translate(m_center);

    qreal dAngle=(qreal)270/100;
    qreal startAngle=45;
    int value=0;
    QString strValue;
    for(int i=0;i<=100;i++)
    {
        painter->save();
        painter->rotate(startAngle);

        if(i%10==0)
        {
            strValue=tr("%1").arg(value);
            qreal textWidth=fontMetrics().width(strValue);
            qreal textHeight=fontMetrics().height();
            QPointF bottomPot(0,m_colorCircleRadius+SPACE1);
            QPointF topPot(0,m_colorCircleRadius+SPACE1+LONG1);
            painter->drawLine(bottomPot,topPot);
            value+=10;

            painter->save();
            QPointF textPot(0-textWidth/2,m_colorCircleRadius+SPACE1+LONG1+SPACE1+textHeight);
            painter->translate(textPot);
            painter->rotate(180);
            painter->drawText(QPointF(-textWidth,textHeight/2),strValue);
            painter->restore();            
        }
        else if(i%5==0)
        {
            QPointF bottomPot(0,m_colorCircleRadius+SPACE1);
            QPointF topPot(0,m_colorCircleRadius+SPACE1+OK1);
            painter->drawLine(bottomPot,topPot);

        }
        else
        {
            QPointF bottomPot(0,m_colorCircleRadius+SPACE1);
            QPointF topPot(0,m_colorCircleRadius+SPACE1+SHORT1);
            painter->drawLine(bottomPot,topPot);
        }
        painter->restore();
        startAngle+=dAngle;
    }
    painter->restore();
}

void myGauge2::drawCoverBall(QPainter *painter)
{
    painter->save();

    qreal ballRadius=m_outerRadius/7;
    m_coverBallRadius=ballRadius;
    QRadialGradient ballGradient(m_center,ballRadius,m_center);
    ballGradient.setColorAt(0.0,QColor(140,140,140));
    ballGradient.setColorAt(0.7,QColor(140,140,140));
    ballGradient.setColorAt(1.0,QColor(60,60,60));
    painter->setBrush(ballGradient);
    painter->setPen(Qt::NoPen);
    painter->drawEllipse(m_center,ballRadius,ballRadius);

    painter->restore();
}

void myGauge2::drawTextRect(QPainter *painter)
{
    painter->save();
    qreal rectWidth=m_coverCircleRadius/5;

    QPointF topLeftPot(m_center.x()-1.5*rectWidth,m_center.y()+rectWidth*2);
    QPointF bottomRightPot(topLeftPot.x()+3*rectWidth,topLeftPot.y()+rectWidth*2);
    QRectF textRect(topLeftPot,bottomRightPot);

    painter->setPen(Qt::NoPen);
    painter->setBrush(QColor(0,170,255));
    painter->setOpacity(0.6);
    painter->drawRoundRect(textRect,ANGLE1,ANGLE1);

    qreal fontSize=textRect.height()/2;
    QFont font;
    font.setPointSize(fontSize);
    painter->setFont(font);

    painter->setOpacity(1.0);
    painter->setPen(Qt::black);
    QString strValue;
    strValue=tr("%1").arg(m_value);
    painter->drawText(textRect,Qt::AlignHCenter|Qt::AlignVCenter,strValue);
    painter->restore();
}

void myGauge2::drawCoverCircle(QPainter *painter)
{
    painter->save();
    painter->setBrush(QColor(130,130,130));
    painter->setPen(Qt::NoPen);
    painter->drawEllipse(m_center,m_coverCircleRadius,m_coverCircleRadius);
    painter->restore();
}

void myGauge2::drawColorPie(QPainter *painter)
{
    painter->save();

    QPointF topLeftPot(m_center.x()-m_colorCircleRadius,m_center.y()-m_colorCircleRadius);
    QPointF bottomRightPot(m_center.x()+m_colorCircleRadius,m_center.y()+m_colorCircleRadius);
    m_colorCircleRect=QRectF(topLeftPot,bottomRightPot);
    painter->setPen(Qt::NoPen);

    QConicalGradient greenGradient(m_center,m_innerRadius);
    greenGradient.setColorAt(0.0,QColor(0,30,0));
    greenGradient.setColorAt(0.25,QColor(0,230,0));
    greenGradient.setColorAt(1.0,QColor(0,230,0));
    painter->setBrush(Qt::green);
    painter->drawPie(m_colorCircleRect,45*16,180*16);

    painter->setBrush(QColor(218,218,0));
    painter->drawPie(m_colorCircleRect,0*16,45*16);

    painter->setBrush(QColor(240,50,50));
    painter->drawPie(m_colorCircleRect,0,-45*16);

    painter->restore();
}

void myGauge2::drawIndicator(QPainter *painter)
{
    painter->save();

    painter->translate(m_center);
    qreal increment=(qreal)270/100;
    qreal changedAngle=45+increment*m_currentValue;
    painter->rotate(changedAngle);

    QPointF topPot(0,m_colorCircleRadius+LONG1);
    QPointF bottomLeftPot(-m_coverBallRadius/3,0);
    QPointF bottomRightPot(m_coverBallRadius/3,0);
    painter->setPen(Qt::NoPen);

    QLinearGradient indicatorGradient(topPot,bottomLeftPot);
    indicatorGradient.setColorAt(0.0,QColor(236,187,62));
    indicatorGradient.setColorAt(0.5,QColor(220,147,0));
    indicatorGradient.setColorAt(1.0,QColor(236,187,62));

    painter->setBrush(indicatorGradient);
    QVector<QPointF> potVec;
    potVec.push_back(topPot);
    potVec.push_back(bottomLeftPot);
    potVec.push_back(bottomRightPot);

    painter->drawPolygon(potVec);
    painter->restore();
}

void myGauge2::resetVariables(QPainter *painter)
{
    m_outerRadius=width()>height() ? height()/2: width()/2;
    m_innerRadius=m_outerRadius/8*7;
    m_coverCircleRadius=m_outerRadius/8*4+10;
    m_colorCircleRadius=m_outerRadius/8*5;

    m_center=rect().center();
}

void myGauge2::setValue(qreal value)
{
    if(value>m_value)
    {
        m_bReverse=false;
        m_value=value;

        if(!m_bAnimating)
        {
            m_currentValue=m_value;
        }
    }
    else if(value<m_value)
    {
        m_bReverse=true;
        m_value=value;
        if(!m_bAnimating)
        {
            m_currentValue=m_value;
        }
    }
    else
    {
        return ;
    }
    updateTimer->start();
}

void myGauge2::UpdateGraph()
{
    if(!m_bReverse)
    {
        m_currentValue+=0.5;

        if(m_currentValue>=m_value)
        {
            updateTimer->stop();
        }
    }
    else
    {
        m_currentValue-=0.5;
        if(m_currentValue<=m_value)
        {
            updateTimer->stop();
        }
    }
    update();
}
