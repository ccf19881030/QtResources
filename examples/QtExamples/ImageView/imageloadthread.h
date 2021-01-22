/****************************************************************
** ImageLoadThread
** 图片加载类，移入线程
**
** imageloadthread.h
**
** Zhou Tao   2017-05-18T11:36:16
**
** QQ : 741301964
**
** 深圳市XX电子股份有限公司
**
****************************************************************/
#ifndef IMAGELOADTHREAD_H
#define IMAGELOADTHREAD_H

#include <QObject>
#include <QWidget>
#include <QImage>
#include <QImageReader>
#include <QPainter>
#include <QDebug>

class ImageLoadThread : public QObject
{
    Q_OBJECT
public:
    explicit ImageLoadThread(int width ,int height,bool preview = false);
    //int getFileID(){return fileID;}

    void readImageFile(const QStringList filePathList, int firstLoad);//读取文件列表中的文件
    void readImageFile(const QString filePath, int itemID);//读取文件
    QSize resizeImage(const QSize image,int w,int h);//图片自适应窗口

signals:
    void sign_readFinished(int,QImage);//图片读取完成
    void sign_readFailed(int,const QString filename);//图片读取失败

public slots:
    void slot_readImageFile(const QString filePath, int widgetID);//读取图片
    void slot_readImageFile(const QStringList filePath, int firstLoad = 0);//读取图片文件

private:
    QImage image;
    QImageReader imageReader;//图片读取器
    QString pmfilename;//文件路径

    int m_nWidth;
    int m_nHeight;
    bool m_bIsPreview;//是否为预览模式
};

#endif // IMAGELOADTHREAD_H
