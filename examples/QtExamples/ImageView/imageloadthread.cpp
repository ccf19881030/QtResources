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
#include "imageloadthread.h"

ImageLoadThread::ImageLoadThread(int width, int height, bool preview) :
    m_nWidth(width),m_nHeight(height),m_bIsPreview(preview)
{
    imageReader.setQuality(100);//设置图片质量
    imageReader.setAutoTransform(true);
}

//读取文件列表中的文件
void ImageLoadThread::readImageFile(const QStringList filePathList,int firstLoad)
{
    readImageFile(filePathList.value(firstLoad,""),firstLoad);

    for(int nIndex = 0;nIndex<12;nIndex++)
    {
        if(firstLoad == nIndex)
            continue;

        readImageFile(filePathList.value(nIndex,""),nIndex);
    }
}

//读取文件
void ImageLoadThread::readImageFile(const QString filePath,int itemID)
{
    pmfilename = filePath;
    imageReader.setFileName(pmfilename);

    if (imageReader.canRead())
    {
        if(m_bIsPreview)//预览模式
        {
            QSize size = resizeImage(imageReader.size(),m_nWidth,m_nHeight);
            imageReader.setScaledSize(size);//设置缩放大小
        }
        else
        {
            QSize size = resizeImage(imageReader.size(),2048,1200);//压缩读取
            imageReader.setScaledSize(size);//设置缩放大小
        }

        // 读取图片
        QImage image = imageReader.read();
//        qWarning() << "thread start..." << itemID;
        emit sign_readFinished(itemID,image);
    }
    else
    {
        // 获取错误信息
        //QImageReader::ImageReaderError error = imageReader.error();
        QString strError = imageReader.errorString();
        qDebug() << "Last Error : " << strError;
        emit sign_readFailed(itemID,pmfilename);
    }
}

//图片自适应窗口
QSize ImageLoadThread::resizeImage(const QSize image,int w,int h)
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

//读取图片
void ImageLoadThread::slot_readImageFile(const QString filePath, int widgetID)
{
    readImageFile(filePath,widgetID);
}

//firstLoad 优先加载
void ImageLoadThread::slot_readImageFile(const QStringList filePath,int firstLoad)
{
    readImageFile(filePath,firstLoad);
}
