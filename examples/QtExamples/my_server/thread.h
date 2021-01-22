#ifndef THREAD_H
#define THREAD_H
#include "mytcpsocket.h"
#include <QObject>
#include<QThread>
class thread1 : public QThread
{
    Q_OBJECT
public:
    thread1(QObject *parent,int socketId);
private:

    QObject *myparent;
    mytcpsocket *tcpsocket;
    int socketId;
    void run();
public slots:
    void readData();
signals:
    void updaData(QByteArray byte);
};

#endif // THREAD_H
