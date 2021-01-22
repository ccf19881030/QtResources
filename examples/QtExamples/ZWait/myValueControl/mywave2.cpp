#include "mywave2.h"
#define BG2

myWave2::myWave2(QWidget *parent) :
    QWidget(parent)
{
    this->initVariables();
}

void myWave2::initVariables()
{
    m_nMin = 0;
    m_nMax = 0;
    m_nCurrentValue = 0;
    m_nValue = 0;
    m_nIncrement = 0;

    m_bReverse = false;

    m_updateTimer=new QTimer(this);
    m_updateTimer->setInterval(PYS_TIMER_INTERVAL);
    connect(m_updateTimer,SIGNAL(timeout()),this,SLOT(UpdateValue()));

    setMaximumWidth(PYS_WIDTH);
}

void myWave2::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    drawBackground(&painter);
    drawSpectrum(&painter);
}

void myWave2::drawBackground(QPainter *painter)
{

#ifdef BG1
    painter->save();
    painter->setPen(Qt::NoPen);

    QPointF TopRectTopLeft(0,0);
    QPointF TopRectBottomRight(width(),height()/2);
    QRectF TopRect(TopRectTopLeft,TopRectBottomRight);
    PYS_APPLY_LINEAR_GRADIENT(TopRect,TopRect.topLeft(),TopRect.bottomLeft(),PYS_BG_END_COLOR ,PYS_BG_START_COLOR);
    painter->drawRect(TopRect);

    QPointF BottomRectTopLeft(0,height()/2);
    QPointF BottomRectBottomRight(width(),height());
    QRectF BottomRect(BottomRectTopLeft,BottomRectBottomRight);
    PYS_APPLY_LINEAR_GRADIENT(BottomRect,BottomRect.topLeft(),BottomRect.bottomLeft(),PYS_BG_START_COLOR,PYS_BG_END_COLOR)
    painter->drawRect(BottomRect);

    painter->restore();
#endif

#ifdef BG2
    painter->save();
    painter->setPen(QColor(50,50,50));
    painter->setBrush(QColor(50,50,50));
    painter->drawRect(rect());
    painter->restore();
#endif

#ifdef BG3
#include <QRadialGradient>
    QRadialGradient BgGradient(rect().center(),width() > height() ? height()/2:width(),rect().center());
    BgGradient.setColorAt(0.0,QColor(156,156,156));
    BgGradient.setColorAt(1.0,QColor(60,60,60));
    painter->setBrush(BgGradient);
    painter->setPen(Qt::NoPen);
    painter->drawRect(rect());
#endif
}

void myWave2::drawSpectrum(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);

    qreal CenterY = (qreal) rect().center().y();


    qreal HalfHeight = (qreal) height()/2 - PYS_TOP_SPACE ;
    int Range = m_nMax - m_nMin;
    qreal YIncrement = (qreal)HalfHeight/Range;
    // draw top bar
    qreal TopRectY = YIncrement * m_nCurrentValue ;
    QPointF TopRectTopLeft(PYS_LEFT_SPACE, HalfHeight - TopRectY + PYS_TOP_SPACE );
    QPointF TopRectBottomRight(width()- PYS_LEFT_SPACE,CenterY);
    QRectF TopRect(TopRectTopLeft,TopRectBottomRight);

    QLinearGradient TopRectGradient(TopRect.topLeft(),TopRect.topRight());
    TopRectGradient.setColorAt(0.0,PYS_BAR_END_COLOR);
    TopRectGradient.setColorAt(0.5,PYS_BAR_START_COLOR);
    TopRectGradient.setColorAt(1.0,PYS_BAR_END_COLOR);
    painter->setBrush(TopRectGradient);

    painter->drawRect(TopRect);


    // draw bottom bar
    qreal BottomRectY = CenterY + YIncrement * m_nCurrentValue;
    QPointF BottomRectTopLeft(PYS_LEFT_SPACE,CenterY);
    QPointF BottomRectBottomRight(width() - PYS_LEFT_SPACE,BottomRectY);
    QRectF BottomRect(BottomRectTopLeft,BottomRectBottomRight);

    QLinearGradient BottomRectGradient(BottomRect.topLeft(),BottomRect.topRight());
    BottomRectGradient.setColorAt(0.0,PYS_BAR_END_COLOR);
    BottomRectGradient.setColorAt(0.5,PYS_BAR_START_COLOR);
    BottomRectGradient.setColorAt(1.0,PYS_BAR_END_COLOR);
    painter->setBrush(BottomRectGradient);

    painter->drawRect(BottomRect);


    painter->restore();
}

void myWave2::setRange(int min, int max)
{
    m_nMin = min < max ? min : max;
    m_nMax = max > min ? max : min;

    m_nIncrement = ( m_nMax - m_nMin )/ PYS_INCREMENT_FACTOR;
}

void myWave2::setMinimum(int min)
{
    m_nMin = min;
}

void myWave2::setMaximum(int max)
{
    m_nMax = max;
}

void myWave2::setValue(int value)
{
    if(m_nValue > value )
    {
        m_bReverse = true;
    }else if(m_nValue < value )
    {
        m_bReverse = false;
    }else{
        STOP_TIMER(m_updateTimer);
        return ;
    }

    m_nValue = value;

//    DEBUG_VAR(m_nValue);

    STOP_TIMER(m_updateTimer);
    m_updateTimer->start();
}

void myWave2::UpdateValue()
{
    if(m_bReverse)
    {
        m_nCurrentValue -= m_nIncrement;

        if(m_nCurrentValue < m_nValue)
        {
            m_nCurrentValue = m_nValue;
            STOP_TIMER(m_updateTimer);
        }
    }else{
        m_nCurrentValue += m_nIncrement;

        if(m_nCurrentValue > m_nValue)
        {
            m_nCurrentValue = m_nValue;
            STOP_TIMER(m_updateTimer);
        }
    }

    update();
}
