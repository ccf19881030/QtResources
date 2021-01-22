#ifndef QICMP_H
#define QICMP_H

#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <QThread>
//ip头部
typedef struct{
    unsigned char hdr_len:4;
    unsigned char version:4;
    unsigned char tos;
    unsigned short total_len;
    unsigned short indentifier;
    unsigned short frag_and_flags;
    unsigned char ttl;
    unsigned char protolcol;
    unsigned short checksum;
    unsigned long sourceIP;
    unsigned long destIP;
}IP_HEADER;

//ICMP头部
typedef struct{
    BYTE type;
    BYTE code;
    USHORT cksum;
    USHORT id;
    USHORT seq;
}ICMP_HEADER;

//报文解码结构
typedef struct{
    USHORT usSeqNo;
    DWORD dwRoundTripTime;
    in_addr dwIPaddr;
}DECODE_RESULT;


//主类

class QIcmp : public QThread
{
    Q_OBJECT
public:
    QIcmp(QObject *parent=0);
    static int index;
    static bool stop;
    static void initThread();
    static void stopThread();

    BOOL DecodeIcmpResponse(char *pBuf,int iPackSize,DECODE_RESULT &DecodeResult,
                            BYTE ICMP_ECHO_REPLY,BYTE ICMP_TIMEOUT);
    USHORT checksum(USHORT *pBuf,int iSize);
    void startPing();
    void setIpAddress(char *ipAddress);
    void setIpList(QStringList ipList);
    void setTimeout(int timeout);

signals:
    void message(int tripTime,QString destIp,QString status);

private:
    void run();
    char *IpAddress;
    int  iTimeout;
    QStringList ipAddrs;
};

#endif // QICMP_H
