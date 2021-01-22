#include "myflashlist.h"

myFlashList::myFlashList(QWidget *parent) :
    QWidget(parent)
{
    initVars();
    initWgts();
    initStgs();
    initConns();
}

myFlashList::~myFlashList()
{
    d->clear();
}

void myFlashList::initVars()
{
}

void myFlashList::initWgts()
{
    mainLayout = new QHBoxLayout(this);
    scrollbar = new QScrollBar(this);
    d = new PYFlashListPrivate(this);

    mainLayout->addWidget(d);
    mainLayout->addWidget(scrollbar);
    setLayout(mainLayout);
}

void myFlashList::initStgs()
{
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);

    scrollbar->setRange(0,0);
    scrollbar->hide();

}

void myFlashList::initConns()
{
    connect(scrollbar,SIGNAL(valueChanged(int)),d,SLOT(setCurrentIndex(int)));
    connect(d,SIGNAL(sig_setMaximum(int)),this,SLOT(setMaximum(int)));
    connect(d,SIGNAL(sig_setCurrentIndex(int)),scrollbar,SLOT(setValue(int)));
    connect(d,SIGNAL(sig_itemClicked(QString)),this,SIGNAL(sig_itemClicked(QString)));
}

void myFlashList::calcGeo()
{

}


void myFlashList::setMaximum(int max)
{
    if(max == 0)
    {
        scrollbar->hide();
    }else{
        scrollbar->show();
    }
    scrollbar->setRange(0,max);

}


void myFlashList::resizeEvent(QResizeEvent *)
{

}


void myFlashList::addItem(const QString &str)
{
    d->addItem(str);
}

void myFlashList::clear()
{
    d->clear();
}

void myFlashList::render()
{
    d->render();
}


PYFlashListPrivate::PYFlashListPrivate(QWidget* parent):QWidget(parent)
{
   initVars();
   initSettings();
}

void PYFlashListPrivate::initVars()
{
   m_currIndex = 0;
   m_VisibleItemCnt = 0;
   m_ItemCounter = 0;

   m_bAllJobsDone = false;

   m_RotateTimer = new QTimer(this);
   m_RotateTimer->setInterval(UPDATE_TIMER_INTERVAL);
   connect(m_RotateTimer,SIGNAL(timeout()),this,SLOT(DoRotation()));

   m_ItemCountTimer = new QTimer(this);
   m_ItemCountTimer->setInterval(ITEM_COUNTER_TIMER_INTERVAL);
   connect(m_ItemCountTimer,SIGNAL(timeout()),this,SLOT(UpdateItemCount()));
}

void PYFlashListPrivate::initSettings()
{
    setMouseTracking(this);
}

void PYFlashListPrivate::calcGeo()
{
    m_VisibleItemCnt = height()/ ITEM_HEIGHT + 1;
    int InvisibleItemCnt = m_IIVec.count() - m_VisibleItemCnt;

    if(InvisibleItemCnt >= 0)
    {
        emit sig_setMaximum(InvisibleItemCnt);
    }
}

void PYFlashListPrivate::makeupJobs()
{
    int Guard = 0;
    for(int index = m_currIndex; index < m_IIVec.count() ;index++)
    {
        if(Guard++ > m_VisibleItemCnt)
        {
            break;
        }

        if(!m_IIVec.at(index).jobDone())
        {
            if(!m_RotateTimer->isActive())
            {
                m_RotateTimer->start();
                m_ItemCountTimer->start();
                break ;
            }
        }
    }

    // reset items which is before the current index 's angle
    for(int index = 0;index < m_currIndex ; index++)
    {
            m_IIVec[index].resetAngle();
    }

    // reset items which is after the visible item's angle
    if((m_currIndex + m_VisibleItemCnt) < m_IIVec.count())
    {
        for(int index  = (m_currIndex + m_VisibleItemCnt);index < m_IIVec.count();index++)
        {
                m_IIVec[index].resetAngle();
        }
    }

}

