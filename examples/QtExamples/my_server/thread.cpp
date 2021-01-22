#include "thread.h"
#include<QDebug>
thread1::thread1(QObject *parent, int socketId):QThread(parent),socketId(socketId),myparent(parent)
{

}

void thread1::run()
{
    tcpsocket=new mytcpsocket(this);
    tcpsocket->setSocketDescriptor(socketId);

    bool b=connect(tcpsocket, SIGNAL(readyRead()),
            this, SLOT(readData()),Qt::DirectConnection);

    connect(this,SIGNAL(updaData(QByteArray)),myparent,SLOT(updataData(QByteArray)));
    connect(myparent, SIGNAL(sendData(QByteArray)),tcpsocket, SLOT(sendData(QByteArray)));
    exec();
}

void thread1::readData()
{

   QByteArray buffer=tcpsocket->readAll();

     tcpsocket->write(buffer);

    emit updaData(buffer);

}

