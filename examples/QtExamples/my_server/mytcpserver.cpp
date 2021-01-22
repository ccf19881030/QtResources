#include "mytcpserver.h"
#include "thread.h"
mytcpserver::mytcpserver(QObject *parent):QTcpServer(parent),tcpserver(parent)
{
    int port=8010;
    listen(QHostAddress::Any,port);

}

void mytcpserver::incomingConnection(int socketId)
{
    thread1 *th1=new thread1(tcpserver,socketId);
    th1->start();

}
