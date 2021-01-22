#include "mycoolbar.h"

myCoolBar::myCoolBar(QWidget *parent) :
    QWidget(parent)
{
    this->initVariables();
}

void myCoolBar::initVariables()
{
    m_Min=0;
    m_Max=100;
    m_value=0;
    m_indicatorPos=0.0;
    m_pressed=false;
    m_valid=false;
    m_firstRun=true;

    updateTimer=new QTimer(this);
    updateTimer->setInterval(100);
    connect(updateTimer,SIGNAL(timeout()),this,SLOT(update()));
    updateTimer->start();
}

void myCoolBar::setRange(int min, int max)
{
    Q_ASSERT(max>=min);
    m_Min=min;
    m_Max=max;

    int length=m_Max-m_Min;
    m_increment=width()/length;
    update();
}

void myCoolBar::setValue(int value)
{
    m_value=value;
    update();
}

void myCoolBar::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    drawBar(&painter);
    drawFilledRegion(&painter);
    drawIndicator(&painter);
}

void myCoolBar::drawBackground(QPainter *painter)
{
    painter->save();

    QLinearGradient lGradient(QPointF(0,0),QPointF(0,height()));
    lGradient.setColorAt(1.0,QColor(230,230,230));
    lGradient.setColorAt(0.8,QColor(60,60,60));
    lGradient.setColorAt(0.2,QColor(60,60,60));
    lGradient.setColorAt(0.0,QColor(230,230,230));

    painter->setBrush(lGradient);
    painter->drawRect(this->rect());
    painter->restore();
}

void myCoolBar::drawBar(QPainter *painter)
{
    m_increment=width()/(m_Max-m_Min);
    painter->save();
    qreal top=(qreal)(height()-BAR_HEIGHT)/2;
    qreal bottom=top+BAR_HEIGHT;
    QPointF topLeftPot(LEFT_WIDTH,top);
    QPointF bottomRightPot(width()-RIGHT_WIDTH,bottom);
    QRectF barRect(topLeftPot,bottomRightPot);
    m_barRect=barRect;

    QLinearGradient barGradient(barRect.topLeft(),barRect.bottomLeft());
    barGradient.setColorAt(0.0,QColor(230,230,230));
    barGradient.setColorAt(0.2,QColor(120,120,120));
    barGradient.setColorAt(0.5,QColor(230,230,230));
    barGradient.setColorAt(0.0,QColor(230,230,230));
    painter->setBrush(barGradient);

    painter->drawRoundedRect(barRect,RECT_RADIUS,RECT_RADIUS);

    painter->restore();
}

void myCoolBar::drawIndicator(QPainter *painter)
{
    painter->save();

   if(m_firstRun)
    {
        m_indicatorY=m_barRect.center().y();
        m_indicatorX=m_barRect.topLeft().x()+m_indicatorPos+INDICATOR_RADIUS;
        QPointF indicatorCenter(m_indicatorX,m_indicatorY);
        m_lastPot=indicatorCenter;
        m_firstRun=false;
    }
    m_lastPot.setY(m_barRect.center().y());

    QPointF indicatorTopLeftPot(m_lastPot.x()-INDICATOR_RADIUS,m_lastPot.y()-INDICATOR_RADIUS);
    QPointF indicatorBottomRightPot(m_lastPot.x()+INDICATOR_RADIUS,m_lastPot.y()+INDICATOR_RADIUS);

    QRectF indicatorRect(indicatorTopLeftPot,indicatorBottomRightPot);
    m_indicatorRect=indicatorRect;

    QLinearGradient indicatorGradient(indicatorRect.topLeft(),indicatorRect.bottomRight());
    indicatorGradient.setColorAt(0.0,QColor(230,230,230));
    indicatorGradient.setColorAt(0.4,QColor(120,120,120));
    indicatorGradient.setColorAt(1.0,QColor(230,230,230));
    painter->setBrush(indicatorGradient);
    painter->drawEllipse(indicatorRect.center(),INDICATOR_RADIUS,INDICATOR_RADIUS);

   painter->restore();
}

void myCoolBar::drawFilledRegion(QPainter *painter)
{
    if(m_lastPot.x()-m_barRect.x()<=INDICATOR_RADIUS)
    {
        return ;
    }

    painter->save();
    QRectF regionRect(m_barRect.topLeft(),QPointF(m_indicatorRect.center().x(),m_indicatorRect.center().y()+m_barRect.height()/2));
    QLinearGradient regionGradient(regionRect.topLeft(),regionRect.bottomLeft());
    regionGradient.setColorAt(0.0,QColor(80,80,80));
    regionGradient.setColorAt(0.2,QColor(120,120,120));
    regionGradient.setColorAt(0.5,QColor(230,230,230));
    regionGradient.setColorAt(0.8,QColor(120,120,120));
    regionGradient.setColorAt(1.0,QColor(80,80,80));
    painter->setPen(Qt::NoPen);
    painter->setBrush(regionGradient);
    painter->drawRoundedRect(regionRect,RECT_RADIUS,RECT_RADIUS);

    painter->restore();
}

void myCoolBar::mousePressEvent(QMouseEvent *e)
{
    if(e->button() & Qt::LeftButton)
    {
        if(m_indicatorRect.contains(e->pos()))
        {
            m_valid=true;
        }
        update();
    }
}

void myCoolBar::mouseMoveEvent(QMouseEvent *e)
{
    if(m_valid)
    {
        QPointF curPos=e->pos();
        if(curPos.x()<m_barRect.topLeft().x()+INDICATOR_RADIUS/2||curPos.x()>m_barRect.bottomRight().x()-INDICATOR_RADIUS/2)
        {
            return ;
        }

        if(curPos.x()>m_lastPot.x())
        {
            m_lastPot=QPointF(e->pos().x(),m_barRect.center().y());
            update();
        }

        if(curPos.x()<m_lastPot.x())
        {
            m_lastPot=QPointF(e->pos().x(),m_barRect.center().y());
            update();
        }
    }
    update();

}
void myCoolBar::mouseReleaseEvent(QMouseEvent *e)
{
    if(e->button() & Qt::LeftButton)
    {
        m_pressed=false;
        m_valid=false;
        update();
    }
}

void myCoolBar::resizeEvent(QResizeEvent *)
{
    update();
}

