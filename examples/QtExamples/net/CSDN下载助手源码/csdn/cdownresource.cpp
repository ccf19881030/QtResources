#include "cdownresource.h"
#include <QEventLoop>
#include <QRegExp>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QTime>

CDownResource::CDownResource(QObject *parent) :
    QObject(parent)
{
    m_pValidateDialog = new CValidateDialog();
}

void CDownResource::resolveUrl(const QString &url,const QString &cookie)
{
    QNetworkAccessManager manager;

    QNetworkReply *reply = manager.get(QNetworkRequest(QUrl(url)));

    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    QString str = reply->readAll();
    reply->deleteLater();

    QRegExp rx("title mb-bg\" title=[^>]{1,200}>");
    rx.indexIn(str);
    QString fileName = rx.cap().remove("title mb-bg\" title=").remove(">");

    rx.setPattern("<div class=\"cut_intro\" style=\"overflow:hidden;\">[^<]{1,1000}<");
    rx.indexIn(str);
    QString fileInfo = rx.cap(0).remove("<div class=\"cut_intro\" style=\"overflow:hidden;\">").remove("<");

    rx.setPattern("<div class=\"wraper-info\">.{1,1000}<ul class=\"tags-share\">");
    rx.indexIn(str);
    QString content = rx.cap().remove("<div class=\"wraper-info\">").remove("<ul class=\"tags-share\">");

    QString send = QString("<li>资源名: ") + fileName+"</li>" + QString("<li>资源简介:") + fileInfo+"</li>"  + content;
    send.remove('\n');

    rx.setPattern("http://download.csdn.net/index.php/source/do_download/[^\"]{1,100}\"");
    rx.indexIn(str);

    QString postUrl = rx.cap().remove("\"");

    emit setFileInfo(send);

    getDownRealUrl(postUrl, url);
}

void CDownResource::getDownRealUrl(const QString &postUrl, const QString &postRef)
{
    // 获取下载资源的真实地址
    QNetworkRequest networkRequest;

    networkRequest.setUrl(QUrl(postUrl));
    networkRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    networkRequest.setRawHeader(QByteArray("Referer"),postRef.toLatin1());
    networkRequest.setRawHeader(QByteArray("Cookie"), m_Cookie.toLatin1());

    QByteArray postData = "ds=dx&validate_code=" + m_ValidateCode.toLatin1()+"&basic%5Breal_name%5D=&basic%5Bmobile%5D=&basic%5Bemail%5D=&basic%5Bjob%5D=&basic%5Bcompany%5D=&basic%5Bprovince%5D=&basic%5Bcity%5D=&basic%5Bindustry%5D=";

    QNetworkAccessManager manager;
    QNetworkReply *reply = manager.post(networkRequest, postData);

    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    QString str = reply->readAll();
    reply->deleteLater();

    qDebug()<< str;
    QRegExp rx("http://dldx.csdn.net/[^']{1,300}'");
    rx.indexIn(str);
    m_PostUrl = rx.cap(0).remove("'");

    qDebug()<< m_PostUrl;

    if (m_PostUrl == "") {

        m_PrePixmap = getValidateCodePix(postRef, 1);

        m_pValidateDialog->setPixmap(m_PrePixmap);

        if (1 != m_pValidateDialog->exec()) // 以固态模式打开
              return;
        m_ValidateCode = m_pValidateDialog->getValidateCode();

        // 重新发出请求
        getDownRealUrl(postUrl, postRef);
    }

    emit sendDownloadUrl(m_PostUrl);
}

void CDownResource::setCookie(const QString cookie)
{
    m_Cookie = cookie;
}

QPixmap CDownResource::getValidateCodePix(QString ref, int style)
{
    // 获取验证码  "src","/index.php/rest/tools/validcode/source_ip_validate/1"+Math.random());

    // 产生随机数
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

    QString rand = "http://download.csdn.net/index.php/rest/tools/validcode/source_ip_validate/10.";
    for (int i =0; i< 16; ++i)
        rand.append(QString::number(qrand()%9));

    if (style == 1) {

        rand = "http://download.csdn.net/index.php/rest/tools/validcode/source_ip_validate";
    }

    QNetworkAccessManager manager;
    QNetworkRequest networkRequest;
    networkRequest.setUrl(QUrl(rand));
    networkRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    networkRequest.setRawHeader(QByteArray("Referer"),ref.toLatin1());
    networkRequest.setRawHeader(QByteArray("Cookie"), m_Cookie.toLatin1());

    QNetworkReply *reply = manager.get(QNetworkRequest(QUrl(rand)));

    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    QByteArray str = reply->readAll();
    reply->deleteLater();

    if (style == 1) {

        QString tmp = reply->rawHeader("Set-Cookie");
        m_Cookie = tmp.remove(" path=/") + m_Cookie;
    }

    QPixmap pixmap ;
    pixmap.loadFromData(str);
    return pixmap;
}




