   Qt中使用QSettings类读取ini后缀的配置文件非常简单，使用该类也可以很简单的操作Windows注册表。以前也使用过MFC中的WritePrivateProfileString()和GetPrivateProfileString()这两个API操作ini配置文件。
## 使用QSettings类读写ini配置文件的示例代码
### 相关代码如下：
// test.cpp

```cpp
#include <QCoreApplication>
#include <QSettings>
#include <iostream>
#include <QDebug>

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString fileName;
    fileName = QCoreApplication::applicationDirPath();
    fileName += "/config/net.ini";

    QSettings settings(fileName, QSettings::IniFormat);
    // 设置服务器的ip和端口信息
    settings.beginGroup("server");
    settings.setValue("ip", "192.168.1.120");
    settings.setValue("port", 10001);
    settings.endGroup();

    // 设置数据库连接信息
    settings.beginGroup("dbInfo");
    settings.setValue("dbSource", "MySQL");
    settings.setValue("host", "15.15.0.216");
    settings.setValue("port", 9011);
    settings.setValue("username", "root");
    settings.setValue("password", "123456");
    settings.setValue("dbName", "HBHazeDB");
    settings.endGroup();

    // 读取ini文件
    settings.setIniCodec("UTF8");  // 设置编码方式  --->解析ini配置文件中的文字问题
    // 获取server分组下的ip和端口信息
    settings.beginGroup("server");
    QString strIp = settings.value("ip").toString();
    int port = settings.value("port").toInt();
    settings.endGroup();

    // 获取dbInfo分组下的数据库连接信息
    settings.beginGroup("dbInfo");
    QString dbSource = settings.value("dbSource").toString();
    QString host = settings.value("host").toString();
    int dbPort = settings.value("port").toInt();
    QString username = settings.value("username").toString();
    QString password = settings.value("password").toString();
    QString dbName = settings.value("dbName").toString();
    settings.endGroup();

    qDebug() << "server info:[" << "ip:" << strIp << ",port:" << port << "]";

    qDebug() << "dbInfo:[" << "dbSource:" << dbSource << ",host:" << host <<
                ",dbPort:" << dbPort << ",username:" << username
             << ",password:" << password << ",dbName:" << dbName << "]";


    return a.exec();
}
```

### 对应的net.ini配置文件如下：
```ini
[server]
ip=192.168.1.120
port=10001

[dbInfo]
dbSource=MySQL
host=192.168.0.101
port=8099
username=root
password=123456
dbName=testDB
```
## 参考文章
* [QSettings读写注冊表、配置文件](https://www.cnblogs.com/claireyuancy/p/7095249.html)
* [QSettings官方文档](https://doc.qt.io/qt-5/qsettings.html)
