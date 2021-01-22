/****************************************************************
** CustomGraphicsView
** 自定义graphicsview，用于显示加载图片的item
**
** customgraphicsview.h
**
** Zhou Tao   2017-05-18T11:23:16
**
** QQ : 741301964
**
** 深圳市XX电子股份有限公司
**
****************************************************************/
#include "customgraphicsview.h"

CustomGraphicsView::CustomGraphicsView(QGraphicsScene *scene, QWidget *parent,bool isPreview)
    :QGraphicsView(parent),m_bIsPreview(isPreview)
{
    setScene(scene);
    setStyleSheet("background: transparent;border:0px");
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setResizeAnchor(QGraphicsView::AnchorViewCenter);//居中

    if(!m_bIsPreview)
    {
        thread = new QThread(this);
        m_pImageRead = new ImageLoadThread(185,120);
        connect(m_pImageRead,SIGNAL(sign_readFinished(int,QImage)),this,SLOT(slot_readFinished(int,QImage)));
        connect(m_pImageRead,SIGNAL(sign_readFailed(int,QString)),this,SLOT(slot_readFailed(int,QString)));
        connect(this,SIGNAL(sign_readImageFile(QString,int)),m_pImageRead,SLOT(slot_readImageFile(QString,int)));
        m_pImageRead->moveToThread(thread);
        thread->start();

        label = new QLabel(this);
        label->setGeometry(462,250,100,100);
        movie = new QMovie("../image/loading.gif");
        label->setMovie(movie);

        label->close();
    } 
}

CustomGraphicsView::~CustomGraphicsView()
{
    if(!m_bIsPreview)
    {
        delete m_pImageRead;
        delete thread;
    }
}

//窗口移动动画
void CustomGraphicsView::moveWidgetAnimation(const QPoint &startPos, const QPoint &endPos, int duration)
{
    QPropertyAnimation *m_pMoveAnimation = new QPropertyAnimation(this, "pos");//移动动画
    m_pMoveAnimation->setDuration(duration);
    m_pMoveAnimation->setStartValue(startPos);
    m_pMoveAnimation->setEndValue(endPos);
    m_pMoveAnimation->setEasingCurve(QEasingCurve::Linear);//缓和曲线
    m_pMoveAnimation->start(QAbstractAnimation::DeleteWhenStopped);
}

//设置窗口大小
void CustomGraphicsView::setSize(int w, int h)
{
    m_nWidth = w;
    m_nHeight = h;
}

//读取文件
void CustomGraphicsView::readImageFile(const QString filePath, int widgetID)
{
    movie->start();
    label->show();

    qDebug()<<filePath<<widgetID;

    Q_ASSERT_X(m_pImageRead != NULL,"error","m_pImageRead is NULL!");
    if(!m_bIsPreview && widgetID >= 0) //&& !filePath.isEmpty()
    {
        emit sign_readImageFile(filePath,widgetID);
    }
}

//窗口图片移动
void CustomGraphicsView::translateItem(QPoint pos, QPoint lastpos)
{
    QPointF delta = mapToScene(pos) - mapToScene(lastpos);
    QPointF setPos = items().first()->pos() + delta;
    items().first()->setPos(setPos);

    qDebug()<<"set pos "<<items().first()->scenePos()<<items().first()->pos();
}

//鼠标点击，预览模式下有用
void CustomGraphicsView::mousePressEvent(QMouseEvent *event)
{
    if(m_bIsPreview)
    {
        itemPos = event->pos();
        if(BlackPixmapItem *selectedItem = (BlackPixmapItem*)itemAt(itemPos))
        {
            qDebug()<<"click item.";
            selectedItem->setFocusIn();//点击item放大
        }
        else
            qDebug()<<"didn't click item.";
    }
    else
        QWidget::mousePressEvent(event);
}

//鼠标移动，预览模式下有用
void CustomGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    QWidget::mouseMoveEvent(event);
}

//鼠标释放，预览模式下有用
void CustomGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    if(m_bIsPreview)
    {
        BlackPixmapItem *selectedItem = (BlackPixmapItem*)itemAt(itemPos);//按下的item
        if(selectedItem)
        {
            if(selectedItem == (BlackPixmapItem*)itemAt(event->pos()))
            {                
                selectedItem->setFocusOut();//释放item缩小

                QPoint pos = mapFromScene(selectedItem->pos());
                qDebug()<<"release item id."<<selectedItem->getFileDirIndex();
                ///item点击
                emit sign_itemClicked(selectedItem->getPixmap(),QRect(pos,QSize(185,120)),selectedItem->getFileDirIndex());
            }
            else
                selectedItem->setFocusOut();//释放item缩小
        }
        else
            qDebug()<<"didn't release item.";
    }
    else
        QWidget::mouseReleaseEvent(event);
}

//窗口大小改变，item缩放
void CustomGraphicsView::resizeEvent(QResizeEvent *)
{
    if(!m_bIsPreview)
    {
        BlackPixmapItem * item = (BlackPixmapItem*)(items().first());
        if(item){
            QSize pixmapSize = item->getInitPixmapSize();
            QSize size = m_pImageRead->resizeImage(pixmapSize,width(),height());
            item->setSize(width(),height());
            item->setPixmap(item->getPixmap().scaled(size.width(),size.height()));
        }
    }
}

//图片加载完成
void CustomGraphicsView::slot_readFinished(int id, QImage image)
{
    QSize size = m_pImageRead->resizeImage(image.size(),1024,600);
    // 平滑缩放，清晰度高
    QImage scaleImage = image.scaled(size.width(),size.height(),Qt::KeepAspectRatio,Qt::SmoothTransformation);

    QPixmap pixmap;
    pixmap.convertFromImage(scaleImage);

    BlackPixmapItem *pItem = (BlackPixmapItem *)items().first();
    if(! pItem->isVisible())
        pItem->setVisible(true);
    pItem->setSize(1024,600);
    pItem->setPixmap(pixmap);

    label->close();
    movie->stop();
}

void CustomGraphicsView::slot_readFailed(int id, QString filename)
{
    qDebug()<<"CustomGraphicsView::slot_readFailed"<<filename;
    BlackPixmapItem *pItem = (BlackPixmapItem *)items().first();
//    //文件路径为空，item隐藏
//    if(filename.isEmpty())
//    {
//        pItem->setVisible(false);
//        return;
//    }

    QPixmap pixmap(960,720);
    pItem->setSize(1024,600);
    pixmap.fill(Qt::green);
    pItem->setPixmap(pixmap);

    label->close();
    movie->stop();
}
