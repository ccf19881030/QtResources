/*功能：图灵机器人，与图灵机器人聊天
 *条件：需要联网
 *作者：杜都督
 *日期：2017/04/14
 */

#ifndef TURING_H
#define TURING_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

class Turing : public QObject
{
    Q_OBJECT

public:

    explicit Turing(QObject *parent = 0);

    /**
     * @brief 向图灵机器人发送文字
     * @param str：发送的文字，可以为中文
     */
    Q_INVOKABLE void send(const QString &str);

signals:
    /**
     * @brief 接收到图灵机器人发送来的消息
     * @param str：接收到的消息
     */
    void received(const QString &str);


/*以下为该类私有成员*/
private slots:
    void readReply(QNetworkReply *r);

private:
    void initNetwork();

private:
    //network
    QNetworkAccessManager    mNetworkManager;
    QNetworkRequest          mRequest;
    QString                  mStrUrl;
};

#endif // TURING_H
