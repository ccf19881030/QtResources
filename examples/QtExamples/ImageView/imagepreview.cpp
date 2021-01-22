/****************************************************************
** ImagePreview
** 图片预览界面
**
** ImagePreview.h
**
** Zhou Tao   2017-05-23T10:52:16
**
** QQ : 741301964
**
** 深圳市XX电子股份有限公司
**
****************************************************************/
#include "imagepreview.h"
#include <QPainter>

ImagePreview::ImagePreview(QWidget *parent,int itemNum) : QWidget(parent),
    m_nItemNum(itemNum)
{
    QString fileString("D:/Work/QtProject/qmlProject/qmlTest/untitled/image/UI界面/IMG_2438.JPG,D:/Work/QtProject/qmlProject/qmlTest/untitled/image/UI界面/IMG_2439.JPG,D:/Work/QtProject/qmlProject/qmlTest/untitled/image/UI界面/IMG_2440.JPG,D:/Work/QtProject/qmlProject/qmlTest/untitled/image/UI界面/IMG_2441.JPG,D:/Work/QtProject/qmlProject/qmlTest/untitled/image/UI界面/IMG_2442.JPG,D:/Work/QtProject/qmlProject/qmlTest/untitled/image/UI界面/IMG_2443.JPG,D:/Work/QtProject/qmlProject/qmlTest/untitled/image/UI界面/IMG_2444.JPG,D:/Work/QtProject/qmlProject/qmlTest/untitled/image/UI界面/IMG_2445.JPG,D:/Work/QtProject/qmlProject/qmlTest/untitled/image/UI界面/IMG_2446.JPG,D:/Work/QtProject/qmlProject/qmlTest/untitled/image/UI界面/IMG_2447.JPG,D:/Work/QtProject/qmlProject/qmlTest/untitled/image/UI界面/IMG_2448.JPG,D:/Work/QtProject/qmlProject/qmlTest/untitled/image/UI界面/IMG_2449.JPG,D:/Work/QtProject/qmlProject/qmlTest/untitled/image/UI界面/IMG_2450.JPG,D:/Work/QtProject/qmlProject/qmlTest/untitled/image/UI界面/IMG_2451.JPG,D:/Work/QtProject/qmlProject/qmlTest/untitled/image/UI界面/IMG_2452.JPG,D:/Work/QtProject/qmlProject/qmlTest/untitled/image/UI界面/IMG_2453.JPG,D:/Work/QtProject/qmlProject/qmlTest/untitled/image/UI界面/IMG_2454.JPG,D:/Work/QtProject/qmlProject/qmlTest/untitled/image/UI界面/IMG_2455.JPG,D:/Work/QtProject/qmlProject/qmlTest/untitled/image/UI界面/IMG_2456.JPG,D:/Work/QtProject/qmlProject/qmlTest/untitled/image/UI界面/IMG_2457.JPG,D:/Work/QtProject/qmlProject/qmlTest/untitled/image/UI界面/IMG_2458.JPG,D:/Work/QtProject/qmlProject/qmlTest/untitled/image/UI界面/IMG_2459.JPG,D:/Work/QtProject/qmlProject/qmlTest/untitled/image/UI界面/IMG_2460.JPG,D:/Work/QtProject/qmlProject/qmlTest/untitled/image/UI界面/IMG_2462.JPG,D:/Work/QtProject/qmlProject/qmlTest/untitled/image/UI界面/IMG_2463.JPG,D:/Work/QtProject/qmlProject/qmlTest/untitled/image/UI界面/IMG_2464.JPG,D:/Work/QtProject/qmlProject/qmlTest/untitled/image/UI界面/IMG_2465.JPG,D:/Work/QtProject/qmlProject/qmlTest/untitled/image/UI界面/IMG_2466.JPG,D:/Work/QtProject/qmlProject/qmlTest/untitled/image/UI界面/IMG_2467.JPG,D:/Work/QtProject/qmlProject/qmlTest/untitled/image/UI界面/IMG_2468.JPG,D:/Work/QtProject/qmlProject/qmlTest/untitled/image/UI界面/IMG_2469.JPG,D:/Work/QtProject/qmlProject/qmlTest/untitled/image/UI界面/IMG_2470.JPG,D:/Work/QtProject/qmlProject/qmlTest/untitled/image/UI界面/IMG_2471.JPG,D:/Work/QtProject/qmlProject/qmlTest/untitled/image/UI界面/IMG_2472.JPG,D:/Work/QtProject/qmlProject/qmlTest/untitled/image/UI界面/IMG_2473.JPG,D:/Work/QtProject/qmlProject/qmlTest/untitled/image/UI界面/IMG_2474.JPG,D:/Work/QtProject/qmlProject/qmlTest/untitled/image/UI界面/IMG_2475.JPG,D:/Work/QtProject/qmlProject/qmlTest/untitled/image/UI界面/IMG_2495.JPG,D:/Work/QtProject/qmlProject/qmlTest/untitled/image/UI界面/IMG_2496.JPG,D:/Work/QtProject/qmlProject/qmlTest/untitled/image/UI界面/IMG_2497.JPG,D:/Work/QtProject/qmlProject/qmlTest/untitled/image/UI界面/IMG_2498.JPG,D:/Work/QtProject/qmlProject/qmlTest/untitled/image/UI界面/IMG_2499.JPG");
    fileList = fileString.split(',');

    /*读取图片*/
    m_pImageRead = new ImageLoadThread(185,120,true);
    connect(this,SIGNAL(sign_readImageFile(QStringList,int)),m_pImageRead,SLOT(slot_readImageFile(QStringList,int)));
    connect(m_pImageRead,SIGNAL(sign_readFinished(int,QImage)),this,SLOT(slot_readFinished(int,QImage)));
    connect(m_pImageRead,SIGNAL(sign_readFailed(int,QString)),this,SLOT(slot_readFailed(int,QString)));
    m_pImageRead->moveToThread(&thread);
    thread.start();

    scene = new QGraphicsScene(0,0,1024,600);

    view = new CustomGraphicsView(scene,this,true);
    view->setGeometry(0,0,1024,600);

    for(int nIndex = 0;nIndex < m_nItemNum;++nIndex)
    {
        //生成BlackPixmapItem对象
        BlackPixmapItem *pItem = new BlackPixmapItem(185,120,true);
        scene->addItem(pItem);
        QPoint point = QPoint(40+nIndex%4*(185+69),22+nIndex/4*(120+13)+85);

        pItem->setPos(view->mapToScene(point));
        pItem->setFileDirIndex(nIndex);
        m_pListItem.append(pItem);
    }

    view->show();
    connect(view,SIGNAL(sign_itemClicked(QPixmap,QRect,int)),this,SLOT(slot_itemClicked(QPixmap,QRect,int)));

    m_pImageView = new ImageView(this,1024,600);//图片浏览界面
    connect(m_pImageView,SIGNAL(sign_getItemPixmap(int,int)),this,SLOT(slot_getItemPixmap(int,int)));
    connect(m_pImageView,SIGNAL(sign_showPreviewLabel()),this,SLOT(slot_showUpDownWidget()));
    connect(m_pImageView,SIGNAL(sign_pageTurning(int,int)),this,SLOT(slot_pageTurning(int,int)));
    m_pImageView->close();

    m_nPageNum = 0;//当前预览图的页数
    m_nCurImageIndex = 0;
    initImageList(fileList,m_nCurImageIndex);

    //底部
    m_labelwidget = new QWidget(this);
    m_labelwidget->setGeometry(0,515,1024,85);

    m_pShowAnimation = new QPropertyAnimation(m_labelwidget,"pos");
    m_pCloseAnimation = new QPropertyAnimation(m_labelwidget,"pos");
    connect(m_pCloseAnimation,SIGNAL(finished()),m_labelwidget,SLOT(close()));

    //button
    m_pIconLeft = new QPushButton(m_labelwidget);//向上翻页 按钮
    m_pIconLeft->setText("<<");
    m_pIconLeft->setObjectName("Left");
    m_pIconLeft->setGeometry(267,0,157,85);
    m_pIconLeft->setEnabled(false);//不能向左翻页
    connect(m_pIconLeft,SIGNAL(pressed()),this,SLOT(slot_buttonClicked()));

    m_pIconList = new QPushButton(m_labelwidget);//进入文件列表 按钮
    m_pIconList->setText("列表");
    m_pIconList->setGeometry(267+157+10,0,157,85);

    m_pIconRight = new QPushButton(m_labelwidget);//向下翻页 按钮
    m_pIconRight->setText(">>");
    m_pIconRight->setObjectName("Right");
    m_pIconRight->setGeometry(267+157+10+157+10,0,157,85);
    connect(m_pIconRight,SIGNAL(pressed()),this,SLOT(slot_buttonClicked()));
}

