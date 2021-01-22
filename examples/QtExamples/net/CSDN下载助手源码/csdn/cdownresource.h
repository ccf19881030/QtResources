/*
 *      文件名: cdownresource.h
 *
 *      功能: 实现资源的下载
 *
 *      流程: 通过cmainwindow提供的csdn资源下载页面地址进行解析
 *          返回文件介绍信息   并且通过http请求获取真实下载地址
 *              如果出现验证码，则弹窗
 *      标注:  本类已去掉资源下载功能，改成解析出真实地址，然后调用本地游览器进行下载
 *      作者: wu5151
 *      博客地址: http://blog.csdn.net/wu5151
 */


#ifndef CDOWNRESOURCE_H
#define CDOWNRESOURCE_H

#include <QObject>
#include <QProgressBar>
#include <QtNetwork/qnetworkreply.h>
#include <QtNetwork/QNetworkRequest>
#include <QNetworkAccessManager>
#include <QFile>
#include "cvalidatedialog.h"

class CDownResource : public QObject
{
    Q_OBJECT
public:
    explicit CDownResource(QObject *parent = 0);

     // 解析资源地址 获取资源的相关信息
    void resolveUrl(const QString &url,const QString &cookie);

    void setCookie (const QString cookie);

    // 获取真实下载地址
    void getDownRealUrl(const QString &postUrl, const QString &postRef);

    // 获取验证码
    QPixmap getValidateCodePix(QString ref, int style =0);

signals:
    void setFileInfo(const QString &content); // 发送资源信息
    void sendDownloadUrl(const QString &link); // 发送真实下载地址

private:
    QString m_PostUrl;
    QString m_Cookie;

    CValidateDialog *m_pValidateDialog;

    QPixmap m_PrePixmap;
    QString m_ValidateCode;
};

#endif // CDOWNRESOURCE_H
