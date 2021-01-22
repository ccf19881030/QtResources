#include "app.h"
#include "myhelper.h"

QString App::AppName = "TcpFileTool";
QString App::AppPath = "";
int App::DeskWidth = 1440;
int App::DeskHeight = 900;

int App::IcoMain = 0xf021;
int App::IcoMenu = 0xf0d7;
int App::IcoMin = 0xf068;
int App::IcoMax = 0xf079;
int App::IcoNormal = 0xf0b2;
int App::IcoClose = 0xf00d;

bool App::SaveLog = false;
bool App::UseStyle = false;
QString App::StyleName = ":/qss/blue.css";
int App::FontSize = 9;
QString App::FontName = "Microsoft YaHei";

QString App::ServerIP = "127.0.0.1";
int App::ServerPort = 6005;
QString App::SendFile = "";
int App::ListenPort = 6005;

void App::ReadConfig()
{
    QString fileName = QString("%1/%2_Config.ini").arg(App::AppPath).arg(App::AppName);

    //如果配置文件大小为0,则以初始值继续运行,并生成配置文件
    QFile file(fileName);
    if (file.size() == 0) {
        WriteConfig();
        return;
    }

    QSettings *set = new QSettings(fileName, QSettings::IniFormat);
    set->beginGroup("AppConfig");

    App::SaveLog = set->value("SaveLog").toBool();
    App::UseStyle = set->value("UseStyle").toBool();
    App::StyleName = set->value("StyleName").toString();
    App::FontSize = set->value("FontSize").toInt();
    App::FontName = set->value("FontName").toString();

    App::ServerIP = set->value("ServerIP").toString();
    App::ServerPort = set->value("ServerPort").toInt();
    App::SendFile = set->value("SendFile").toString();
    App::ListenPort = set->value("ListenPort").toInt();

    set->endGroup();
}

void App::WriteConfig()
{
    QString fileName = QString("%1/%2_Config.ini").arg(App::AppPath).arg(App::AppName);

    QSettings *set = new QSettings(fileName, QSettings::IniFormat);
    set->beginGroup("AppConfig");

    set->setValue("SaveLog", App::SaveLog);
    set->setValue("UseStyle", App::UseStyle);
    set->setValue("StyleName", App::StyleName);
    set->setValue("FontSize", App::FontSize);
    set->setValue("FontName", App::FontName);

    set->setValue("ServerIP", App::ServerIP);
    set->setValue("ServerPort", App::ServerPort);
    set->setValue("SendFile", App::SendFile);
    set->setValue("ListenPort", App::ListenPort);

    set->endGroup();
}
