/****************************************************************
** ImageView
** 图片浏览界面
**
** ImageView.cpp
**
** Zhou Tao   2017-05-18T10:52:16
**
** QQ : 741301964
**
** 深圳市XX电子股份有限公司
**
****************************************************************/
#include "imageview.h"
#include <QPainter>
#include <QDebug>

ImageView::ImageView(QWidget *parent, int width, int height) :
    QWidget(parent),m_nWidth(width),m_nHeight(height)
{
    //图片加载
    for(int itemNum=0;itemNum<3;itemNum++)
    {
        QGraphicsScene *scene = new QGraphicsScene(0,0,1024,600);

        CustomGraphicsView *view = new CustomGraphicsView(scene,this,false);
        view->setGeometry(-1024+itemNum*1024,0,1024,600);
        view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        view->centerOn(0.0,0.0);//确保scene显示居中
        BlackPixmapItem *pItem = new BlackPixmapItem(185,120,false);

        scene->addItem(pItem);
        QPoint point = QPoint(0,0);
        pItem->setPos(view->mapToScene(point));

        m_pListItem.append(pItem);
        m_listWidget.append(view);
    }

    //底部控件
    m_BottomWidget = new QWidget(this);
    m_BottomWidget->setGeometry(0,515,1024,85);
    m_BottomWidget->installEventFilter(this);
    m_BottomWidget->close();

    //自动播放按键
    m_autoplaybutton = new QPushButton(m_BottomWidget);
    m_autoplaybutton->setText("播放");
    m_autoplaybutton->setObjectName("autoplay");
    m_autoplaybutton->setGeometry(73,0,157,85);

    //目录
    m_filelistbutton = new QPushButton(m_BottomWidget);
    m_filelistbutton->setText("目录");
    m_filelistbutton->setGeometry(793,0,157,85);

    //放大
    m_enlargementbutton = new QPushButton(m_BottomWidget);
    m_enlargementbutton->setText("放大");
    m_enlargementbutton->setObjectName("enlarge");
    m_enlargementbutton->setGeometry(73+157+23,0,157,85);

    //缩小
    m_shrinkbutton = new QPushButton(m_BottomWidget);
    m_shrinkbutton->setText("缩小");
    m_shrinkbutton->setObjectName("shrink");
    m_shrinkbutton->setGeometry(73+157+23+157+23,0,157,85);

    //预览
    m_previewbutton = new QPushButton(m_BottomWidget);
    m_previewbutton->setText("预览");
    m_previewbutton->setObjectName("preview");
    m_previewbutton->setGeometry(73+157+23+157+23+157+23,0,157,85);

    m_backbutton = new QPushButton(this);//返回
    m_backbutton->setText("返回");
    m_backbutton->setObjectName("back");
    m_backbutton->setGeometry(32+54+28,20,54,54);

    //按键信号与槽
    connect(m_autoplaybutton, SIGNAL(pressed()), this, SLOT(slot_buttonClick()));
    connect(m_enlargementbutton, SIGNAL(pressed()), this, SLOT(slot_buttonClick()));
    connect(m_shrinkbutton, SIGNAL(pressed()), this,SLOT(slot_buttonClick()));

    connect(m_backbutton, SIGNAL(pressed()), this, SLOT(slot_buttonClick()));
    connect(m_previewbutton, SIGNAL(pressed()), this, SLOT(slot_buttonClick()));

    //底部窗口动画
    m_pShowAnimation = new QPropertyAnimation(m_BottomWidget, "pos");
    m_pCloseAnimation = new QPropertyAnimation(m_BottomWidget, "pos");
    connect(m_pCloseAnimation,SIGNAL(finished()),m_BottomWidget,SLOT(hide()));

    //定时器   定时10s关闭上下窗口
    timer = new QTimer();
    //设置定时器每个多少毫秒发送一个timeout()信号    10s
    timer->setInterval(10000);
    connect(timer, SIGNAL(timeout()), this, SLOT(slot_mouseClick()));

    //图片自动播放定时器
    autoplaytimer = new QTimer();
    autoplaytimer->setInterval(4000);//2s
    connect(autoplaytimer, SIGNAL(timeout()), this, SLOT(slot_autoplay()));

    m_nMoveTotalSize = 0;//总移动距离
    scaleFactor = 1.0;//缩放因子
    m_isMove = false;//是否移动鼠标
    m_nCurrentIndex = 0;//路径索引
}

