#include "qicmp.h"
#include <QStringList>
#include <QHostInfo>

using namespace std;
int QIcmp::index=0;
bool QIcmp::stop=false;

//计算网际校验和
USHORT QIcmp::checksum(USHORT *pBuf,int iSize){
    unsigned long cksum=0;
    while(iSize>1){
        cksum+=*(pBuf++);
        iSize-=sizeof(USHORT);
    }
    if(iSize){
        cksum+=*(USHORT*)pBuf;
    }
    cksum=(cksum>>16)+(cksum&0x0ffff);
    cksum+=(cksum>>16);
    return (USHORT)(~cksum);
}


void QIcmp::setIpAddress(char* ipAddress)
{
    strcpy(IpAddress,ipAddress);
}

void QIcmp::setIpList(QStringList ipList)
{
    ipAddrs=ipList;
}


void QIcmp::setTimeout(int timeout)
{
    iTimeout=timeout;
}

void QIcmp::initThread()
{
    index=0;
    stop=false;
}

void QIcmp::stopThread()
{
    stop=true;
}

void QIcmp::run()
{
    while(!stop){
        //****************************要互斥***********
        int i=index++;
        if(i>=ipAddrs.count()){
            break;
        }
        QString ip=ipAddrs.at(i);
        setIpAddress(ip.toLocal8Bit().data());
        startPing();
    }
}


//对数据包进行解码
BOOL QIcmp::DecodeIcmpResponse(char *pBuf,int iPackSize,DECODE_RESULT &DecodeResult,
                               BYTE ICMP_ECHO_REPLY,BYTE ICMP_TIMEOUT){
    IP_HEADER *pIpHdr=(IP_HEADER*)pBuf;
    int iIpHdrLen=pIpHdr->hdr_len*4;
    if(iPackSize<(int)(iIpHdrLen+sizeof(ICMP_HEADER))){
        return false;
    }

    ICMP_HEADER *pIcmpHdr=(ICMP_HEADER*)(pBuf+iIpHdrLen);
    USHORT usID,usSquNo;
    if(pIcmpHdr->type==ICMP_ECHO_REPLY){
        usID=pIcmpHdr->id;
        usSquNo=pIcmpHdr->seq;
    }else if(pIcmpHdr->type==ICMP_TIMEOUT){
        char *pInnerIpHdr=pBuf+iIpHdrLen+sizeof(ICMP_HEADER);
        int iInnerIPHdrLen=((IP_HEADER*)pInnerIpHdr)->hdr_len*4;
        ICMP_HEADER *pInnerIcmpHdr=(ICMP_HEADER*)(pInnerIpHdr+iInnerIPHdrLen);
        usID=pInnerIcmpHdr->id;
        usSquNo=pInnerIcmpHdr->seq;
    }else{
        return false;
    }

    if(usID!=(USHORT)GetCurrentProcessId() || usSquNo!=DecodeResult.usSeqNo)
        return false;

    DecodeResult.dwIPaddr.s_addr=pIpHdr->sourceIP;
    DecodeResult.dwRoundTripTime=GetTickCount()-DecodeResult.dwRoundTripTime;

    //    if(pIcmpHdr->type==ICMP_ECHO_REPLY || pIcmpHdr->type==ICMP_TIMEOUT){
    //        if(DecodeResult.dwRoundTripTime)
    //            cout<<"\t"<<DecodeResult.dwRoundTripTime<<"ms"<<flush;
    //        else
    //            cout<<"\t"<<"1ms"<<flush;
    //    }
    return true;
}

