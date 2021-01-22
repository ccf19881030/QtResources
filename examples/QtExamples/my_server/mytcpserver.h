#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QObject>
#include<QTcpServer>
class mytcpserver : public QTcpServer
{
    Q_OBJECT
public:
    mytcpserver(QObject *parent=0);
protected:
    QObject *tcpserver;
    void incomingConnection(int socketId);
signals:
   void  updataData(QByteArray);
    void sendData(QByteArray);
};

#endif // MYTCPSERVER_H
