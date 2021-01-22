#include "myvolume.h"

myVolume::myVolume(QWidget *parent) :
        QWidget(parent)
{
    this->initVariables();
}

void myVolume::initVariables()
{
    m_nValue = 0;
}

void myVolume::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);
    drawBg(&painter);
    draw(&painter);
}


void myVolume::drawBg(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(PYV_BG_COLOR);
    painter->drawRect(rect());
    painter->restore();
}

void myVolume::draw(QPainter *painter)
{
    painter->save();

    qreal dY = (qreal)(height() - (PYV_BAR_COUNT + 1 ) * PYV_TOP_SPACE)/PYV_BAR_COUNT;

    qreal initY = PYV_TOP_SPACE;
    for(int BarIndex = 0;BarIndex < PYV_BAR_COUNT;BarIndex++)
    {
       QPointF BarTopLeft(PYV_LEFT_SPACE,initY);
       QPointF BarBottomRight(width() - PYV_LEFT_SPACE,initY + dY);
       QRectF BarRect(BarTopLeft,BarBottomRight);

       QLinearGradient BarGradient(BarRect.topLeft(),BarRect.bottomLeft());
       BarGradient.setColorAt(0.0,PYV_BAR_DEFAULT_END_COLOR);
       BarGradient.setColorAt(0.5,PYV_BAR_DEFAULT_START_COLOR);
       BarGradient.setColorAt(1.0,PYV_BAR_DEFAULT_END_COLOR);

       painter->setPen(Qt::NoPen);
       painter->setOpacity(PYV_OPACITY);
       painter->setBrush(BarGradient);

       painter->drawRoundedRect(BarRect,PYV_RECT_RADIUS,PYV_RECT_RADIUS);

       /// increment initY
       initY += dY + PYV_TOP_SPACE;
    }

    // draw value bar
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setOpacity(1.0);

    QLinearGradient ValueBarGradient(QPointF(0,height() - PYV_TOP_SPACE),QPointF(0,PYV_TOP_SPACE));
    ValueBarGradient.setColorAt(0.0,PYV_BAR_START_COLOR);
    ValueBarGradient.setColorAt(0.5,PYV_BAR_MIDDLE_COLOR);
    ValueBarGradient.setColorAt(1.0,PYV_BAR_END_COLOR);
    painter->setBrush(ValueBarGradient);

    qreal rInitY =  PYV_TOP_SPACE*((PYV_BAR_COUNT - m_nValue) + 1)+(PYV_BAR_COUNT - m_nValue )* dY ;
    for(int ValueIndex = 0;ValueIndex < m_nValue; ValueIndex++)
    {
        QPointF BarTopLeft(PYV_LEFT_SPACE,rInitY);
        QPointF BarBottomRight(width() - PYV_LEFT_SPACE,rInitY + dY);
        QRectF BarRect(BarTopLeft,BarBottomRight);
        painter->drawRoundedRect(BarRect,PYV_RECT_RADIUS,PYV_RECT_RADIUS);

        /// decrement initY
        rInitY += dY + PYV_TOP_SPACE;
    }

    painter->restore();
    painter->restore();
}

void myVolume::DoDecrement()
{

}


void myVolume::setValue(int value)
{
    m_nValue = value;
    update();
}

int myVolume::value() const
{
    return m_nValue;
}

