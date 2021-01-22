#include "mygauge3.h"

myGauge3::myGauge3(QWidget *parent) :
    QWidget(parent)
{
    this->initVariables();
    this->initSettings();
}

void myGauge3::initVariables()
{
    this->myTopColor=Qt::red;
    m_nMin=0;
    m_nMax=100;
    m_length=m_nMax-m_nMin;
    m_value=0;
    m_currentValue=0;
    tipTimer=new QTimer(this);
    tipTimer->setInterval(10);
    tipTimer->setSingleShot(true);

    eraseTimer=new QTimer(this);
    eraseTimer->setInterval(1500);
    eraseTimer->setSingleShot(true);

    connect(tipTimer,SIGNAL(timeout()),this,SLOT(ShowTip()));
    connect(eraseTimer,SIGNAL(timeout()),this,SLOT(HideTip()));

    m_longHand=height()/3;
    m_okHand=height()/4;
    m_shortHand=height()/5;
    m_handleWidth=width()/15;
    m_handleHeight=height()/5;
    m_indicatorLength=height()/5;

    m_bDrag=false;
}

void myGauge3::initSettings()
{
    QPointF startPot(LEFT_SPACE1,m_longHand/2);
    m_indicatorLastPot=startPot;
}

void myGauge3::mousePressEvent(QMouseEvent *e)
{
    if(e->button() & Qt::LeftButton)
    {
        if(m_handleRect.contains(e->pos()))
        {
            m_bDrag=true;
            update();
        }
    }
}

void myGauge3::mouseReleaseEvent(QMouseEvent *e)
{
    m_bDrag=false;
    update();
}

void myGauge3::mouseMoveEvent(QMouseEvent *e)
{
    if(m_bDrag)
    {
        m_lastPos=e->pos();

        if(m_lastPos.x()>=m_lineLeftPot.x()&&m_lastPos.x()<=m_lineRightPot.x())
        {
            QPointF indicatorTopPot(m_lastPos.x(),m_indicatorTopPot.y());
            m_indicatorLastPot=indicatorTopPot;

            qreal totalLineWidth=m_lineRightPot.x()-m_lineLeftPot.x();
            qreal dx=e->pos().x()-m_lineLeftPot.x();
            qreal ratio=(qreal)  dx/totalLineWidth;
            m_currentValue=m_length*ratio+m_nMin;
            emit valueChanged(m_currentValue);
            tipTimer->start();
            update();
        }
    }
}

void myGauge3::resizeEvent(QResizeEvent *e)
{
    setValue(m_currentValue);
    e->accept();
}

void myGauge3::paintEvent(QPaintEvent *)
{
    QPainter painter;
    painter.begin(this);
    painter.setRenderHints(QPainter::Antialiasing|QPainter::TextAntialiasing);

    resetVariables(&painter);
    drawBackground(&painter);
    drawRule(&painter);
    drawHandle(&painter);
    drawTip(&painter);
    painter.end();
}

void myGauge3::drawBackground(QPainter *painter)
{
    painter->save();

    QLinearGradient bgGradient(QPointF(0,0),QPointF(0,height()));
    bgGradient.setColorAt(0.0,QColor(210,210,210));
    bgGradient.setColorAt(0.1,QColor(50,50,50));
    bgGradient.setColorAt(0.9,QColor(50,50,50));
    bgGradient.setColorAt(1.0,QColor(210,210,210));

    painter->setBrush(bgGradient);
    painter->setPen(Qt::NoPen);
    painter->drawRect(rect());
    painter->restore();
}

void myGauge3::drawRule(QPainter *painter)
{
    painter->save();
    drawHorizontalLine(painter);
    drawVerticalLines(painter);
    painter->restore();
}

void myGauge3::drawHorizontalLine(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::white);

    QPointF leftPot(LEFT_SPACE1,TOP_SPACE1+m_longHand);
    m_lineLeftPot=leftPot;

    QPointF rightPot(width()-LEFT_SPACE1,TOP_SPACE1+m_longHand);
    m_lineRightPot=rightPot;
    painter->drawLine(leftPot,rightPot);
    painter->restore();
}

void myGauge3::drawVerticalLines(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::white);

    int length=m_nMax-m_nMin;
    qreal startX=LEFT_SPACE1;
    qreal bottomY=m_lineLeftPot.y();
    qreal lineLenght=m_lineRightPot.x()-m_lineLeftPot.x();

    qreal increment=lineLenght/length;
    int startValue=m_nMin;
    QString strValue;
    for(int i=m_nMin;i<=m_nMax;i++)
    {
        if(i%10==0)
        {
            QPointF topPot(startX,bottomY-m_longHand);
            QPointF bottomPot(startX,bottomY);
            painter->drawLine(topPot,bottomPot);
            strValue=tr("%1").arg(startValue);
            qreal textWidth=fontMetrics().width(strValue);
            qreal textHeight=fontMetrics().height();
            QPointF textPot(startX-textWidth/2,bottomY+textHeight);
            painter->drawText(textPot,strValue);

            startValue+=10;
        }
        else if(i%5==0)
        {
            QPointF topPot(startX,bottomY-m_okHand);
            QPointF bottomPot(startX,bottomY);
            painter->drawLine(topPot,bottomPot);
        }
        else
        {
            QPointF topPot(startX,bottomY-m_shortHand);
            QPointF bottomPot(startX,bottomY);
            painter->drawLine(topPot,bottomPot);
        }

        startX+=increment;
    }
    painter->restore();
}