/*********************************主函数部分**************************************/
QIcmp::QIcmp(QObject *parent):QThread(parent)
{
    IpAddress=new char[255];
    char *str="localhost";
    strcpy(IpAddress,str);

    iTimeout=3000;
}
void QIcmp::startPing()
{
    WSAData wsa;
    if(WSAStartup(MAKEWORD(2,2),&wsa)!=0){
        cout<<"WSAStartup() error";
        return ;
    }


    u_long ulDestIP=inet_addr(IpAddress);
    if(ulDestIP==INADDR_NONE){
        hostent *pHostent=gethostbyname(IpAddress);
        if(pHostent){
            ulDestIP=(*(in_addr*)(pHostent->h_addr)).s_addr;
        }else{
            cout<<"你输入的ip地址域名无效!"<<endl;
            WSACleanup();
            return ;
        }
    }

    // cout<<"Tracing root to "<<IpAddress<<" with a maximum of 30 hops.\n"<<endl;

    sockaddr_in destSockAddr;
    ZeroMemory(&destSockAddr,sizeof(sockaddr_in));
    destSockAddr.sin_family=AF_INET;
    destSockAddr.sin_addr.s_addr=ulDestIP;


    SOCKET sockRaw=WSASocket(AF_INET,SOCK_RAW,IPPROTO_ICMP,NULL,0,WSA_FLAG_OVERLAPPED);

    // cout<<"socket"<<sockRaw<<endl;
    if(sockRaw==SOCKET_ERROR){
        cout<<"socket_error"<<" "<<GetLastError()<< endl;
    }

    //setTimeout(3000);
    setsockopt(sockRaw,SOL_SOCKET,SO_RCVTIMEO,(char*)&iTimeout,sizeof(iTimeout));
    setsockopt(sockRaw,SOL_SOCKET,SO_SNDTIMEO,(char*)&iTimeout,sizeof(iTimeout));

    const BYTE ICMP_ECHO_REPLY=0;
    const BYTE ICMP_ECHO_REQUEST=8;
    const BYTE ICMP_TIMEOUT=11;

    const int DEF_ICMP_DATA_SIZE=32;
    const int MAX_ICMP_PACKET_SIZE=1024;
    const DWORD DEF_ICMP_TIMEOUT=3000;
    const int DEF_MAX_HOP=30;

    char IcmpSendBuf[sizeof(ICMP_HEADER)+DEF_ICMP_DATA_SIZE];
    memset(IcmpSendBuf,0,sizeof(IcmpSendBuf));
    char IcmpRecvBuf[MAX_ICMP_PACKET_SIZE];
    memset(IcmpRecvBuf,0,sizeof(IcmpRecvBuf));

    ICMP_HEADER *pIcmpHeader=(ICMP_HEADER*)IcmpSendBuf;
    pIcmpHeader->type=ICMP_ECHO_REQUEST;
    pIcmpHeader->code=0;
    pIcmpHeader->id=(USHORT)GetCurrentProcessId();
    memset(IcmpSendBuf+sizeof(ICMP_HEADER),'E',DEF_ICMP_DATA_SIZE);

    USHORT usSeqNo=0;
    int iTTL=64;
    BOOL bReachDestHost=FALSE;
    int iMaxHot=DEF_MAX_HOP;
    DECODE_RESULT DecodeResult;

    setsockopt(sockRaw,IPPROTO_IP,IP_TTL,(char*)&iTTL,sizeof(iTTL));
    //cout<<iTTL<<flush;

    ((ICMP_HEADER*)IcmpSendBuf)->cksum=0;
    ((ICMP_HEADER*)IcmpSendBuf)->seq=htons(usSeqNo++);
    ((ICMP_HEADER*)IcmpSendBuf)->cksum=checksum((USHORT*)IcmpSendBuf,sizeof(ICMP_HEADER)+DEF_ICMP_DATA_SIZE);

    DecodeResult.usSeqNo=((ICMP_HEADER*)IcmpSendBuf)->seq;
    DecodeResult.dwRoundTripTime=GetTickCount();

    sendto(sockRaw,IcmpSendBuf,sizeof(IcmpSendBuf),0,(sockaddr*)&destSockAddr,sizeof(destSockAddr));

    sockaddr_in from;
    int iFromLen=sizeof(from);
    int iReadDataLen;

    while(1){
        iReadDataLen=recvfrom(sockRaw,IcmpRecvBuf,MAX_ICMP_PACKET_SIZE,0,(sockaddr*)&from,&iFromLen);
        if(iReadDataLen!=SOCKET_ERROR){
            if(DecodeIcmpResponse(IcmpRecvBuf,iReadDataLen,DecodeResult,ICMP_ECHO_REPLY,ICMP_TIMEOUT)){
                if(DecodeResult.dwIPaddr.s_addr==destSockAddr.sin_addr.s_addr)
                    bReachDestHost=true;
                //cout<<'\t'<<inet_ntoa(DecodeResult.dwIPaddr)<<endl;

                emit message((int)DecodeResult.dwRoundTripTime,QByteArray(IpAddress),tr("在线"));
                break;
            }
        }else if(WSAGetLastError()==WSAETIMEDOUT){
            emit message(0,QByteArray(IpAddress),tr("离线"));
            //cout<<"\t*"<<'\t'<<"Request timed out."<<endl;
            break;
        }else
            break;
    }
}



