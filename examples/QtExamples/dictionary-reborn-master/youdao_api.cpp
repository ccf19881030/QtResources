#include "youdao_api.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QByteArray>
#include <QJsonArray>

YoudaoAPI::YoudaoAPI(QObject *parent)
    : QObject(parent)
{
    http = new QNetworkAccessManager(this);
}

void YoudaoAPI::searchWord(const QString &word)
{
    QNetworkRequest request;

    request.setUrl(QUrl("http://fanyi.youdao.com/openapi.do?keyfrom=YouDaoCV&key=659600698&type=data&doctype=json&version=1.1&q=" + word));
    http->get(request);
    connect(http, SIGNAL(finished(QNetworkReply*)), this, SLOT(searchWordFinished(QNetworkReply*)));
}

void YoudaoAPI::translator(const QString &text)
{
    QNetworkRequest request;

    request.setUrl(QUrl("http://fanyi.youdao.com/openapi.do?keyfrom=YouDaoCV&key=659600698&type=data&doctype=json&version=1.1&only=translate&q=" + text));
    http->get(request);
    connect(http, SIGNAL(finished(QNetworkReply*)), this, SLOT(translatorFinished(QNetworkReply*)));
}

void YoudaoAPI::searchWordFinished(QNetworkReply *reply)
{
    QJsonDocument json;
    QJsonObject object, data;

    QByteArray wordInformation = reply->readAll();

    json = QJsonDocument::fromJson(wordInformation);

    if (!json.isNull())
    {
        object = json.object();
        data = object.value("basic").toObject();

        QString uk_phonetic = data.value("uk-phonetic").toString();
        QString us_phonetic = data.value("us-phonetic").toString();
        QString text = NULL;

        QJsonArray explain = data.value("explains").toArray();

        if (explain.isEmpty()) {
            for (int i=0; i<object.value("translation").toArray().size(); ++i) {
                text.append(object.value("translation").toArray().at(i).toString());
                text.append("\n");
            }
        }else {
            for (int i=0; i<explain.size(); ++i) {
                text.append(explain.at(i).toString());
                text.append("\n");
            }
        }

        emit searchWordFinished(object.value("query").toString(), uk_phonetic, us_phonetic, text);

        /*
        if (!data.value("phonetic").toString().isEmpty()) {
            nameLabel->setText(nameLabel->text() + " [" + data.value("phonetic").toString() + "]");
        }
        */

    }
}

void YoudaoAPI::translatorFinished(QNetworkReply *reply)
{
    QJsonDocument json;
    QJsonObject object;

    QByteArray wordInformation = reply->readAll();

    json = QJsonDocument::fromJson(wordInformation);

    if (!json.isNull())
    {
        object = json.object();

        QString text = NULL;

        for (int i=0; i<object.value("translation").toArray().size(); ++i) {
            text.append(object.value("translation").toArray().at(i).toString());
            text.append("\n");
        }

        emit translatorFinished(text);
    }
}
