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
#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H

#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QMutex>
#include <QPropertyAnimation>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "customgraphicsview.h"
#include <QPushButton>

#include <QTime>

//可隐藏界面label按键ID
#define AUTOPLAYBUTTON              611  //自动播放
#define ENLARGEMENTBUTTON           612  //放大
#define SHRINKBUTTON                613  //缩小
#define PREVIEWBUTTON               614  //预览界面
#define FILELISTBUTTON              615  //目录界面

class ImageView : public QWidget
{
    Q_OBJECT
public:
    explicit ImageView(QWidget *parent = 0,int width = 1024,int height = 600);
    ~ImageView();

    void setTimerstart(bool start = true); //设置可隐藏界面定时器是否开启 true开启  false关闭

    void showWidget();//显示顶部底部控件
    void closeWidget(int duration);//关闭顶部底部控件
    void showViewAnimation(const QRect &startRect, int duration);//窗口显示动画
    void closeViewAnimation(const QRect &endRect,int duration);//窗口关闭动画
    void showView();//直接显示窗口

    void setPreviewPixmap(QPixmap, int);//设置item预览图
    void mousePress(QPoint pos);//鼠标按下
    void mouseMove(QPoint pos);//鼠标移动
    void mouseRelease(QPoint pos);//鼠标释放

    void setFileIndex(int);//设置当前显示图片的索引位置
    void readImageFile(QString filePath,int widgetID);//读取图片
    void getPreviewPixmap(QPixmap,int,int);//获取item预览图

    QSize resizeImage(const QSize image,int w,int h);//图片自适应窗口
    void initFileList(QStringList filelist, int index);//初始化文件列表
    void setZoom(qreal zoomFactor);//图片缩放
signals:
    void sign_showPreviewLabel();//显示预览底部和顶部界面
    void sign_getItemPixmap(int itemIndex, int widgetID);//获取item预览图
    void sign_backMenu();//返回主菜单
    void sign_pageTurning(int,int);//预览翻页

public slots:
    void slot_buttonClick();   //按键信号

    void slot_autoplay();//图片自动播放

    void slot_mouseClick(void);         //获取子界面pictureview点击信息，收起工具栏
    void slot_readImage();              //初始化加载图片
    void slot_clearItemPixmap();        //清除item图片

private:
    void closeBottomWidget(void);    //关闭底部工具栏
    void showBottomWidget(void);     //显示底部工具栏
    void moveWidget();   //滑动界面
    BlackPixmapItem *getPixmapItem(CustomGraphicsView *);//获取当前view下的item

    QWidget *m_BottomWidget;          //底部触控窗口

    QPushButton *m_autoplaybutton;          //图片自动播放按键
    QPushButton *m_filelistbutton;          //进入文件列表
    QPushButton *m_enlargementbutton;       //放大
    QPushButton *m_shrinkbutton;            //缩小
    QPushButton *m_previewbutton;           //预览
    QPushButton *m_backbutton;           //返回

    QPropertyAnimation *m_pShowAnimation;       //显示底部Label动画
    QPropertyAnimation *m_pCloseAnimation;      //关闭底部Label动画
    QPropertyAnimation *m_pShowLabelAnimation;  //显示顶部Label动画
    QPropertyAnimation *m_pCloseLabelAnimation; //关闭顶部Label动画

    QTimer *timer;                              //用于自动关闭label窗口
    QTimer *autoplaytimer;                      //用于图片自动播放

    QList<CustomGraphicsView *> m_listWidget;//graphicsview列表
    QList<BlackPixmapItem *> m_pListItem;//item列表

    QStringList m_listImagePath;//图片路径列表
    int m_nCurrentIndex;//图片索引

    QPoint startPos;//鼠标移动初始位置
    QPoint imageLabelPos;//图片显示标签位置
    QSize imageLabelSize;//图片显示标签大小
    int m_nMoveSize;//单次移动距离
    int m_nMoveTotalSize;//总移动距离
    int m_nWidth;
    int m_nHeight;
    bool m_isMove;//鼠标是否移动
    qreal scaleFactor;//缩放因子

    QTime m_releaseTime;

protected:
    void mousePressEvent( QMouseEvent *ev);//鼠标按下
    void mouseReleaseEvent( QMouseEvent *ev);//鼠标松
    void mouseMoveEvent(QMouseEvent *ev);//鼠标移动
    //过滤掉底部窗口鼠标事件，防止按下的时候拖动
    bool eventFilter(QObject *watched, QEvent *event);
};

#endif // ImageView_H
