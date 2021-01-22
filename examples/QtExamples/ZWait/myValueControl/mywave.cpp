#include "mywave.h"

myWave::myWave(QWidget *parent) :
    QWidget(parent)
{
    this->initVariables();
}

void myWave::initVariables()
{
    m_nChannelCount = 0;

    m_xIncrement = 0;

    m_updateTimer=new QTimer(this);
    m_updateTimer->setInterval(PYW_UPDATE_INTERVAL);
    connect(m_updateTimer,SIGNAL(timeout()),this,SLOT(UpdateData()));
}

void myWave::resizeEvent(QResizeEvent *)
{
    m_xIncrement = (qreal)width()/m_nChannelCount;
}

void myWave::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    drawBg(&painter);
    drawWave(&painter);
}


void myWave::drawBg(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);

    QLinearGradient BgGradient(QPoint(0,0),QPoint(0,height()));
    BgGradient.setColorAt(0.0,PYW_BG_END_COLOR);
//    BgGradient.setColorAt(0.5,PYW_BG_END_COLOR);
    BgGradient.setColorAt(1.0,PYW_BG_END_COLOR);
    painter->setBrush(BgGradient);
    painter->drawRect(rect());

    painter->restore();
}

void myWave::drawWave(QPainter *painter)
{
    painter->save();

    if(ANTIALIASING_ON)
    {
        painter->setRenderHints(QPainter::Antialiasing|QPainter::HighQualityAntialiasing);
    }

    QVector<QPointF> PotVec;

    qreal startX = 0; // DEBUG_VAR(ChannelIndex);
    for(int DataIndex =  0  ; DataIndex < m_CurrDataVec.count() - 1; ++DataIndex)
    {
        // DEBUG_VAR(DataIndex);
        qreal CurrValue=m_CurrDataVec.at(DataIndex);
        qreal dY1=(qreal)height()/PYW_RANGE*CurrValue;
        qreal y1=height()-dY1;
        qreal NextValue=m_CurrDataVec.at(DataIndex+1);
        qreal dY2=(qreal)height()/PYW_RANGE*NextValue;
        qreal y2=height()-dY2;
        QPointF dataPot1(startX,y1);
        QPointF dataPot2(startX+m_xIncrement,y2);
        startX += m_xIncrement;
        PotVec.push_back(dataPot1);
        PotVec.push_back(dataPot2);
    }

    painter->setPen(QPen(PYW_CURVE_COLOR,PYW_PEN_WIDTH));
    painter->drawLines(PotVec);
    painter->restore();
}

void myWave::UpdateData()
{
    for(int DataIndex = 0 ;DataIndex < m_nChannelCount ; DataIndex++)
    {
        qApp->processEvents();

        if(m_CurrDataVec.at(DataIndex) < m_DataVec.at(DataIndex))
        {
            m_CurrDataVec[DataIndex] += PYW_VALUE_INCREMENT;
        }else if(m_CurrDataVec.at(DataIndex) > m_DataVec.at(DataIndex)){
            m_CurrDataVec[DataIndex] -= PYW_VALUE_INCREMENT;
        }else{
            continue ;
        }
    }

    update();
}

void myWave::setChannelCount(int cnt)
{
    m_nChannelCount = cnt;
    m_CurrDataVec.resize(cnt);
    m_DataVec.resize(cnt);

    m_xIncrement = (qreal)width()/m_nChannelCount;
}

void myWave::setChannelData(const QVector<int> DataVec)
{
    int DataCnt = DataVec.count();
    for(int DataIndex = 0;DataIndex < DataCnt ; DataIndex++)
    {
        m_DataVec[DataIndex] = DataVec.at(DataIndex);
    }

    if(!m_updateTimer->isActive())
    {
        m_updateTimer->start();
    }
}
