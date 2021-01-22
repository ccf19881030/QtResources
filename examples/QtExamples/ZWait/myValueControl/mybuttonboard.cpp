#include "mybuttonboard.h"

PYButtonBoardPrivate::PYButtonBoardPrivate(QWidget *parent) :
    QWidget(parent),m_MaxButtonLength(0),m_ButtonWidth(0)
{
    setMouseTracking(true);
}

PYButtonBoardPrivate::~PYButtonBoardPrivate()
{

}

void PYButtonBoardPrivate::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing|QPainter::HighQualityAntialiasing);
    drawBg(&painter);
    drawButtons(&painter);
    drawHoverAndSelectButton(&painter);
}

void PYButtonBoardPrivate::mouseMoveEvent(QMouseEvent *e)
{
    int BtnCnt = m_ButtonList.count();
    for(int BtnIndex = 0;BtnIndex < BtnCnt ; BtnIndex++)
    {
        if(m_RectTextPairVec.at(BtnIndex).first.contains(e->pos()))
        {
            m_HoverRect = m_RectTextPairVec.at(BtnIndex).first;
            m_strHoverText = m_RectTextPairVec.at(BtnIndex).second;
            update();
            return ;
        }
    }
}

void PYButtonBoardPrivate::mousePressEvent(QMouseEvent *e)
{
    int BtnCnt = m_ButtonList.count();
    for(int BtnIndex = 0;BtnIndex < BtnCnt ; BtnIndex++)
    {
        if(m_RectTextPairVec.at(BtnIndex).first.contains(e->pos()))
        {
            m_SelectRect = m_RectTextPairVec.at(BtnIndex).first;
            m_strSelectText = m_RectTextPairVec.at(BtnIndex).second;
            update();
            emit sig_ButtonClicked(m_strSelectText);
            return ;
        }
    }

}
void PYButtonBoardPrivate::leaveEvent(QEvent *)
{
    m_HoverRect = QRectF();
    m_strHoverText.clear();
    update();
}

void PYButtonBoardPrivate::drawBg(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    QLinearGradient BgGradient(QPoint(0,0),QPoint(0,height()));
    BgGradient.setColorAt(0.0,PYBB_BG_START_COLOR);
    BgGradient.setColorAt(1.0,PYBB_BG_END_COLOR);
    painter->setBrush(BgGradient);
    painter->drawRect(rect());
    painter->restore();
}

void PYButtonBoardPrivate::drawButtons(QPainter *painter)
{
    m_RectTextPairVec.clear();

    painter->save();

    int BtnCnt = m_ButtonList.count();
    qreal ButtonWidth = m_MaxButtonLength + 2 * PYBB_EXTRA_SPACE;

    int hBoxCnt = (width() - PYBB_SPACE)/(ButtonWidth + PYBB_SPACE);

    qreal ExtraSpace = width() - hBoxCnt * ButtonWidth - (hBoxCnt + 1)*PYBB_SPACE;
    qreal SingleExtraSpace = (qreal)ExtraSpace/hBoxCnt;
    m_ButtonWidth = ButtonWidth + SingleExtraSpace;

    if(m_ButtonWidth < (m_MaxButtonLength + 2 * PYBB_EXTRA_SPACE))
    {
      m_ButtonWidth = m_MaxButtonLength  + 2 * PYBB_EXTRA_SPACE;
    }

    qreal initX = PYBB_SPACE;
    qreal initY = PYBB_SPACE;

    for(int FIndex = 1 ;FIndex <= BtnCnt ; FIndex++)
    {

      QPointF ButtonTopLeft(initX,initY);
      QPointF ButtonBottomRight(initX + m_ButtonWidth,initY + PYBB_BUTTON_HEIGHT);
      QRectF ButtonRect(ButtonTopLeft,ButtonBottomRight);

      m_RectTextPairVec.push_back(qMakePair(ButtonRect,m_ButtonList.at(FIndex-1)));


      painter->setPen(Qt::NoPen);
      QLinearGradient BoxGradient(ButtonRect.topLeft(),ButtonRect.bottomLeft());
      BoxGradient.setColorAt(0.0,PYBB_BUTTON_START_COLOR);
      BoxGradient.setColorAt(1.0,PYBB_BUTTON_END_COLOR);
      painter->setBrush(BoxGradient);

      painter->drawRoundedRect(ButtonRect,PYBB_BUTTON_RECT_RADIUS,PYBB_BUTTON_RECT_RADIUS);


      // increment initX

      if(FIndex % hBoxCnt == 0 )
      {
        // reset initX
        initX = PYBB_SPACE;

        // increment initY
        initY += PYBB_BUTTON_HEIGHT + PYBB_SPACE ;
      }else{

        // increment initX
        initX += m_ButtonWidth + PYBB_SPACE;
      }

      painter->setPen(PYBB_NORMAL_TEXT_COLOR);
      painter->drawText(ButtonRect,tr("%1").arg(m_ButtonList.at(FIndex-1)),PYBB_BUTTON_TEXT_ALIGNMENT);

    }

    setMinimumHeight(initY  + PYBB_SPACE + PYBB_BUTTON_HEIGHT );
    painter->restore();

}

