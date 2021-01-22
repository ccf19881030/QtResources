#include "everyday_page.h"

EverydayPage::EverydayPage(QWidget *parent)
    : QWidget(parent)
{
    layout = new QVBoxLayout(this);
    imageLabel = new QLabel();
    infoLabel = new QLabel();

    http = new QNetworkAccessManager(this);
    http2 = new QNetworkAccessManager(this);

    imageLabel->setFixedHeight(200);
    imageLabel->setScaledContents(true);
    infoLabel->setWordWrap(true);

    QHBoxLayout *imageLayout = new QHBoxLayout();
    imageLayout->addSpacing(15);
    imageLayout->addWidget(imageLabel);
    imageLayout->addSpacing(15);

    QHBoxLayout *infoLayout = new QHBoxLayout();
    infoLayout->addSpacing(20);
    infoLayout->addWidget(infoLabel);
    infoLayout->addSpacing(20);

    layout->addSpacing(10);
    layout->addLayout(imageLayout);
    layout->addSpacing(10);
    layout->addLayout(infoLayout);

    QNetworkRequest request;
    request.setUrl(QUrl("http://open.iciba.com/dsapi/"));
    http->get(request);

    connect(http, SIGNAL(finished(QNetworkReply *)), this, SLOT(replyfinished(QNetworkReply *)));
    connect(http2, SIGNAL(finished(QNetworkReply *)), this, SLOT(loadImagefinished(QNetworkReply *)));
}

void EverydayPage::replyfinished(QNetworkReply *reply)
{
    QByteArray wordInformation = reply->readAll();

    QJsonDocument docment = QJsonDocument::fromJson(wordInformation);

    QJsonObject object;

    if (!docment.isNull())
    {
        object = docment.object();
        m_content = object.value("content").toString();
        m_note = object.value("note").toString();
        m_dateline = object.value("dateline").toString();
        m_picture = object.value("picture").toString();
    }


    if (!m_picture.isEmpty())
    {
        QNetworkRequest request;
        request.setUrl(QUrl(m_picture));
        http2->get(request);
    }

    QString info = NULL;
    info.append(m_content);
    info.append("\n");
    info.append(m_note);
    info.append("\n\n");
    info.append(m_dateline);

    infoLabel->setText(info);
}

void EverydayPage::loadImagefinished(QNetworkReply *reply)
{
    QByteArray data = reply->readAll();
    QPixmap pixmap;
    pixmap.loadFromData(data);
    imageLabel->setPixmap(pixmap);
}
