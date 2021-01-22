#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <QObject>
#include <QTcpSocket>
class tcpsocket : public QTcpSocket
{
    Q_OBJECT
public:
    tcpsocket(QObject *parent);
};

#endif // TCPSOCKET_H
