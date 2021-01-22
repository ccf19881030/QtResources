#include "mysliderbutton.h"

mySliderButton::mySliderButton(QWidget *parent) :
    QWidget(parent)
{
    myBGColor1=QColor::fromRgb(46,132,243);
    myBGColor2=QColor::fromRgb(39,110,203);

    m_bForward = true;
    m_bShrink = false;
    m_bVirgin = true;

    m_slideTimer = new QTimer(this);
    m_slideTimer->setInterval(PYSB_SLIDE_TIMER_INTERVAL);
    connect(m_slideTimer,SIGNAL(timeout()),this,SLOT(DoSliding()));

    m_shrinkTimer = new QTimer(this);
    m_shrinkTimer->setInterval(PYSB_SHRINK_TIMER_INTERVAL);
    connect(m_shrinkTimer,SIGNAL(timeout()),this,SLOT(DoShrinking()));

    setFixedHeight(PYSB_HEIGHT);
    setAttribute(Qt::WA_TranslucentBackground);
}

mySliderButton::~mySliderButton()
{

}

void mySliderButton::calcGeo()
{

}

void mySliderButton::mousePressEvent(QMouseEvent *e)
{
    int ItemCnt = m_StrRectPairVec.count();
    QString strText;
    for(int ItemIndex = 0;ItemIndex < ItemCnt ; ItemIndex++)
    {
        if(m_StrRectPairVec.at(ItemIndex).second.contains(e->pos()))
        {
            strText = m_StrRectPairVec.at(ItemIndex).first;
            DEBUG_VAR(strText);

            emit sig_itemClicked(strText);

            m_TargetRect = m_StrRectPairVec.at(ItemIndex).second;

            if(m_TargetRect.width() > m_BarRect.width())
            {
                m_bShrink = false;
            }else{
                m_bShrink = true;
            }

            if(m_TargetRect.topLeft().x() > m_BarRect.topLeft().x() )
            {
                m_bForward = true;
            }else{
                m_bForward = false;
            }

            int distance = m_TargetRect.topLeft().x() - m_BarRect.topLeft().x();
            if(distance < 0)
                distance = 0 - distance;
            QString tmp;
            tmp = QString("%1").arg(distance);
            DEBUG_VAR(tmp);


            SetSlideIncrement(GetSlideIncrementInit((unsigned int)distance)/*PYSB_BAR_SLIDE_INCREMENT_INIT*/);
            m_slideTimer->start();
            FIREUP_SHRINK_TIMER;
        }
    }
}

void mySliderButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing|QPainter::HighQualityAntialiasing);
    drawBg(&painter);
    drawBar(&painter);
    drawText(&painter);
}

void mySliderButton::SetmyBGColor(QColor c1, QColor c2)
{
    myBGColor1=c1;
    myBGColor2=c2;
}

void mySliderButton::drawBar(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);

    QLinearGradient BarGradient(m_BarRect.topLeft(),m_BarRect.bottomLeft());
//    BarGradient.setColorAt(0.0,PYSB_BAR_START_COLOR);
//    BarGradient.setColorAt(1.0,PYSB_BAR_END_COLOR);
    BarGradient.setColorAt(0.0,myBGColor1);
    BarGradient.setColorAt(1.0,myBGColor2);
    painter->setBrush(BarGradient);

    painter->drawRoundedRect(m_BarRect,PYSB_RECT_RADIUS,PYSB_RECT_RADIUS);
    painter->restore();
}

void mySliderButton::drawBg(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);

    QLinearGradient BgGradient(QPoint(0,0),QPoint(0,height()));
    BgGradient.setColorAt(0.0,PYSB_BG_START_COLOR);
    BgGradient.setColorAt(1.0,PYSB_BG_END_COLOR);
    painter->setBrush(BgGradient);
    painter->drawRoundedRect(rect(),PYSB_RECT_RADIUS,PYSB_RECT_RADIUS);


    painter->restore();
}

