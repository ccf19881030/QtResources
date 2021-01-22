#include "sendfileclient.h"
#include "myhelper.h"

SendFileClient::SendFileClient(QObject *parent) : QTcpSocket(parent)
{
    connect(this, SIGNAL(connected()), this, SLOT(SendData()));
    connect(this, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(displaySocketError(QAbstractSocket::SocketError)));
}

SendFileClient::~SendFileClient()
{

}

void SendFileClient::SendFile(QString fileName, QString serverIP, int serverPort)
{
    this->fileName = fileName;
    connectToHost(serverIP, serverPort);
}

void SendFileClient::SendData()
{
    emit message("与服务器建立连接成功");
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly)) {
        emit message("文件不能打开进行读取");
        disconnectFromHost();
        return;
    } else {
        emit fileSize(file.size());
    }

    qint64 size;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_7);
    QString name = myHelper::GetFileNameWithExtension(fileName);

    //写入开始符及文件名称
    emit message("发送开始符及文件名称");
    block.clear();
    out.device()->seek(0);
    out << 0x01 << name.toUtf8();
    size = block.size();
    write((char *)&size, sizeof(qint64));
    write(block.data(), size);

    if(!waitForBytesWritten(-1)) {
        emit message(QString("发送开始符数据发生错误:%1").arg(errorString()));
        disconnectFromHost();
        return;
    }

    //写入文件大小
    emit message("发送文件大小");
    block.clear();
    out.device()->seek(0);
    out << 0x02 << QString::number(file.size()).toUtf8();
    size = block.size();
    write((char *)&size, sizeof(qint64));
    write(block.data(), size);

    if(!waitForBytesWritten(-1)) {
        emit message(QString("发送文件大小数据发生错误:%1").arg(errorString()));
        disconnectFromHost();
        return;
    }

    //循环写入文件数据
    do {
        block.clear();
        out.device()->seek(0);
        //每次最多读取0xFFFF 即65535个字节发送,对于大文件如果一次性读取完内存不一定吃得消
        //每次发送的文件数据都带上一个0x02标识符
        out << 0x03 << file.read(0xFFFF);
        size = block.size();
        emit message(QString("当前发送数据大小:%1字节").arg(size));
        write((char *)&size, sizeof(qint64));
        write(block.data(), size);
        if(!waitForBytesWritten(-1)) {
            emit message(QString("发送文件数据发生错误:%1").arg(errorString()));
            disconnectFromHost();
            return;
        }
    } while(!file.atEnd());

    //写入结束符及文件名称
    emit message("发送结束符及文件名称");
    block.clear();
    out.device()->seek(0);
    out << 0x04 << name.toUtf8() ;
    size = block.size();
    write((char *)&size, sizeof(qint64));
    write(block.data(), size);

    if(!waitForBytesWritten(-1)) {
        emit message(QString("发送结束符数据发生错误:%1").arg(errorString()));
        disconnectFromHost();
        return;
    }

    emit message("发送文件完毕,等待服务器断开连接");
    waitForDisconnected();
    emit message("客户端主动断开连接");
    disconnectFromHost();
}

void SendFileClient::displaySocketError(QAbstractSocket::SocketError )
{
    emit message(QString("发生错误:%1").arg(errorString()));
}