ImageView::~ImageView()
{
    for(int i = 0;i<m_listWidget.size() ;i++)
    {
        delete m_listWidget.value(i);
    }
}

//设置可隐藏界面定时器是否开启 true开启  false关闭
void ImageView::setTimerstart(bool start)
{
    start?(timer->start()):(timer->stop());

    //处理自动图片播放定时器如果打开则关闭
    if(autoplaytimer->isActive())
        autoplaytimer->stop();
}

void ImageView::closeBottomWidget()
{
    m_pCloseAnimation->setDuration(400);
    m_pCloseAnimation->setStartValue(QPoint(0,515));
    m_pCloseAnimation->setEndValue(QPoint(0,600));
    m_pCloseAnimation->setEasingCurve(QEasingCurve::Linear);//缓和曲线
    m_pCloseAnimation->start();

    //如果定时器开启，则关闭
    if(timer->isActive())
    {
        timer->stop();
    }
}

void ImageView::showBottomWidget()
{
    m_BottomWidget->show();
    m_pShowAnimation->setDuration(400);
    m_pShowAnimation->setStartValue(QPoint(0,600));
    m_pShowAnimation->setEndValue(QPoint(0,515));
    m_pShowAnimation->setEasingCurve(QEasingCurve::Linear);//缓和曲线
    m_pShowAnimation->start();

    //如果定时器关闭，则开启
    if(!timer->isActive())
    {
        timer->start();
    }
}

void ImageView::slot_autoplay()
{
    if((m_nCurrentIndex+1) == m_listImagePath.size())
    {
        BlackPixmapItem *pItem  = getPixmapItem(m_listWidget.value(2));
        pItem->setVisible(true);
        readImageFile(m_listImagePath.value(0),2);//显示第一个
        emit sign_pageTurning(0,m_nCurrentIndex);//翻到第一页
    }
    else if(m_nCurrentIndex/12 != (m_nCurrentIndex+1)/12)
    {
        emit sign_pageTurning((m_nCurrentIndex+1)/12,m_nCurrentIndex);//预览翻页
    }
    //自动播放图片
    //第一个不移动
    for(int i = 1;i<m_listWidget.size() ;i++)
    {
        QPoint endPos = QPoint(m_listWidget.value(i)->x() - m_nWidth,0);
        m_listWidget.value(i)->moveWidgetAnimation(m_listWidget.value(i)->pos(),endPos,400);
    }

    //第一个item移到最后
    m_listWidget.first()->move(m_nWidth,0);
    CustomGraphicsView *m_pImageLoad = m_listWidget.takeFirst();

    //更新最后一个item
    m_nCurrentIndex++;

    m_listWidget.append(m_pImageLoad);
    if(m_nCurrentIndex == m_listImagePath.size())
        m_nCurrentIndex = 0;

    emit sign_getItemPixmap(m_nCurrentIndex+1,2);
}

//显示顶部底部控件
void ImageView::showWidget()
{
    showBottomWidget();           //显示底部窗口
    timer->start();//开启定时器
}

//关闭顶部底部控件
void ImageView::closeWidget(int duration)
{
    timer->stop();
    closeBottomWidget();
    closeViewAnimation(QRect(0,0,0,0),duration);
}

//鼠标按下
void ImageView::mousePressEvent(QMouseEvent *ev)
{
    if(autoplaytimer->isActive())
        autoplaytimer->stop();

    mousePress(ev->pos());
}

//鼠标松开
void ImageView::mouseReleaseEvent(QMouseEvent *ev)
{
    if(m_isMove)
        mouseRelease(ev->pos());
    else
        slot_mouseClick();

    m_isMove = false;//是否移动鼠标

    m_releaseTime = QTime::currentTime();//鼠标释放时间
}

void ImageView::mouseMoveEvent(QMouseEvent *ev)
{
    int releaseTime = m_releaseTime.msecsTo(QTime::currentTime());
    if(releaseTime < 200)   //两次按下时间小于300ms,不响应,防止不停滑动
    {
        m_isMove = true;//是否移动鼠标
        return;
    }

    mouseMove(ev->pos());
    m_isMove = true;//是否移动鼠标
}

