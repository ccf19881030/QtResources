#ifndef EVERYDAYPAGE_H
#define EVERYDAYPAGE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

class EverydayPage : public QWidget
{
    Q_OBJECT

public:
    EverydayPage(QWidget *parent = 0);

private:
    QVBoxLayout *layout;
    QLabel *imageLabel;
    QLabel *infoLabel;

    QNetworkAccessManager *http;
    QNetworkAccessManager *http2;

    QString m_content;
    QString m_note;
    QString m_dateline;
    QString m_picture;

private slots:
    void replyfinished(QNetworkReply *reply);
    void loadImagefinished(QNetworkReply *reply);
};

#endif // EVERYDAYPAGE_H
