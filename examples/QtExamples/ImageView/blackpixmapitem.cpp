/****************************************************************
** BlackPixmapItem
** 自定义graphicsitem，用于加载图片
**
** blackpixmapitem.h
**
** Zhou Tao   2017-05-18T11:09:16
**
** QQ : 741301964
**
** 深圳市XX电子股份有限公司
**
****************************************************************/
#include "blackpixmapitem.h"

BlackPixmapItem::BlackPixmapItem(int width, int height, bool isPreview):
    m_nWidth(width),m_nHeight(height),m_bIsPreview(isPreview){
}

QRectF BlackPixmapItem::boundingRect() const
{
    return QRectF(0, 0, m_nWidth, m_nHeight);
}

//设置item图片
void BlackPixmapItem::setPixmap(const QPixmap Pixmap)
{
    prepareGeometryChange();
    pixmap = Pixmap;
    update();
}

//设置item大小
void BlackPixmapItem::setSize(int w, int h)
{
    prepareGeometryChange();
    m_nWidth = w;
    m_nHeight = h;
}

//item缩放
void BlackPixmapItem::setZoom(qreal zoomFactor)
{
    QTransform transform;
    transform.scale(zoomFactor,zoomFactor);
    transform.translate(1024*(1.0-zoomFactor)/2,600*(1.0-zoomFactor)/2);
    qDebug()<<1024*(1.0-zoomFactor)/2<<600*(1.0-zoomFactor)/2;
    setTransform(transform);
}

//清除图片
void BlackPixmapItem::clearPixmap()
{
    QPixmap clearPix = QPixmap();
    pixmap = clearPix;
    update();
}

#include <QDebug>
//绘制item
void BlackPixmapItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);

    painter->setBrush(Qt::black);//背景填充黑色
    painter->drawRoundedRect(0, 0, m_nWidth,m_nHeight, 2, 2);
    painter->setRenderHint(QPainter::SmoothPixmapTransform,Qt::SmoothTransformation);
    //绘制图片
    if(!pixmap.isNull())
    painter->drawPixmap((m_nWidth-pixmap.width())/2, (m_nHeight-pixmap.height())/2,
                        pixmap.width(),pixmap.height(),pixmap);

    //阴影遮罩
    /*if(isSelected)
    {
        painter->setBrush(Qt::gray);//背景填充
        painter->setOpacity(0.5);//透明度
        painter->drawRoundedRect(0, 0, m_nWidth,m_nHeight, 2, 2);
    }*/
}

//点击放大
void BlackPixmapItem::setFocusIn()
{
    qDebug()<<"BlackPixmapItem focusInEvent ";
    //isSelected = true;
    //update();//更新
    setScale(1.05);//放大
}

//释放缩小
void BlackPixmapItem::setFocusOut()
{
    qDebug()<<"BlackPixmapItem focusOutEvent ";
    //isSelected = false;
    //update();//更新
    setScale(1);//缩小
}
