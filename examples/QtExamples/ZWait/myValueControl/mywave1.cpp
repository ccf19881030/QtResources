#include "mywave1.h"

myWave1::myWave1(QWidget *parent) :
    QWidget(parent)
{
    this->initVariables();
}

void myWave1::initVariables()
{
    m_nMin = 0;
    m_nMax = 100;
    m_nValue = 0;

    m_headY = 0;
    m_barY = 0;

    m_dropTimer=new QTimer(this);
    m_dropTimer->setInterval(15);
    connect(m_dropTimer,SIGNAL(timeout()),this,SLOT(DoDropHead()));

    m_toolTimer=new QTimer(this);
    m_toolTimer->setInterval(500);
    m_toolTimer->setSingleShot(true);
    connect(m_toolTimer,SIGNAL(timeout()),m_dropTimer,SLOT(start()));

    m_shrinkTimer=new QTimer(this);
    m_shrinkTimer->setInterval(5);
    connect(m_shrinkTimer,SIGNAL(timeout()),this,SLOT(DoShrinkBar()));

    setMaximumWidth(PYI_MAX_WIDTH);

}

void myWave1::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    drawBackground(&painter);
    drawBar(&painter);
    drawHead(&painter);
}

void myWave1::drawBackground(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(QColor(30,30,30));
    painter->drawRect(rect());
    painter->restore();
}

void myWave1::drawBar(QPainter *painter)
{
    painter->save();
    painter->setRenderHints(QPainter::Antialiasing);
    painter->setRenderHints(QPainter::HighQualityAntialiasing);

    QPointF BarRectTopLeft(PYI_EXTRA_SPACE,m_barY);
    QPointF BarRectBottomRight(width() - PYI_EXTRA_SPACE,height());
    QRectF BarRect(BarRectTopLeft,BarRectBottomRight);

    QLinearGradient BarGradient(BarRect.topLeft(),BarRect.topRight());
    BarGradient.setColorAt(0.0,PYI_BAR_START_COLOR);
    BarGradient.setColorAt(0.5,PYI_BAR_END_COLOR);
    BarGradient.setColorAt(1.0,PYI_BAR_START_COLOR);

    painter->setPen(PYI_BAR_START_COLOR);
    painter->setBrush(BarGradient);
    painter->drawRect(BarRect);

    painter->restore();
}

void myWave1::drawHead(QPainter *painter)
{
    painter->save();

    qreal Y = m_headY;

    QPointF HeadRectTopLeft(PYI_EXTRA_SPACE,Y);
    QPointF HeadRectBottomRight(width() - PYI_EXTRA_SPACE,Y - PYI_HEAD_HEIGHT) ;
    QRectF HeadRect(HeadRectTopLeft,HeadRectBottomRight);

    QLinearGradient HeadGradient(HeadRect.topLeft(),HeadRect.topRight());
    HeadGradient.setColorAt(0.0,PYI_BAR_START_COLOR);
    HeadGradient.setColorAt(0.5,PYI_BAR_END_COLOR);
    HeadGradient.setColorAt(1.0,PYI_BAR_START_COLOR);

    painter->setPen(PYI_BAR_START_COLOR);
    painter->setBrush(HeadGradient);
    painter->drawRect(HeadRect);


    painter->restore();
}

void myWave1::DoShrinkBar()
{
    m_barY +=PYI_HEAD_Y_INCREMENT;
    update();
}

void myWave1::DoDropHead()
{
    m_headY +=PYI_HEAD_Y_INCREMENT;


    if(m_headY > height())
    {
        if(m_dropTimer->isActive())
        {
            m_dropTimer->stop();
        }
        m_headY = height();
    }

    update();
}

void myWave1::setRange(int min, int max)
{
    Q_ASSERT(min < max);
    m_nMin = min;
    m_nMax = max;
    update();
}

void myWave1::setValue(int value)
{
    m_nValue = value;
    m_nCurrentValue = value;

    int ValueDiff = m_nMax - m_nMin;

    if(ValueDiff == 0)
    {
        return ;
    }

    if(m_dropTimer->isActive())
    {
        m_dropTimer->stop();
    }

    qreal yIncre = (qreal)height()/ValueDiff;

    m_headY = height() - yIncre * m_nCurrentValue;
    m_barY = m_headY;

    update();
    m_shrinkTimer->start();
    m_toolTimer->start();
}

int myWave1::minimum() const
{
    return m_nMin;
}

int myWave1::maximum() const
{
    return m_nMax;
}

int myWave1::value() const
{
    return m_nValue;
}
