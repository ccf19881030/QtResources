#include "tcpserver.h"
#include "qhostaddress.h"

TcpClient::TcpClient(int clientID, QObject *parent) :
    QTcpSocket(parent)
{
    this->clientID = clientID;
    connect(this, SIGNAL(readyRead()), this, SLOT(readData()));
    connect(this, SIGNAL(disconnected()), this, SLOT(disConnect()));
}

void TcpClient::readData()
{
    if (bytesAvailable() <= 0) {
        return;
    }

    QByteArray data = readAll();
    emit clientReadData(clientID, peerAddress().toString(), peerPort(), data);
}

void TcpClient::disConnect()
{
    emit clientDisConnect(clientID, peerAddress().toString(), peerPort());
}


TcpServer::TcpServer(QObject *parent) :
    QTcpServer(parent)
{
    clientCount = 0;
}

void TcpServer::incomingConnection(int handle)
{
    TcpClient *client = new TcpClient(handle, this);
    client->setSocketDescriptor(handle);

    connect(client, SIGNAL(clientReadData(int, QString, int, QByteArray)),
            this, SIGNAL(clientReadData(int, QString, int, QByteArray)));
    connect(client, SIGNAL(clientDisConnect(int, QString, int)),
            this, SLOT(disConnect(int, QString, int)));

    QString ip = client->peerAddress().toString();
    int port = client->peerPort();

    clientLists.append(client);
    clientIDs.append(handle);
    clientInfo.append(QString("%1:%2").arg(ip).arg(port));
    clientCount++;

    emit clientConnect(handle, ip, port);
}

void TcpServer::disConnect(int clientID, QString ip, int port)
{
    for (int i = 0; i < clientCount; i++) {
        if (clientIDs.at(i) == clientID) {
            clientLists.at(i)->close();
            clientLists.removeAt(i);
            clientIDs.removeAt(i);
            clientInfo.removeAt(i);
            clientCount--;
            emit clientDisConnect(clientID, ip, port);
            break;
        }
    }
}

void TcpServer::sendData(QString ip, int port, QByteArray data)
{
    for (int i = 0; i < clientCount; i++) {
        QString str = QString("%1:%2").arg(ip).arg(port);

        if (str == clientInfo.at(i)) {
            clientLists.at(i)->write(data);
            break;
        }
    }
}

void TcpServer::sendData(QByteArray data)
{
    for (int i = 0; i < clientCount; i++) {
        clientLists.at(i)->write(data);
    }
}

void TcpServer::closeAll()
{
    foreach (TcpClient *client, clientLists) {
        client->close();
    }

    this->close();
}