void ImagePreview::showBottomWidget()
{
    m_labelwidget->show();
    m_pShowAnimation->setDuration(400);
    m_pShowAnimation->setStartValue(QPoint(0,600));
    m_pShowAnimation->setEndValue(QPoint(0,515));
    m_pShowAnimation->setEasingCurve(QEasingCurve::Linear);//缓和曲线
    m_pShowAnimation->start();
}

void ImagePreview::closeBottomWidget()
{
    m_pCloseAnimation->setDuration(400);
    m_pCloseAnimation->setStartValue(QPoint(0,515));
    m_pCloseAnimation->setEndValue(QPoint(0,600));
    m_pCloseAnimation->setEasingCurve(QEasingCurve::Linear);//缓和曲线
    m_pCloseAnimation->start();
}

//翻页
void ImagePreview::pageTurning(bool next)
{
    if(!next)
    {
        if(m_nPageNum - 1 < 0) //不能继续翻页
        {
            m_pIconLeft->setEnabled(false);
            if(!m_pIconRight->isEnabled())
                m_pIconRight->setEnabled(true);
            return;
        }
        else
        {
            if(!m_pIconRight->isEnabled())
                m_pIconRight->setEnabled(true);
            if(!m_pIconLeft->isEnabled())
                m_pIconLeft->setEnabled(true);
        }

        m_nPageNum --;

        if(m_nPageNum - 1 < 0) //不能继续翻页
        {
            m_pIconLeft->setEnabled(false);
            if(!m_pIconRight->isEnabled())
                m_pIconRight->setEnabled(true);
        }
    }
    else
    {
        if((m_nPageNum+1) * m_nItemNum >= fileList.length()) //不能继续翻页
        {
            m_pIconRight->setEnabled(false);
            if(!m_pIconLeft->isEnabled())
                m_pIconLeft->setEnabled(true);
            return;
        }
        else
        {
            if(!m_pIconRight->isEnabled())
                m_pIconRight->setEnabled(true);
            if(!m_pIconLeft->isEnabled())
                m_pIconLeft->setEnabled(true);
        }

        m_nPageNum ++;

        if((m_nPageNum+1) * m_nItemNum >= fileList.length()) //不能继续翻页
        {
            m_pIconRight->setEnabled(false);
            if(!m_pIconLeft->isEnabled())
                m_pIconLeft->setEnabled(true);
        }
    }
    qDebug()<<next<<m_nItemNum*m_nPageNum;
    m_nCurImageIndex = m_nItemNum*m_nPageNum;

    emit sign_readImageFile(fileList.mid(m_nCurImageIndex,m_nItemNum));
}