void PYFlashListPrivate::wheelUp()
{
    if(--m_currIndex < 0)
    {
        m_currIndex = 0;
    }
    update();
    emit sig_setCurrentIndex(m_currIndex);
    makeupJobs();
}

void PYFlashListPrivate::wheelDown()
{
    if(++m_currIndex + m_VisibleItemCnt > m_IIVec.count())
    {
        m_currIndex = m_IIVec.count() - m_VisibleItemCnt;
    }
    update();
    emit sig_setCurrentIndex(m_currIndex);
    makeupJobs();
}

void PYFlashListPrivate::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::HighQualityAntialiasing|QPainter::Antialiasing);
    drawBg(&painter);
    drawItems(&painter);
    drawHoverRect(&painter);
}

void PYFlashListPrivate::mouseMoveEvent(QMouseEvent *e)
{
    if(!m_bAllJobsDone)
    {
        return ;
    }

    int ItemCnt = e->pos().y()/ITEM_HEIGHT;
    if(m_currIndex + ItemCnt < m_IIVec.count())
    {
        QPointF topLeft(0,ItemCnt*ITEM_HEIGHT);
        QPointF bottomRight(width(),(ItemCnt+1)*ITEM_HEIGHT);
        m_HoverRect = QRectF(topLeft,bottomRight);
        m_strHoverText = m_IIVec.at(m_currIndex+ItemCnt).getText();
        update();
    }
}

void PYFlashListPrivate::mousePressEvent(QMouseEvent *e)
{
    if(!m_bAllJobsDone)
    {
        return ;
    }
    int ItemCnt = e->pos().y()/ITEM_HEIGHT;
    if(m_currIndex + ItemCnt < m_IIVec.count())
    {
        m_selectedIndex = m_currIndex + ItemCnt;
        QString strText = m_IIVec.at(m_selectedIndex).getText();
        emit sig_itemClicked(strText);
    }
    update();
}

void PYFlashListPrivate::resizeEvent(QResizeEvent *)
{

    calcGeo();
    makeupJobs();
}

void PYFlashListPrivate::leaveEvent(QEvent *)
{
    m_HoverRect = QRectF();
    update();
}
void PYFlashListPrivate::showEvent(QShowEvent *)
{
    calcGeo();
}

void PYFlashListPrivate::wheelEvent(QWheelEvent *e)
{
    if(e->delta() > 0)
    {
        wheelUp();
    }else{
        wheelDown();
    }
}

void PYFlashListPrivate::drawBg(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    QLinearGradient BgGradient(QPoint(0,0),QPoint(0,height()));
    BgGradient.setColorAt(0.0,BG_START_COLOR);
    BgGradient.setColorAt(1.0,BG_END_COLOR);
    painter->setBrush(BgGradient);
    painter->drawRect(rect());
    painter->restore();
}

void PYFlashListPrivate::drawItems(QPainter *painter)
{
    if(m_IIVec.count() == 0)
    {
        return ;
    }

    painter->save();

    int Guard = 0;
    qreal initY = 0;
    for(int index = m_currIndex;index < m_IIVec.count();index++)
    {
        if(Guard++ > m_VisibleItemCnt)
        {
            break ;
        }

        QPointF topLeft(0,initY);
        QPointF bottomRight(width(),initY + ITEM_HEIGHT);
        QRectF ItemRect(topLeft,bottomRight);

        painter->save();
        QTransform t;
        t.translate(ItemRect.center().x(),ItemRect.center().y());

        t.scale(m_IIVec.at(index).getZoomingFactor(),m_IIVec.at(index).getZoomingFactor());
        painter->setTransform(t);

        QPointF TedTopLeft(-width()/2,-ITEM_HEIGHT/2);
        QPointF TedBottomRight(width()/2,ITEM_HEIGHT/2);
        QRectF TedRect(TedTopLeft,TedBottomRight);

        QLinearGradient ItemGradient(TedRect.topLeft(),TedRect.bottomLeft());
        if(index%2)
        {
            ItemGradient.setColorAt(0.0,ITEM_START_COLOR);
            ItemGradient.setColorAt(1.0,ITEM_END_COLOR);
        }else{
            ItemGradient.setColorAt(0.0,ITEM_START_COLOR_A);
            ItemGradient.setColorAt(1.0,ITEM_END_COLOR_A);
        }
        painter->setPen(Qt::NoPen);
        painter->setBrush(ItemGradient);
        painter->drawRect(TedRect);

        painter->setPen(NORMAL_TEXT_COLOR);
        painter->drawText(TedRect,m_IIVec.at(index).getText(),Qt::AlignVCenter|Qt::AlignHCenter);
        painter->restore();
        /// increment initY
        initY += ITEM_HEIGHT;
    }
    painter->restore();
}

