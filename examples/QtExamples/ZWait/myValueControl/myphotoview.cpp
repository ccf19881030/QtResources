#include "myphotoview.h"

PYNum::PYNum(QWidget* parent):QWidget(parent)
{
    m_opacity = 0.0;

    setWindowOpacity(PYN_FIN_OPACITY);

    m_fadeTimer = new QTimer(this);
    m_fadeTimer->setInterval(PYN_TIMER_INTERVAL);
    connect(m_fadeTimer,SIGNAL(timeout()),this,SLOT(DoFading()));

    m_hideTimer = new QTimer(this);
    m_hideTimer->setInterval(PYN_TIMER_INTERVAL);
    connect(m_hideTimer,SIGNAL(timeout()),this,SLOT(DoHiding()));

    m_holdTimer = new QTimer(this);
    m_holdTimer->setInterval(PYN_HOLD_DURATION);
    m_holdTimer->setSingleShot(true);
    connect(m_holdTimer,SIGNAL(timeout()),m_hideTimer,SLOT(start()));

    m_nTotal = 0;
    m_nValue = 0;

    setFixedHeight(PYN_MAX_HEIGHT);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
}

void PYNum::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing|QPainter::HighQualityAntialiasing);
    drawBg(&painter);
    drawText(&painter);
}

void PYNum::drawBg(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);

    QLinearGradient BgGradient(QPoint(0,0),QPoint(0,height()));
    BgGradient.setColorAt(0.0,PYN_BG_START_COLOR);
    BgGradient.setColorAt(1.0,PYN_BG_END_COLOR);

    painter->setBrush(BgGradient);
    painter->drawRoundedRect(rect(),PYN_RECT_RADIUS,PYN_RECT_RADIUS);
    painter->restore();
}

void PYNum::drawText(QPainter *painter)
{
    painter->save();
    QString strText ;
    strText = tr("%1/%2").arg(m_nValue).arg(m_nTotal);
    qreal TextLength = fontMetrics().width(strText);
    qreal ThisWidth = TextLength * PYN_WIDTH_FACTOR;

    painter->setPen(PYN_TEXT_COLOR);
    QFont TextFont;
    TextFont.setBold(true);
    painter->setFont(TextFont);
    painter->drawText(rect(),strText,Qt::AlignVCenter|Qt::AlignHCenter);
    setFixedWidth(ThisWidth);

    painter->restore();
}

void PYNum::showEvent(QShowEvent *)
{
    m_opacity = 0.0;
    setWindowOpacity(m_opacity);
    m_fadeTimer->start();
}

void PYNum::DoFading()
{
    m_opacity += PYN_OPACITY_INCREMENT;

    if(m_opacity > PYN_FIN_OPACITY)
    {
        m_opacity = PYN_FIN_OPACITY;
        m_fadeTimer->stop();
        m_holdTimer->start();
    }
    setWindowOpacity(m_opacity);
}

void PYNum::DoHiding()
{
    m_opacity -= PYN_OPACITY_INCREMENT;

    if(m_opacity < 0.0)
    {
        m_opacity = 0.0;
        m_hideTimer->stop();
    }

    setWindowOpacity(m_opacity);
}

void PYNum::setTotal(int totalNum)
{
    m_nTotal = totalNum;
    update();
}

void PYNum::setValue(int value)
{
    m_nValue = value;
    update();

}

myPhotoView::myPhotoView(QWidget *parent) :
    QWidget(parent)
{
    this->initVariables();
}

void myPhotoView::initVariables()
{
    m_currImage = 0;
    m_nTotal = 0;
    m_nCurrIndex = 0;

    num = new PYNum(this);
    connect(this,SIGNAL(sig_setTotal(int)),num,SLOT(setTotal(int)));
    connect(this,SIGNAL(sig_setValue(int)),num,SLOT(setValue(int)));

    prevButton = new QToolButton(this);
    nextButton = new QToolButton(this);

    prevButton->setIcon(QIcon(":/images/prev.png"));
    nextButton->setIcon(QIcon(":/images/next.png"));

    prevButton->setIconSize(PYP_BUTTON_SIZE);
    nextButton->setIconSize(PYP_BUTTON_SIZE);

    prevButton->setFixedSize(PYP_BUTTON_SIZE);
    nextButton->setFixedSize(PYP_BUTTON_SIZE);

    prevButton->setAutoRaise(true);
    nextButton->setAutoRaise(true);

    connect(prevButton,SIGNAL(clicked()),this,SLOT(showPrevious()));
    connect(nextButton,SIGNAL(clicked()),this,SLOT(showNext()));

    calcGeo();

#ifdef PYP_IMAGE_FADE_TIMER_INTERVAL
    m_imageOpacity = 0.0;
    m_imageFadeTimer = new QTimer(this);
    m_imageFadeTimer->setInterval(PYP_IMAGE_FADE_TIMER_INTERVAL);
    connect(m_imageFadeTimer,SIGNAL(timeout()),this,SLOT(DoImageFading()));

#endif
}