//当文件目录更改时，更新显示图片
void ImagePreview::updataImagelist(QString path)
{
    ;
}

//按键按下
void ImagePreview::slot_buttonClicked()
{
    QString buttonName = sender()->objectName();
    qDebug()<<buttonName;
    if(buttonName == "Left")
    {
        pageTurning(false);
    }
    else if(buttonName == "Right")
    {
        pageTurning(true);
    }
}

//初始化图片列表 文件列表、文件索引起始值
void ImagePreview::initImageList(QStringList &ImgList, int index)
{
    m_nCurImageIndex = index;
    m_nPageNum = m_nCurImageIndex/m_nItemNum;
    emit sign_readImageFile(ImgList.mid(m_nItemNum*m_nPageNum,m_nItemNum),m_nCurImageIndex%m_nItemNum);
    m_pImageView->initFileList(ImgList,index);
}

void ImagePreview::paintEvent(QPaintEvent *)
{
    ;
}

void ImagePreview::showEvent(QShowEvent *ev)
{
    emit sign_showTopWidget();
    showBottomWidget();
}

//图片读取完成
void ImagePreview::slot_readFinished(int id, QImage image)
{
    QPixmap pixmap;
    pixmap.convertFromImage(image);

    if(! m_pListItem.value(id)->isVisible())
        m_pListItem.value(id)->setVisible(true);
    m_pListItem.value(id)->setPixmap(pixmap);
}

