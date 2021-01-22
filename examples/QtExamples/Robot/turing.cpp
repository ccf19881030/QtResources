#include "turing.h"

#include <QDomDocument>
#include <QDomElement>

void Turing::send(const QString &str)
{
    QByteArray data;
    data.append(QString("info=%1").arg(str));

    mNetworkManager.post(mRequest, data);
}

Turing::Turing(QObject *parent) : QObject(parent)
{
    initNetwork();
}

void Turing::initNetwork()
{
    mStrUrl = "http://www.tuling123.com/api/product_exper/chat.jhtml";

    mRequest.setUrl(QUrl(mStrUrl));
    mRequest.setHeader(QNetworkRequest::UserAgentHeader,
        "Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/50.0.2661.102 Safari/537.36");
    mRequest.setHeader(QNetworkRequest::ContentTypeHeader,
                       "application/x-www-form-urlencoded; charset=UTF-8");

    send("");
    connect(&mNetworkManager, &QNetworkAccessManager::finished, this, &Turing::readReply);
}

void Turing::readReply(QNetworkReply *r)
{
    int statusCode = r->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    if(200 != statusCode)
    {
        qDebug() << "Status code is error:" << statusCode;
        return;
    }

    QString strContent = r->readAll();
    QDomDocument doc;
    doc.setContent(strContent);

    QDomElement root = doc.documentElement();
    QDomNodeList children = root.elementsByTagName("Content");
    for(int i = 0; i < children.count(); i++)
    {
        QDomNode node = children.at(i);
        QString content = node.toElement().text();
        emit received(content);
    }
}
