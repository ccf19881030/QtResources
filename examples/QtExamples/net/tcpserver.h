#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpSocket>
#include <QTcpServer>
#include <QStringList>

class TcpClient : public QTcpSocket
{
	Q_OBJECT
public:
	explicit TcpClient(int clientID, QObject *parent = 0);

private:
	int clientID;

signals:
	void clientReadData(int clientID, QString ip, int port, QByteArray data);
	void clientDisConnect(int clientID, QString ip, int port);

private slots:
	void readData();
	void disConnect();

public slots:

};

class TcpServer : public QTcpServer
{
	Q_OBJECT
public:
	explicit TcpServer(QObject *parent = 0);

	int getClientCount()const
	{
		return clientCount;
	}

	QStringList getClientInfo()const
	{
		return clientInfo;
	}

private:
	QList<TcpClient *> clientLists;
	QList<int> clientIDs;

	int clientCount;
	QStringList clientInfo;

protected:
	void incomingConnection(int handle);

signals:
	void clientReadData(int clientID, QString ip, int port, QByteArray data);
	void clientConnect(int clientID, QString ip, int port);
	void clientDisConnect(int clientID, QString ip, int port);

private slots:
	void disConnect(int clientID, QString ip, int port);

public slots:
	void sendData(QString ip, int port, QByteArray data);
    void sendData(QByteArray data);
    void closeAll();
};

#endif // TCPSERVER_H