//过滤掉底部窗口鼠标事件，防止按下的时候拖动
bool ImageView::eventFilter(QObject *watched, QEvent *event)
{
    ;
}

void ImageView::slot_mouseClick()
{
    if(m_BottomWidget->isHidden())
    {
        showBottomWidget();                     //显示底部窗口
    }else
    {
        closeBottomWidget();                     //关闭底部窗口
    }
}

//窗口显示动画
void ImageView::showViewAnimation(const QRect &startRect,int duration)
{
    //view移动到初始位置
    for(int i = 0;i<m_listWidget.size() ;i++)
    {
        m_listWidget.value(i)->move(QPoint(m_nWidth*i - m_nWidth,0));
    }
    scaleFactor = 1.0;//缩放因子
    show();
    m_listWidget.value(1)->setSize(185,120);
    QPropertyAnimation *m_pMoveAnimation = new QPropertyAnimation(m_listWidget.value(1), "geometry");//移动动画
    m_pMoveAnimation->setDuration(duration);
    m_pMoveAnimation->setStartValue(startRect);
    m_pMoveAnimation->setEndValue(QRect(0,0,1024,600));
    m_pMoveAnimation->setEasingCurve(QEasingCurve::InOutQuart);//缓和曲线
    m_pMoveAnimation->start(QAbstractAnimation::DeleteWhenStopped);
    connect(m_pMoveAnimation,SIGNAL(finished()),this,SLOT(slot_readImage()));
}

//窗口关闭动画
void ImageView::closeViewAnimation(const QRect &endRect, int duration)
{
    BlackPixmapItem *pItem  = getPixmapItem(m_listWidget.value(1));

    m_listWidget.value(1)->setSize(1024,600);
    QPropertyAnimation *m_pMoveAnimation = new QPropertyAnimation(m_listWidget.value(1), "geometry");//移动动画
    m_pMoveAnimation->setDuration(duration);
    m_pMoveAnimation->setStartValue(QRect(0,0,1024,600));

    int itemID = m_nCurrentIndex%12;
    QRect rect = QRect(40+itemID%4*(185+69),22+itemID/4*(120+13)+85,185,120);
    m_pMoveAnimation->setEndValue(rect);
    m_pMoveAnimation->setEasingCurve(QEasingCurve::OutQuad);//缓和曲线
    m_pMoveAnimation->start(QAbstractAnimation::DeleteWhenStopped);
    connect(m_pMoveAnimation,SIGNAL(finished()),this,SLOT(close()));
    connect(m_pMoveAnimation,SIGNAL(finished()),this,SLOT(slot_clearItemPixmap()));
    if(duration > 50)   //返回主菜单不显示预览标签
        connect(m_pMoveAnimation,SIGNAL(finished()),this,SIGNAL(sign_showPreviewLabel()));//显示预览底部和顶部界面)

    //图片回到起始位置
    pItem->setPos(m_listWidget.value(1)->mapToScene(QPoint(0,0)));
    pItem->setZoom(1.0);//图片缩小为原始大小

    m_releaseTime = QTime::currentTime();//鼠标释放时间
}

//直接显示窗口
void ImageView::showView()
{
    show();
    m_listWidget.value(1)->setGeometry(0,0,1024,600);
    slot_readImage();//初始化加载图片
}

//设置item预览图
void ImageView::setPreviewPixmap(QPixmap pixmap, int widgetID)
{
    BlackPixmapItem *pItem  = getPixmapItem(m_listWidget.value(widgetID));
    if(pixmap.isNull())
        pixmap.fill(Qt::green);
    pItem->setPixmap(pixmap);
    pItem->setInitPixmapSize(pixmap.size());
}

//初始化加载图片
void ImageView::slot_readImage()
{
    showWidget();
    //隐藏越界item
    if(m_nCurrentIndex-1 < 0)
    {
        BlackPixmapItem *pItem  = getPixmapItem(m_listWidget.value(0));
        pItem->setVisible(false);
    }
    else
    {
        m_listWidget.value(0)->readImageFile(m_listImagePath.value(m_nCurrentIndex-1,""),0);
    }

    m_listWidget.value(1)->readImageFile(m_listImagePath.value(m_nCurrentIndex,""),1);

    //隐藏越界item
    if(m_nCurrentIndex+1 == m_listImagePath.length())
    {
        BlackPixmapItem *pItem  = getPixmapItem(m_listWidget.value(2));
        pItem->setVisible(false);
    }
    else
    {
        m_listWidget.value(2)->readImageFile(m_listImagePath.value(m_nCurrentIndex+1,""),2);
    }
}