void PYFlashListPrivate::drawHoverRect(QPainter *painter)
{
    if(m_HoverRect.isEmpty() && !m_bAllJobsDone)
    {
        return ;
    }

    painter->save();
    painter->setPen(Qt::NoPen);
    QLinearGradient HoverGradient(m_HoverRect.topLeft(),m_HoverRect.bottomLeft());
    HoverGradient.setColorAt(0.0,HOVER_START_COLOR);
    HoverGradient.setColorAt(1.0,HOVER_END_COLOR);
    painter->setBrush(HoverGradient);
    painter->drawRoundedRect(m_HoverRect,RECT_RADIUS,RECT_RADIUS);

    QFont BoldFont;
    BoldFont.setBold(true);
    painter->setFont(BoldFont);

    painter->setPen(HOVER_TEXT_COLOR);
    painter->drawText(m_HoverRect,m_strHoverText,Qt::AlignVCenter|Qt::AlignHCenter);
    painter->restore();
}

void PYFlashListPrivate::DoRotation()
{
    int Guard = 0;
    bool bHasJobUndone = false;
    m_bAllJobsDone = false;
    m_HoverRect = QRectF();

    for(int index = m_currIndex;index < m_IIVec.count()/* && Guard < m_ItemCounter*/ ;index++ )
    {
        if(!m_IIVec.at(index).jobDone())
        {
            bHasJobUndone = true;
            m_IIVec[index].updateZoomingFactor();
        }

        if(Guard++ > m_VisibleItemCnt)
        {
            break;
        }
        update();
    }

    if(!bHasJobUndone)
    {
        m_RotateTimer->stop();
        m_bAllJobsDone = true;
    }

}

void PYFlashListPrivate::UpdateItemCount()
{
    if(++m_ItemCounter > m_VisibleItemCnt)
    {
        if(m_ItemCountTimer->isActive())
        {
            m_ItemCountTimer->stop();
            m_ItemCounter = 0;
        }
    }
}

void PYFlashListPrivate::addItem(const QString &str)
{
    ItemInfo ID(str);
    m_IIVec.push_back(ID);

    if(m_RotateTimer->isActive())
    {
        m_RotateTimer->stop();
    }
    m_RotateTimer->start();

}

void PYFlashListPrivate::clear()
{

}

void PYFlashListPrivate::render()
{
    update();
}

void PYFlashListPrivate::setCurrentIndex(int curIndex)
{
    if(curIndex == m_currIndex)
    {
        return ;
    }

    m_currIndex = curIndex;

    m_VisibleItemCnt = height()/ITEM_HEIGHT + 1;
    int Guard = 0;
    for(int index = m_currIndex ;index < m_IIVec.count();index++)
    {
        m_IIVec[index].resetZoomingFactor();
        if(Guard++ > m_VisibleItemCnt)
        {
            break ;
        }
    }
    m_RotateTimer->start();
    m_ItemCountTimer->start();
}
