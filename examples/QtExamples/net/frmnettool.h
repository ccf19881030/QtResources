#ifndef FRMNETTOOL_H
#define FRMNETTOOL_H

#include <QWidget>

class QTcpSocket;
class TcpServer;
class QUdpSocket;

namespace Ui
{
class frmNetTool;
}

class frmNetTool : public QWidget
{
    Q_OBJECT

public:
    explicit frmNetTool(QWidget *parent = 0);
    ~frmNetTool();

private:
    Ui::frmNetTool *ui;

    int msgMaxCount;
    int countTcpServer;
    int countTcpClient;
    int countUdpServer;

    QStringList keys;           //模拟设备回复数据key
    QStringList values;         //模拟设备回复数据value

    QTcpSocket *tcpClient;
    TcpServer *tcpServer;
    QUdpSocket *udpServer;

    QTimer *timerTcpClient;
    QTimer *timerTcpServer;
    QTimer *timerUdpServer;

private slots:
    void initForm();
    void initConfig();
    void saveConfig();
    void readSendData();        //读取发送配置文件数据
    void readDeviceData();      //读取设备转发文件数据

    void sendDataTcpServer();
    void sendDataTcpServer(QString data);
    void sendDataTcpServer(QString ip, int port, QString data);

    void sendDataTcpClient();
    void sendDataTcpClient(QString data);

    void sendDataUdpServer();
    void sendDataUdpServer(QString data);
    void sendDataUdpServer(QString ip, int port, QString data);

    void appendTcpClient(quint8 type, QString msg);
    void appendTcpServer(quint8 type, QString msg);
    void appendUdpServer(quint8 type, QString msg);

private slots:
    void tcpClientReadData();
    void tcpClientReadError();

    void clientReadData(int, QString ip, int port, QByteArray data);
    void clientConnect(int, QString ip, int port);
    void clientDisConnect(int, QString ip, int port);

    void udpServerReadData();
    void udpServerReadError();

private slots:
    void on_btnTcpListen_clicked();
    void on_btnClearTcpServer_clicked();

    void on_btnTcpConnect_clicked();
    void on_btnClearTcpClient_clicked();

    void on_btnUdpListen_clicked();
    void on_btnClearUdpServer_clicked();
};

#endif // FRMNETTOOL_H
