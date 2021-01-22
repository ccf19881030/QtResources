#ifndef MYTCPSOCKET_H
#define MYTCPSOCKET_H

#include <QObject>
#include<QTcpSocket>
class mytcpsocket : public QTcpSocket
{
Q_OBJECT
public:
    mytcpsocket(QObject *parent=0);
private slots:
   void sendData(QByteArray);
};

#endif // MYTCPSOCKET_H