void PYButtonBoardPrivate::drawHoverAndSelectButton(QPainter *painter)
{

    // draw hover button and text
    if(!m_HoverRect.isEmpty())
    {
        painter->save();
        painter->setPen(Qt::NoPen);
        QLinearGradient HoverGradient(m_HoverRect.topLeft(),m_HoverRect.bottomLeft());
        HoverGradient.setColorAt(0.0,PYBB_SELECT_BUTTON_START_COLOR);
        HoverGradient.setColorAt(1.0,PYBB_SELECT_BUTTON_END_COLOR);
        painter->setBrush(HoverGradient);
        painter->setOpacity(PYBB_BUTTON_HOVER_OPACITY);
        painter->drawRoundedRect(m_HoverRect,PYBB_BUTTON_RECT_RADIUS,PYBB_BUTTON_RECT_RADIUS);

        painter->setOpacity(1.0);
        painter->setPen(PYBB_HOVER_TEXT_COLOR);
        painter->drawText(m_HoverRect,tr("%1").arg(m_strHoverText),PYBB_BUTTON_TEXT_ALIGNMENT);
        painter->restore();

    }

    // draw select button and text

    if(!m_strSelectText.isEmpty())
    {
        int BtnCnt = m_RectTextPairVec.count();
        for(int BtnIndex = 0;BtnIndex < BtnCnt ; BtnIndex++)
        {
            if(m_RectTextPairVec.at(BtnIndex).second == m_strSelectText)
            {
                m_SelectRect = m_RectTextPairVec.at(BtnIndex).first;
                break;
            }
        }
        //
        painter->save();
        painter->setPen(Qt::NoPen);
        QFont BoldFont;
        BoldFont.setBold(true);
        painter->setFont(BoldFont);

        QLinearGradient SelectGradient(m_SelectRect.topLeft(),m_SelectRect.bottomLeft());
        SelectGradient.setColorAt(0.0,PYBB_SELECT_BUTTON_START_COLOR);
        SelectGradient.setColorAt(1.0,PYBB_SELECT_BUTTON_END_COLOR);
        painter->setBrush(SelectGradient);
        painter->drawRoundedRect(m_SelectRect,PYBB_BUTTON_RECT_RADIUS,PYBB_BUTTON_RECT_RADIUS);

        painter->setPen(PYBB_SELECT_TEXT_COLOR);
        painter->drawText(m_SelectRect,tr("%1").arg(m_strSelectText),PYBB_BUTTON_TEXT_ALIGNMENT);
        painter->restore();
    }
}

void PYButtonBoardPrivate::addButton(const QString &str)
{
    qreal ButtonLength = fontMetrics().width(str);

    if(m_MaxButtonLength < ButtonLength)
    {
        m_MaxButtonLength = ButtonLength;
    }

    m_ButtonList.push_back(str);
    update();
}

void PYButtonBoardPrivate::setButtons(const QStringList &strList)
{
    m_ButtonList = strList;
    foreach(const QString& str,strList)
    {
        qreal ButtonLength = fontMetrics().width(str);
        if(m_MaxButtonLength < ButtonLength)
        {
            m_MaxButtonLength = ButtonLength;
        }
    }

    update();
}

myButtonBoard::myButtonBoard(QWidget *parent):QWidget(parent)
{
    createWidgets();
    initSettings();
    initMessages();
}

void myButtonBoard::createWidgets()
{
    d = new PYButtonBoardPrivate(this);
    dContainer = new QScrollArea(this);
    dContainer->setWidget(d);
    mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(dContainer);
    setLayout(mainLayout);

}

void myButtonBoard::initSettings()
{
    dContainer->setWidgetResizable(true);
    dContainer->setContentsMargins(0,0,0,0);
    dContainer->setFrameShape(QFrame::NoFrame);

}

void myButtonBoard::initMessages()
{
    connect(d,SIGNAL(sig_ButtonClicked(QString)),this,SIGNAL(sig_ButtonClicked(QString)));
}

void myButtonBoard::addButton(const QString &str)
{
    d->addButton(str);
}

void myButtonBoard::setButtons(const QStringList &strList)
{
    d->setButtons(strList);
}
