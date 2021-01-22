#include "mytcpsocket.h"
#include<QThread>
mytcpsocket::mytcpsocket(QObject *parent):QTcpSocket(parent)
{

}

void mytcpsocket::sendData(QByteArray byte)
{
    write(byte);
}
