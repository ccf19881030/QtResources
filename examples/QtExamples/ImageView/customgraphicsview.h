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
#ifndef CUSTOMGRAPHICSVIEW_H
#define CUSTOMGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QMouseEvent>
#include <QResizeEvent>

#include "blackpixmapitem.h"
#include <QPropertyAnimation>
#include <QDebug>

#include <QThread>
#include "imageloadthread.h"

#include <QLabel>
#include <QMovie>

class CustomGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit CustomGraphicsView(QGraphicsScene *scene, QWidget *parent =0, bool isPreview =false);
    ~CustomGraphicsView();
    //窗口移动动画
    void moveWidgetAnimation(const QPoint &startPos = QPoint(-1024,0), const QPoint &endPos = QPoint(0,0), int duration = 800);//显示控制
    void setSize(int w,int h);//设置窗口大小

    void readImageFile(const QString filePath, int widgetID);//读取文件

    void translateItem(QPoint pos, QPoint lastpos);//窗口图片移动

protected:
    void mousePressEvent(QMouseEvent *event);//鼠标点击，预览模式下有用
    void mouseMoveEvent(QMouseEvent *event);//鼠标移动，预览模式下有用
    void mouseReleaseEvent(QMouseEvent *event);//鼠标释放，预览模式下有用
    void resizeEvent(QResizeEvent *);//窗口大小改变，item缩放

signals:
    void sign_itemClicked(QPixmap,QRect,int);///item点击
    void sign_readImageFile(const QString filePath, int itemID);//读取图片文件

public slots:
    void slot_readFinished(int,QImage);//图片加载完成
    void slot_readFailed(int,QString);//图片加载失败

private:
    QPoint itemPos;//鼠标点击位置
    bool m_bIsPreview;//是否为预览模式

    int m_nWidth;//view宽
    int m_nHeight;//view高

    QRect initRect;//初始位置

    ImageLoadThread *m_pImageRead;//图片加载
    QThread *thread;

    QLabel *label;
    QMovie *movie;
};

#endif // CUSTOMGRAPHICSVIEW_H
