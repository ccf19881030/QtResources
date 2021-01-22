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
#ifndef IMAGEPREVIEW_H
#define IMAGEPREVIEW_H

#include <QWidget>
#include <QtGlobal>
#include "imageloadthread.h"
#include <QList>

#include <QThread>
#include "imageloadthread.h"
#include "blackpixmapitem.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include "customgraphicsview.h"
#include <QPushButton>

#include "imageview.h"

#include <QShowEvent>

#define   LEFTBUTTONID     608
#define   LISTBUTTONID     609
#define   RIGHTBUTTONID    610

class ImagePreview : public QWidget
{
    Q_OBJECT
public:
    explicit ImagePreview(QWidget *parent = 0,int itemNum = 12);

    QString curPath;
    QStringList fileList;

    void showBottomWidget();       //显示底部控件
    void closeBottomWidget();      //关闭底部控件
    void pageTurning(bool next);   //翻页
    void initImageList(QStringList &ImgList, int index);//初始化图片列表

    void updataImagelist(QString path);  //当文件目录更改时，更新显示图片
    void listClicked(int);//点击列表浏览图片

signals:
    void sign_sendid(int id);//发送按键值
    void sign_sendcurpath(QString curdirpath, int index); //发送当前路径给PictureControl
    void sign_closeTopWidget();//关闭顶部控件
    void sign_showTopWidget();//显示顶部控件
    void sign_readImageFile(const QStringList filePath,int firstLoad = 0);//读取图片文件

public slots:
    void slot_buttonClicked();          //按键按下
    void slot_readFinished(int,QImage);       //图片读取完成
    void slot_readFailed(int,QString);        //图片读取失败
    void slot_itemClicked(QPixmap, QRect, int);//点击预览图片
    void slot_getItemPixmap(int,int);    //获取当前item的预览图
    void slot_showUpDownWidget();        //显示顶部底部控件
    void slot_pageTurning(int nPage, int curIndex);    //翻到指定页

private:
    int m_nItemNum;//一页显示的item个数
    int m_nPageNum;//当前预览图所在的页

    QPushButton *m_pIconLeft;//向上翻页 按钮
    QPushButton *m_pIconRight;//向下翻页 按钮
    QPushButton *m_pIconList;//进入文件列表 按钮

    QWidget *m_labelwidget;          //底部触控窗口

    QPropertyAnimation *m_pShowAnimation; //显示底部窗口动画
    QPropertyAnimation *m_pCloseAnimation; //关闭底部窗口动画

    void paintEvent(QPaintEvent *);
    int m_nCurImageIndex;    //当前图片索引

    QList<BlackPixmapItem *> m_pListItem;//加载预览图的item列表

    ImageLoadThread *m_pImageRead;//图片加载类
    QThread thread;//图片加载线程
    CustomGraphicsView *view;
    QGraphicsScene *scene;

    ImageView *m_pImageView;//图片浏览界面

protected:
    void showEvent(QShowEvent *ev);
};

#endif // ImagePreview_H
