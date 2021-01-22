#ifndef YOUDAOAPI_H
#define YOUDAOAPI_H

#include <QObject>

class QNetworkAccessManager;
class QNetworkRequest;
class QNetworkReply;

class YoudaoAPI : public QObject
{
    Q_OBJECT

public:
    YoudaoAPI(QObject *parent = 0);

    void searchWord(const QString &word);
    void translator(const QString &text);

private:
    QNetworkAccessManager *http;

private slots:
    void searchWordFinished(QNetworkReply *reply);
    void translatorFinished(QNetworkReply *reply);

signals:
    void searchWordFinished(QString, QString, QString, QString);
    void translatorFinished(QString);

};

#endif // YOUDAOAPI_H