//清除item图片
void ImageView::slot_clearItemPixmap()
{
    BlackPixmapItem *pItem  = getPixmapItem(m_listWidget.value(1));
    pItem->clearPixmap();
}

//鼠标按下
void ImageView::mousePress(QPoint pos)
{
    if(scaleFactor > 1.0)
    {
        ;
    }

    startPos = pos;//记录点击点与原点的差距
    m_nMoveTotalSize = 0;
}

//鼠标移动
void ImageView::mouseMove(QPoint pos)
{
    m_nMoveSize = (pos.x() - startPos.x());
    m_nMoveTotalSize += m_nMoveSize;//总移动距离
    if(scaleFactor > 1.0)
    {
        m_listWidget.value(1)->translateItem(pos,startPos);//图片拖动
    }
    else
    {
        moveWidget();//滑动界面
    }
    startPos = pos;
}

//鼠标释放
void ImageView::mouseRelease(QPoint pos)
{
    if(m_nMoveTotalSize == 0)
        return;

    if(scaleFactor > 1.0)
    {
        ;
    }
    else
    {
        //数据队列头部 or 数据队列尾部
        if((m_nCurrentIndex == 0 && m_nMoveTotalSize > 0) ||
           (m_nCurrentIndex == (m_listImagePath.size() - 1) && m_nMoveTotalSize < 0))
        {
            for(int i = 0;i<m_listWidget.size() ;i++)
            {
                QPoint endPos = QPoint(m_nWidth*i - m_nWidth,0);
                m_listWidget.value(i)->moveWidgetAnimation(m_listWidget.value(i)->pos(),endPos,200);
            }
            return;
        }

        if(m_nMoveTotalSize < -50) //向左滑动  第一个item移到最后
        {
            if(m_nCurrentIndex/12 != (m_nCurrentIndex+1)/12)
                emit sign_pageTurning((m_nCurrentIndex+1)/12,m_nCurrentIndex);//预览翻页

            int moveSize = m_nWidth + m_listWidget.value(1)->x();
            //向左移动
            for(int i = 0;i<m_listWidget.size() ;i++)
            {
                QPoint endPos = QPoint(m_listWidget.value(i)->x() - moveSize,0);
                m_listWidget.value(i)->moveWidgetAnimation(m_listWidget.value(i)->pos(),endPos,200);
            }

            m_listWidget.first()->move(m_nWidth,0);
            CustomGraphicsView *m_pImageLoad = m_listWidget.takeFirst();
            //更新最后一个item
            m_nCurrentIndex++;
            m_listWidget.append(m_pImageLoad);

            //隐藏越界item
            if(m_nCurrentIndex+1 == m_listImagePath.length())
            {
                BlackPixmapItem *pItem  = getPixmapItem(m_listWidget.value(2));
                pItem->setVisible(false);
            }
            else
                emit sign_getItemPixmap(m_nCurrentIndex+1,2);
        }
        else if(m_nMoveTotalSize > 50) //向右滑动  最后一个item移到最前面
        {
            if(m_nCurrentIndex/12 != (m_nCurrentIndex-1)/12)
                emit sign_pageTurning((m_nCurrentIndex-1)/12,m_nCurrentIndex);//预览翻页

            int moveSize = m_nWidth - m_listWidget.value(1)->x();
            //向右移动
            for(int i = 0;i<m_listWidget.size()-1 ;i++)
            {
                QPoint endPos = QPoint(m_listWidget.value(i)->x() + moveSize,0);
                m_listWidget.value(i)->moveWidgetAnimation(m_listWidget.value(i)->pos(),endPos,200);
            }

            m_listWidget.last()->move(-m_nWidth,0);
            CustomGraphicsView *m_pImageLoad = m_listWidget.takeLast();
            //更新第一个item
            m_nCurrentIndex--;
            m_listWidget.prepend(m_pImageLoad);

            //隐藏越界item
            if(m_nCurrentIndex-1 < 0)
            {
                BlackPixmapItem *pItem  = getPixmapItem(m_listWidget.value(0));
                pItem->setVisible(false);
            }
            else
                emit sign_getItemPixmap(m_nCurrentIndex-1,0);
        }

        //移动到初始位置
        for(int i = 0;i<m_listWidget.size() ;i++)
        {
            m_listWidget.value(i)->moveWidgetAnimation(m_listWidget.value(i)->pos(),QPoint(m_nWidth*i - m_nWidth,0),200);
            //m_listWidget.value(i)->move(QPoint(m_nWidth*i - m_nWidth,0));
        }
    }

    m_nMoveTotalSize = 0;//总移动距离
}

