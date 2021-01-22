#include "myapp.h"
#include <QSettings>

QString myApp::PortName="COM1";//通信串口号
int myApp::CountChuChang=0;//出厂计数
int myApp::CountWeiXiu=0;//维修计数
bool myApp::UsePwd=false;//是否启用密码
QString myApp::PassWord="baoxue";

//读取配置信息
void myApp::ReadConfig()
{
    QSettings *set=new QSettings("configMC.txt",QSettings::IniFormat);

    myApp::PortName=set->value("AppConfig/PortName").toString();
    myApp::CountChuChang=set->value("AppConfig/CountChuChang").toInt();
    myApp::CountWeiXiu=set->value("AppConfig/CountWeiXiu").toInt();
    myApp::UsePwd=set->value("AppConfig/UsePwd").toBool();
    myApp::PassWord=set->value("AppConfig/PassWord").toString();
}

//写入配置信息
void myApp::WriteConfig()
{
    QSettings *set=new QSettings("configMC.txt",QSettings::IniFormat);

    set->clear();
    set->beginGroup("AppConfig");

    set->setValue("PortName",myApp::PortName);    
    set->setValue("CountChuChang",myApp::CountChuChang);
    set->setValue("CountWeiXiu",myApp::CountWeiXiu);
    set->setValue("UsePwd",myApp::UsePwd);
    set->setValue("PassWord",myApp::PassWord);

    set->endGroup();
}
