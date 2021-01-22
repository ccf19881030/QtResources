#include "receivefileserver.h"
#include "receivefilethread.h"

ReceiveFileServer::ReceiveFileServer(QObject *parent) : QTcpServer(parent)
{

}

ReceiveFileServer::~ReceiveFileServer()
{

}

bool ReceiveFileServer::startServer(int port)
{
    return listen(QHostAddress::Any, port);
}

void ReceiveFileServer::stopServer()
{
    close();
}

void ReceiveFileServer::incomingConnection(int handle)
{
    ReceiveFileThread *receiveFile = new ReceiveFileThread(handle, this);
    connect(receiveFile, SIGNAL(message(QString)), this, SIGNAL(message(QString)));
    connect(receiveFile, SIGNAL(receiveFileName(QString)), this, SIGNAL(receiveFileName(QString)));
    connect(receiveFile, SIGNAL(receiveFileSize(qint64)), this, SIGNAL(receiveFileSize(qint64)));
    connect(receiveFile, SIGNAL(receiveData(qint64)), this, SIGNAL(receiveData(qint64)));
    connect(receiveFile, SIGNAL(finished()), this, SIGNAL(finished()));
    connect(receiveFile, SIGNAL(finished()), receiveFile, SLOT(deleteLater()));
    receiveFile->start();
}
