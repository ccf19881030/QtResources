/***********socket.h********************/
#ifndef SOCKET_H
#define SOCKET_H

#pragma comment(lib, "ws2_32.lib")
#include <iostream>
#include <QString>
#include <QWidget>
#include <Windows.h>

#define SERV_PORT 9000

using namespace std;

class sock  : public QWidget
{
    Q_OBJECT

public:
    void tcp_WSA();
    int tcp_init();
    int tcp_accept(int sfd);
    int tcp_connet();
};

class Communication
{
public:
    QString worker_name;
    QString worker_passward;
};

extern void tcp_WSA();
extern int  tcp_init();
extern int  tcp_accept(int sfd);
extern int  tcp_connet();

#endif