void myGauge3::drawTip(QPainter *painter)
{
    if(!m_bShowTip)
    {
        return ;
    }
    painter->save();
    QLinearGradient tipRectGradient(m_tipRect.topLeft(),m_tipRect.bottomLeft());
    tipRectGradient.setColorAt(0.0,QColor(200,200,200));
    tipRectGradient.setColorAt(1.0,QColor(170,170,170));
    painter->setBrush(tipRectGradient);
    painter->drawRect(m_tipRect);
    painter->drawText(m_tipRect,Qt::AlignCenter,tr("%1").arg(m_currentValue));

    painter->restore();
}

void myGauge3::SetmyTopColor(QColor c)
{
    this->myTopColor=c;
}

void myGauge3::drawHandle(QPainter *painter)
{
    painter->save();

    m_indicatorTopPot=QPointF(m_indicatorLastPot.x(),m_lineLeftPot.y()-m_longHand/4);
    QPointF indicatorLeftPot(m_indicatorTopPot.x()-width()/50,m_indicatorTopPot.y()+m_indicatorLength);
    m_indicatorBottomLeftPot=indicatorLeftPot;
    QPointF indicatorRightPot(m_indicatorTopPot.x()+width()/50,m_indicatorTopPot.y()+m_indicatorLength);
    m_indicatorBottomRightPot=indicatorRightPot;

    QLinearGradient indicatorGradient(indicatorLeftPot,indicatorRightPot);
    indicatorGradient.setColorAt(0.0,this->myTopColor);
    //indicatorGradient.setColorAt(0.0,QColor(180,50,50));
    //indicatorGradient.setColorAt(0.5,QColor(230,30,30));
    //indicatorGradient.setColorAt(1.0,QColor(180,50,50));
    painter->setBrush(indicatorGradient);

    QVector<QPointF> potVec;
    potVec.push_back(m_indicatorTopPot);
    potVec.push_back(indicatorLeftPot);
    potVec.push_back(indicatorRightPot);

    painter->drawPolygon(potVec);

    qreal indicatorLength=indicatorRightPot.x()-indicatorLeftPot.x();

    QPointF handleTopLeftPot(indicatorLeftPot.x()-(m_handleWidth/2-indicatorLength/2),indicatorLeftPot.y());
    QPointF handleBottomRightPot(indicatorLeftPot.x()+indicatorLength,indicatorLeftPot.y()+m_handleHeight);
    QRectF handleRect(indicatorLeftPot,handleBottomRightPot);

    QPointF tipRectTopLeftPot(handleRect.topRight().x()+10,handleRect.topRight().y());
    QString strValue;
    strValue=tr("%1").arg(m_currentValue);
    qreal textLength=fontMetrics().width(strValue);
    qreal textHeight=fontMetrics().height();
    QPointF tipRectBottomRightPot(tipRectTopLeftPot.x()+textLength+5,tipRectTopLeftPot.y()+textHeight+5);
    QRectF tipRect(tipRectTopLeftPot,tipRectBottomRightPot);
    m_tipRect=tipRect;

    m_handleRect=handleRect;
    QLinearGradient handleGradient(handleRect.topLeft(),handleRect.topRight());
    handleGradient.setColorAt(0.0,QColor(160,160,160));
    handleGradient.setColorAt(0.2,QColor(200,200,200));
    handleGradient.setColorAt(0.8,QColor(200,200,200));
    handleGradient.setColorAt(1.0,QColor(160,160,160));
    painter->setBrush(handleGradient);
    painter->drawRect(handleRect);
    painter->restore();
}

void myGauge3::resetVariables(QPainter *painter)
{
    m_longHand=height()/3;
    m_okHand=height()/4;
    m_shortHand=height()/5;
    m_handleWidth=width()/15;
    m_handleHeight=height()/5;
    m_indicatorLength=height()/5;
}


void myGauge3::setRange(int min, int max)
{
    if(min<max)
    {
        m_nMin=min;
        m_nMax=max;
        m_length=m_nMax-m_nMin;
        update();
    }
}

void myGauge3::setValue(qreal value)
{

    if(m_nMin<=value&&value<=m_nMax)
    {
        m_value=value;
        m_currentValue=value;
        qreal lineWidth=width()-2*LEFT_SPACE1;
        qreal ratio=(qreal)m_value/m_length;
        qreal x=lineWidth*ratio;
        qreal newX=x+LEFT_SPACE1;
        qreal y=TOP_SPACE1+m_longHand-10;
        QPointF indicatorPot(newX,y);
        m_indicatorLastPot=indicatorPot;
        update();
    }
}
void myGauge3::ShowTip()
{
    m_bShowTip=true;
    eraseTimer->start();
    update();
}

void myGauge3::HideTip()
{
    m_bShowTip=false;
    update();
}
