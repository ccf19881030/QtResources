#include "myprogressbar.h"

myProgressBar::myProgressBar(QWidget *parent) :
    QWidget(parent)
{
    this->initVariables();
}

void myProgressBar::initVariables()
{
    m_nCurrentIndex=0;
    m_nRectCount=(width()-2*TOP_SPACE)/RECT_WIDTH;
    updateTimer=new QTimer(this);
    updateTimer->setInterval(100);
    m_bReverse=false;
    connect(updateTimer,SIGNAL(timeout()),this,SLOT(UpdateGraph()));
    start();
}

void myProgressBar::paintEvent(QPaintEvent *)
{
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);
    drawBackground(&painter);
    drawRects(&painter);
    painter.end();
}

void myProgressBar::drawBackground(QPainter *painter)
{
    painter->save();

    QLinearGradient bgGradient(QPointF(0,0),QPointF(0,height()));

    bgGradient.setColorAt(0.0,QColor(180,180,180));
    bgGradient.setColorAt(0.2,QColor(30,30,30));
    bgGradient.setColorAt(0.8,QColor(30,30,30));
    bgGradient.setColorAt(1.0,QColor(180,180,180));
    painter->setBrush(Qt::black);
    painter->setPen(Qt::black);
    painter->drawRoundRect(rect(),0,0);
    painter->restore();
}

void myProgressBar::drawRects(QPainter *painter)
{
    painter->save();

    qreal initX=LEFT_SPACE;
    qreal top=TOP_SPACE;
    qreal bottom=height()-TOP_SPACE;
    m_nRectCount=(width()-2*TOP_SPACE)/RECT_WIDTH;

    for(int i=0;i<m_nRectCount-1;i++)
    {
        QPointF topLeftPot(initX,top);
        QPointF bottomRightPot(initX+RECT_WIDTH,bottom);
        QRectF  singleRect(topLeftPot,bottomRightPot);
        QLinearGradient rectGradient(singleRect.topLeft(),singleRect.topRight());
        painter->setPen(Qt::NoPen);

        if(!m_bReverse)
        {
            if(i==m_nCurrentIndex)
            {
                rectGradient.setColorAt(0.0,QColor(30,100,30));
                rectGradient.setColorAt(0.2,QColor(30,180,30));
                rectGradient.setColorAt(0.8,QColor(30,180,30));
                rectGradient.setColorAt(1.0,QColor(30,100,30));


            }
            else if(i==(m_nCurrentIndex-1))
            {
                rectGradient.setColorAt(0.0,QColor(30,100,30));
                rectGradient.setColorAt(0.2,QColor(30,150,30));
                rectGradient.setColorAt(0.8,QColor(30,150,30));
                rectGradient.setColorAt(1.0,QColor(30,100,30));

            }
            else if(i==(m_nCurrentIndex-2))
            {
                rectGradient.setColorAt(0.0,QColor(30,100,30));
                rectGradient.setColorAt(0.2,QColor(30,120,30));
                rectGradient.setColorAt(0.8,QColor(30,120,30));
                rectGradient.setColorAt(1.0,QColor(30,100,30));

            }
            else if(i==(m_nCurrentIndex-3))
            {
                rectGradient.setColorAt(0.0,QColor(30,100,30));
                rectGradient.setColorAt(0.2,QColor(30,90,30));
                rectGradient.setColorAt(0.8,QColor(30,90,30));
                rectGradient.setColorAt(1.0,QColor(30,100,30));

            }
            else
            {
                rectGradient.setColorAt(0.0,QColor(150,150,150));
                rectGradient.setColorAt(0.2,QColor(30,30,30));
                rectGradient.setColorAt(0.8,QColor(30,30,30));
                rectGradient.setColorAt(1.0,QColor(150,150,150));
            }
        }
        else
        {
            if(i==m_nCurrentIndex)
            {
                rectGradient.setColorAt(0.0,QColor(30,100,30));
                rectGradient.setColorAt(0.2,QColor(30,180,30));
                rectGradient.setColorAt(0.8,QColor(30,180,30));
                rectGradient.setColorAt(1.0,QColor(30,100,30));


            }
            else if(i==(m_nCurrentIndex+1))
            {
                rectGradient.setColorAt(0.0,QColor(30,100,30));
                rectGradient.setColorAt(0.2,QColor(30,150,30));
                rectGradient.setColorAt(0.8,QColor(30,150,30));
                rectGradient.setColorAt(1.0,QColor(30,100,30));

            }
            else if(i==(m_nCurrentIndex+2))
            {
                rectGradient.setColorAt(0.0,QColor(30,100,30));
                rectGradient.setColorAt(0.2,QColor(30,120,30));
                rectGradient.setColorAt(0.8,QColor(30,120,30));
                rectGradient.setColorAt(1.0,QColor(30,100,30));

            }
            else if(i==(m_nCurrentIndex+3))
            {
                rectGradient.setColorAt(0.0,QColor(30,100,30));
                rectGradient.setColorAt(0.2,QColor(30,90,30));
                rectGradient.setColorAt(0.8,QColor(30,90,30));
                rectGradient.setColorAt(1.0,QColor(30,100,30));

            }
            else
            {
                rectGradient.setColorAt(0.0,QColor(150,150,150));
                rectGradient.setColorAt(0.2,QColor(30,30,30));
                rectGradient.setColorAt(0.8,QColor(30,30,30));
                rectGradient.setColorAt(1.0,QColor(150,150,150));
            }

        }
        painter->setBrush(rectGradient);
        painter->drawRoundedRect(singleRect,SMALL_ANGLE,SMALL_ANGLE);

        initX+=RECT_WIDTH+RECT_SPACE;
    }
    painter->restore();
}

void myProgressBar::UpdateGraph()
{
    if(!m_bReverse)
    {
        m_nCurrentIndex=(++m_nCurrentIndex)%m_nRectCount;

        if(m_nCurrentIndex==m_nRectCount-1)
        {
            m_bReverse=true;
        }
    }
    else
    {
        m_nCurrentIndex=(--m_nCurrentIndex)%m_nRectCount;
        if(m_nCurrentIndex==0)
        {
            m_bReverse=false;
        }
    }
    update();
}

void myProgressBar::start()
{
    updateTimer->start();
}

void myProgressBar::stop()
{
    updateTimer->stop();
}

void myProgressBar::setInterval(int msec)
{
    updateTimer->setInterval(msec);
}
