#ifndef APP_H
#define APP_H

class QString;

class App
{
public:
    //全局配置参数
    static int LeftPanelWidth;          //左面板宽度
    static int RightPanelWidth;         //右面板宽度
    static QString PlatForm;            //平台
    static QString SendFileName;        //发送配置文件名
    static QString DeviceFileName;      //模拟设备数据文件名

    //TCP服务器配置参数
    static bool HexSendTcpServer;       //16进制发送
    static bool HexReceiveTcpServer;    //16进制接收
    static bool DebugTcpServer;         //启用数据调试
    static bool AutoSendTcpServer;      //自动发送数据
    static int IntervalTcpServer;       //发送数据间隔
    static int TcpListenPort;           //监听端口

    //TCP客户端配置参数
    static bool HexSendTcpClient;       //16进制发送
    static bool HexReceiveTcpClient;    //16进制接收
    static bool DebugTcpClient;         //启用数据调试
    static bool AutoSendTcpClient;      //自动发送数据
    static int IntervalTcpClient;       //发送数据间隔
    static QString TcpServerIP;         //服务器IP
    static int TcpServerPort;           //服务器端口

    //UDP服务器配置参数
    static bool HexSendUdpServer;       //16进制发送
    static bool HexReceiveUdpServer;    //16进制接收
    static bool DebugUdpServer;         //启用数据调试
    static bool AutoSendUdpServer;      //自动发送数据
    static int IntervalUdpServer;       //发送数据间隔
    static int UdpListenPort;           //监听端口
    static QString UdpClientIP;         //客户端IP
    static int UdpClientPort;           //客户端端口

    //读写配置参数及其他操作
    static void ReadConfig();           //读取配置参数
    static void WriteConfig();          //写入配置参数
    static void NewConfig();            //以初始值新建配置文件
    static bool CheckConfig();          //校验配置文件
    static void WriteError(QString str);//写入错误信息
    static void NewDir(QString dirName);//新建目录

};

#endif // APP_H
