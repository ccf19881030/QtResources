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
#ifndef BLACKPIXMAPITEM_H
#define BLACKPIXMAPITEM_H

#include <QStyleOptionGraphicsItem>
#include <QMouseEvent>
#include <QWidget>
#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>

#include <QFocusEvent>

class BlackPixmapItem : public QGraphicsItem
{
public:

    explicit BlackPixmapItem(int width ,int height,bool isPreview =false);

    void setFocusIn();//点击放大
    void setFocusOut();//释放缩小
    void setPixmap(const QPixmap);//设置item图片
    QPixmap getPixmap(){return pixmap;}//获取item显示的图片
    void setSize(int w,int h);//设置item大小
    void setZoom(qreal zoomFactor);//item缩放

    void setInitPixmapSize(QSize pixmapsize){pixmapSize = pixmapsize;}//保存预览图大小
    QSize getInitPixmapSize(){return pixmapSize;}//获取保存的预览图大小

    void setFileDirIndex(int index){fileDirIndex = index;}//保存文件在列表中的索引
    int getFileDirIndex(){return fileDirIndex;}//获取索引
    void clearPixmap();//清除图片

private:
     int m_nWidth;//item宽
     int m_nHeight;//item高
     QPixmap pixmap;//显示的图片
     //bool isSelected;
     bool m_bIsPreview;//是否为预览状态
     QSize pixmapSize;//预览图大小
     int fileDirIndex;//文件路径索引

protected:
     QRectF boundingRect() const;
     void paint(QPainter *painter,
                const QStyleOptionGraphicsItem *option,QWidget *widget);//绘制item
};

#endif // BLACKPIXMAPITEM_H