void mySliderButton::drawText(QPainter *painter)
{
    painter->save();

    painter->setPen(PYSB_TEXT_COLOR);
    QFont textFont;
    textFont.setBold(true);
    painter->setFont(textFont);

    int ItemCnt = m_StrRectPairVec.count();
    qreal initX = 0;
    qreal textWidth = 0;
    QString strText;
    for(int ItemIndex = 0;ItemIndex < ItemCnt ;ItemIndex++)
    {
        strText = m_StrRectPairVec.at(ItemIndex).first;
        textWidth  = fontMetrics().width(strText);
        QPointF topLeft(initX,0);
        QPointF bottomRight(initX + textWidth + 2 * PYSB_EXTRA_SPACE,height());
        QRectF textRect(topLeft,bottomRight);

        m_StrRectPairVec[ItemIndex].second = textRect;
        if(m_bVirgin)
        {
            m_BarRect = textRect;
            m_bVirgin = false;
        }
        painter->drawText(textRect,strText,Qt::AlignVCenter|Qt::AlignHCenter);

        /// increment initX
        initX +=textWidth + 2 * PYSB_EXTRA_SPACE;
    }

    setFixedWidth(initX);
    painter->restore();
}

unsigned int mySliderButton::GetSlideIncrement()
{
    if(m_nInc > 1)
        m_nInc --;

    return m_nInc;
}

void mySliderButton::SetSlideIncrement(unsigned int nInc)
{
    m_nInc = nInc;
}

unsigned int mySliderButton::GetSlideIncrementInit(unsigned int nDistance)
{
    unsigned int n = 1;

    while(1)
    {
        if(n*n>nDistance)
            break;
        else
            n++;
    }

    return n*1.4;
}

void mySliderButton::DoSliding()
{

    qreal BarX = m_BarRect.topLeft().x();
    qreal BarWidth = m_BarRect.width();
    if(m_bForward)
    {
        BarX += GetSlideIncrement()/*PYSB_BAR_SLIDE_INCREMENT*/;
        if(BarX >= m_TargetRect.topLeft().x())
        {
            BarX = m_TargetRect.topLeft().x();
            m_slideTimer->stop();
            //FIREUP_SHRINK_TIMER;
            //SetSlideIncrement(PYSB_BAR_SLIDE_INCREMENT_INIT);
        }
    }else{
        BarX -= GetSlideIncrement()/*PYSB_BAR_SLIDE_INCREMENT*/;
        if(BarX <= m_TargetRect.topLeft().x())
        {
            BarX = m_TargetRect.topLeft().x();
            m_slideTimer->stop();
            //FIREUP_SHRINK_TIMER;
            //SetSlideIncrement(PYSB_BAR_SLIDE_INCREMENT_INIT);
        }
    }

    m_BarRect = QRectF(QPointF(BarX,0),QPointF(BarX + BarWidth,height()));
    update();
}

void mySliderButton::DoShrinking()
{
    qreal BarX = m_BarRect.topLeft().x();
    qreal BarWidth = m_BarRect.width();

    if(m_bShrink)
    {
        BarWidth -= PYSB_BAR_WIDTH_INCREMENT;

        if(BarWidth < m_TargetRect.width())
        {
            m_shrinkTimer->stop();
        }

    }else{
        BarWidth += PYSB_BAR_WIDTH_INCREMENT;

        if(BarWidth > m_TargetRect.width())
        {
            m_shrinkTimer->stop();
        }

    }
    m_BarRect = QRectF(QPointF(BarX,0),QPointF(BarX + BarWidth,height()));
    update();
}

void mySliderButton::addItem(const QString &str)
{
    int ItemCnt = m_StrRectPairVec.count();
    for(int ItemIndex = 0;ItemIndex < ItemCnt ; ItemIndex++)
    {
        if(m_StrRectPairVec.at(ItemIndex).first.toLower() == str.toLower())
        {
            return ;
        }
    }

    m_StrRectPairVec.push_back(qMakePair(str,QRectF()));
    update();

    if(m_StrRectPairVec.count() > 0)
    {
        emit sig_itemClicked(m_StrRectPairVec.at(0).first);
    }

    calcGeo();
}
