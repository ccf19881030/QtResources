/***********socket.c********************/
#include "socket.h"
#include <QMessageBox>
#include <QWidget>
#include <QDebug>
#include <Windows.h>

void sock::tcp_WSA()
{
	WSADATA lpWSAD;
	WORD wVer = MAKEWORD(2,2);
    int ret;
	ret = WSAStartup(wVer, &lpWSAD);
    if (ret != 0)
    {
        QMessageBox::information(this, tr("消息"), tr("连接服务器失败！"), QMessageBox::Ok);
        qDebug()<<"err"<<endl;
		return;					//初始化错误
	}
	if ( LOBYTE( lpWSAD.wVersion ) != 2 || HIBYTE( lpWSAD.wVersion ) != 2 )
	{
        //cout<<WSACleanup( )<<endl;
        qDebug()<<tr("连接服务器失败")<<endl;
		return; 
	}
}

int tcp_init()
{
    SOCKET sfd;
	sfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sfd == INVALID_SOCKET)
	{
        cout<<"socket create fail"<<endl;
        qDebug()<<"socket create fail"<<endl;
		return -1;
	}

	int ret;
	struct sockaddr_in FAR serveraddr;

	memset(&serveraddr,0,sizeof(struct sockaddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(SERV_PORT);
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);

	ret = bind(sfd, (struct sockaddr *)&serveraddr, sizeof(struct sockaddr));
	if (ret == SOCKET_ERROR)
	{
        cout<<"bind fail"<<endl;
        qDebug()<<"bind fail"<<endl;
		return -1;
	}

	ret = listen(sfd, 10);
	if (ret == SOCKET_ERROR)
	{
        cout<<"listen fail"<<endl;
        qDebug()<<"listen fail"<<endl;
		return -1;
	}

	return sfd;
}

int  tcp_accept(int sfd)
{
    SOCKET cfd;
	struct sockaddr_in FAR addr;
	int FAR addrlen = sizeof(struct sockaddr);

	cfd = accept(sfd, (struct sockaddr *)&addr, &addrlen);
	if (cfd == INVALID_SOCKET)
	{
        cout<<"accept fail"<<endl;
        qDebug()<<"accept fail"<<endl;
		return -1;
	}
	cout<<inet_ntoa(addr.sin_addr)<<" "<<ntohs(addr.sin_port)<<" success connect..."<<endl;

	return cfd;
}

int sock::tcp_connet()
{
	int ret;
    SOCKET sfd;
	sfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sfd == INVALID_SOCKET)
	{
        cout<<"socket create fail"<<endl;
        qDebug()<<"socket create fail"<<endl;
		return -1;
	}

	struct sockaddr_in FAR serveraddr;

	memset(&serveraddr, 0,sizeof(struct sockaddr_in));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(SERV_PORT);
	serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");   
    //connect(sfd, (struct sockaddr*)&serveraddr, sizeof(struct sockaddr))
    ret = ::connect(sfd, (struct sockaddr*)&serveraddr, sizeof(struct sockaddr));   //将sfd连接至指定的服务器网络地址 serveraddr
    if (ret == SOCKET_ERROR)
    {
        QMessageBox::information(this, tr("消息"), tr("连接服务器失败！"), QMessageBox::Ok);
        qDebug()<<"connect fail"<<endl;
        return -1;
    }

	return sfd;
}