void myPhotoView::calcGeo()
{
    /// RESIZE AND MOVE PREVBUTTON
    QPoint PrevMovePot(PYP_LEFT_SPACE,height() - PYP_TOP_SPACE - PYP_BUTTON_SIZE.height());
    prevButton->move(PrevMovePot);
    prevButton->show();


    /// RESIZE AND MOVE NEXTBUTTON
    QPoint NextMovePot(width() - PYP_LEFT_SPACE - PYP_BUTTON_SIZE.width(),height() - PYP_TOP_SPACE -PYP_BUTTON_SIZE.height());
    nextButton->move(NextMovePot);
    nextButton->show();

    /// RESIZE AND MOVE NUM
    qreal NumX = (qreal)width()/2 - (qreal)num->width()/2;
    qreal NumY = height() - PYP_TOP_SPACE - PYP_BUTTON_SIZE.height()/2 - num->height()/2;
    QPointF NumMovePot(NumX,NumY);
    num->move(NumMovePot.toPoint());
}

void myPhotoView::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing|QPainter::HighQualityAntialiasing|QPainter::SmoothPixmapTransform);
    drawBg(&painter);
    drawImage(&painter);
}

void myPhotoView::showEvent(QShowEvent *)
{
    calcGeo();
}

void myPhotoView::resizeEvent(QResizeEvent *)
{
    calcGeo();
}

void myPhotoView::drawBg(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);

    QLinearGradient BgGradient(QPoint(0,0),QPoint(0,height()));
    BgGradient.setColorAt(0.0,PYP_BG_START_COLOR);
    BgGradient.setColorAt(1.0,PYP_BG_END_COLOR);
    painter->setBrush(BgGradient);

    painter->drawRect(rect());

    painter->restore();
}

void myPhotoView::drawImage(QPainter *painter)
{
    painter->save();

#ifdef PYP_IMAGE_MOTION_PATTERN_FADE

    painter->setOpacity(m_imageOpacity);
    qreal imageWidth = m_currImage->width();
    qreal imageHeight = m_currImage->height();
    qreal ImageX = rect().center().x() - imageWidth/2;
    qreal ImageY = rect().center().y() - imageHeight/2;
    QPointF ImagePot(ImageX,ImageY);
    painter->drawImage(ImagePot,*m_currImage);
#endif



    painter->restore();
}



#ifdef PYP_IMAGE_FADE_TIMER_INTERVAL
void myPhotoView::DoImageFading()
{
    m_imageOpacity += PYP_IMAGE_OPACITY_INCREMENT;

    if(m_imageOpacity > 1.0)
    {
        m_imageOpacity = 1.0;
        m_imageFadeTimer->stop();
    }
    update();
}

#endif


void myPhotoView::load(const QString &strFolder)
{
    m_strFolder = strFolder;

    QDir imageFolder(strFolder);

    if (imageFolder.exists())
    {
        QStringList ImageList = imageFolder.entryList(PYP_IMAGE_SUFFIX);
        if (ImageList.count()>0)
        {
            QString strFullPath ;
            m_ImageVec.clear();
            foreach(const QString strImage,ImageList)
            {
                strFullPath = tr("%1/%2").arg(strFolder).arg(strImage);
                QImage* img = new QImage(strFullPath);
                m_ImageVec.push_back(img);
            }

            if(m_ImageVec.size() > 0)
            {
                m_currImage = m_ImageVec.at(0);
                m_nCurrIndex = 0;
            }

            emit sig_setTotal(ImageList.count());
        #ifdef PYP_IMAGE_MOTION_PATTERN_FADE
            m_imageFadeTimer->start();
        #endif
        }
    }
}

void myPhotoView::showNext()
{
    if(m_ImageVec.isEmpty())
    {
        return ;
    }
    m_nCurrIndex++;

    if(m_nCurrIndex >= m_ImageVec.count())
    {
        m_nCurrIndex = m_ImageVec.count() -1;
    }
    m_currImage = m_ImageVec.at(m_nCurrIndex);

#ifdef PYP_IMAGE_MOTION_PATTERN_FADE
    m_imageOpacity = 0.0;
    m_imageFadeTimer->start();
#endif
    emit sig_setValue(m_nCurrIndex + 1);
    calcGeo();
}

void myPhotoView::showPrevious()
{
    if(m_ImageVec.isEmpty())
    {
        return ;
    }

    m_nCurrIndex--;

    if(m_nCurrIndex < 0)
    {
        m_nCurrIndex = 0;
    }
    m_currImage = m_ImageVec.at(m_nCurrIndex);
#ifdef PYP_IMAGE_MOTION_PATTERN_FADE
    m_imageOpacity = 0.0;
    m_imageFadeTimer->start();
#endif

    emit sig_setValue(m_nCurrIndex + 1);
    calcGeo();
}