//图片读取失败
void ImagePreview::slot_readFailed(int id, QString filename)
{
    //超出长度的item隐藏，否则显示默认图标（加载失败）
    if(m_nItemNum*m_nPageNum + id + 1 > fileList.length())
       m_pListItem.value(id)->setVisible(false);
    else
    {
        if(! m_pListItem.value(id)->isVisible())
        {
            m_pListItem.value(id)->setVisible(true);
        }

        qDebug()<<"fileName"<<filename;
        QPixmap pixmap(160, 120);
        pixmap.fill(Qt::green);
        m_pListItem.value(id)->setPixmap(pixmap);
    }
}

//点击预览图片
void ImagePreview::slot_itemClicked(QPixmap pixmap, QRect rect,int fileIndex)
{
    closeBottomWidget();//关闭底部窗口
    emit sign_closeTopWidget();//关闭顶部窗口
    m_pImageView->setPreviewPixmap(pixmap,1);
    m_pImageView->setFileIndex(m_nItemNum*m_nPageNum + fileIndex);
    m_pImageView->showViewAnimation(rect,400);

    if((m_nPageNum+1) * m_nItemNum + 1 > fileList.length()) //不能继续翻页
    {
        m_pIconRight->setEnabled(false);
    }
}

//获取当前item的预览图
void ImagePreview::slot_getItemPixmap(int itemIndex, int widgetID)
{
    int curIndex = itemIndex%m_nItemNum;
    BlackPixmapItem *item = m_pListItem.value(curIndex);
    if(!item)
        return;

    m_pImageView->getPreviewPixmap(item->getPixmap(),itemIndex,widgetID);
}

//显示顶部底部控件
void ImagePreview::slot_showUpDownWidget()
{
    showBottomWidget();
    emit sign_showTopWidget();
}

//翻到指定页
void ImagePreview::slot_pageTurning(int nPage,int curIndex)
{
    qDebug()<<"turn page "<<nPage;
    m_nCurImageIndex = curIndex;
    m_nPageNum = nPage;
    emit sign_readImageFile(fileList.mid(m_nPageNum*m_nItemNum,m_nItemNum),m_nCurImageIndex%m_nItemNum);

    if(m_nPageNum - 1 < 0) //不能继续翻页
    {
        m_pIconLeft->setEnabled(false);
        if(!m_pIconRight->isEnabled())
            m_pIconRight->setEnabled(true);
        return;
    }
    else
    {
        if(!m_pIconRight->isEnabled())
            m_pIconRight->setEnabled(true);
        if(!m_pIconLeft->isEnabled())
            m_pIconLeft->setEnabled(true);
    }

    if((m_nPageNum+1) * m_nItemNum >= fileList.length()) //不能继续翻页
    {
        m_pIconRight->setEnabled(false);
        if(!m_pIconLeft->isEnabled())
            m_pIconLeft->setEnabled(true);
        return;
    }
    else
    {
        if(!m_pIconRight->isEnabled())
            m_pIconRight->setEnabled(true);
        if(!m_pIconLeft->isEnabled())
            m_pIconLeft->setEnabled(true);
    }
}