//设置当前显示图片的索引位置
void ImageView::setFileIndex(int index)
{
    m_nCurrentIndex = index;
}

//读取图片
void ImageView::readImageFile(QString filePath, int widgetID)
{
    m_listWidget.value(widgetID)->readImageFile(filePath,widgetID);
}

//获取item预览图
void ImageView::getPreviewPixmap(QPixmap pix,int index, int widgetID)
{
    QSize size = resizeImage(pix.size(),m_nWidth,m_nHeight);
    int itemID = index%12;
    qDebug()<<"ItemID "<<itemID<<index<<widgetID;
    setPreviewPixmap(pix.scaled(size.width(),size.height()),widgetID);

    BlackPixmapItem *pItem  = getPixmapItem(m_listWidget.value(1));
    pItem->setZoom(1.0);
    readImageFile(m_listImagePath.value(index),widgetID);
}

//滑动界面
void ImageView::moveWidget()
{
    //item移动
    for(int i = 0;i<m_listWidget.size() ;i++)
    {
        QPoint endPos = QPoint((m_listWidget.value(i)->x() + m_nMoveSize),0);
        m_listWidget.value(i)->move(endPos);
    }
}

//获取当前view下的item
BlackPixmapItem *ImageView::getPixmapItem(CustomGraphicsView *view)
{
    return (BlackPixmapItem *)view->items().first();
}

//图片自适应窗口
QSize ImageView::resizeImage(const QSize image,int w,int h)
{
    double width,height;

    double setWidth = (double)w;
    double setHeight = (double)h;
    // 缩放图片尺寸以适应屏幕大小
    double imageWidth = (double)image.width();
    double imageHeight = (double)image.height();

    if(setWidth/imageWidth<=setHeight/imageHeight){
        width=imageWidth*(setWidth/imageWidth);
        height=imageHeight*(setWidth/imageWidth);
    }else{
        width=imageWidth*(setHeight/imageHeight);
        height=imageHeight*(setHeight/imageHeight);
    }

    return QSize((int)width,(int)height);
}

//初始化文件列表
void ImageView::initFileList(QStringList filelist,int index)
{
    m_listImagePath = filelist;
    m_nCurrentIndex = index;
}

//图片缩放
void ImageView::setZoom(qreal zoomFactor)
{
    BlackPixmapItem *pItem = getPixmapItem(m_listWidget.value(1));
    pItem->setPos(m_listWidget.value(1)->mapToScene(QPoint(0,0)));//图片回到起始位置
    pItem->setZoom(zoomFactor);
}

void ImageView::slot_buttonClick()
{
    QString buttonName = sender()->objectName();
    if(buttonName == "preview" || buttonName == "back")//预览、返回
    {
        //退出此界面，关闭可隐藏界面定时器
        timer->stop();
        //退出此界面，关闭自动播放定时器
        if(autoplaytimer->isActive())
            autoplaytimer->stop();

        //返回、预览
        closeWidget(400);
    }
    else if(buttonName == "autoplay")  //自动播放
    {
        timer->start();
        if(autoplaytimer->isActive())
        {
            autoplaytimer->stop();
        }else
        {
            autoplaytimer->start();
        }
    }
    else if(buttonName == "enlarge") //放大
    {
        timer->start();
        scaleFactor = scaleFactor+0.2;
        setZoom(scaleFactor);
    }
    else if(buttonName == "shrink")   //缩小
    {
        timer->start();
        scaleFactor = scaleFactor-0.2;
        setZoom(scaleFactor);
    }
}
