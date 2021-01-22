/***************************************************************
 *Copyright(c) 2014-2015 Company By LH Unigress
 *All rights reserved.
 *文件名称：登录日志文件
 *简要描述：保存登录时的状态信息
 *
 *当前版本：V2.0
 *作者：Kelvin Li
 *创作日期：2014/10
 *说明：
*****************************************************************/

#include <QSettings>
#include "myapp.h"

QString Myapp::AppPath = "";

//存储当前登录用户信息,方便用户密码修改和用户退出操作
QString Myapp::CurrentUserName = "";
QString Myapp::CurrentUserPwd = "";
QString Myapp::CurrentUserType = "";
QString Myapp::CurrentUserId ="";

QString Myapp::LastLoginter = "";

Myapp::Myapp()
{
}

/*
 *函数功能：读取配置文件内容
 *输入参数：无
 *输出参数：无
 *返回值:  无
*/
void Myapp::ReadConfig()
{
    QString fileName = Myapp::AppPath+"config.txt";
    //如果配置文件不存在,则以初始值继续运行
    //没有这个判断的话,配置赋值都为空
    if(!myHelper::FileIsExist(fileName))
    {
        Myapp::CurrentUserType = Myapp::CurrentUserType.toLatin1();
        return;
    }
    QSettings *set = new QSettings(fileName,QSettings::IniFormat);
    set->beginGroup("AppConfig");

    set->endGroup();

}

void Myapp::WriteConfig()
{
    QString fileName = Myapp::AppPath+"config.txt";
    QSettings *set = new QSettings(fileName,QSettings::IniFormat);

    set->beginGroup("AppConfig");

    set->setValue("LastLoginer",Myapp::LastLoginter);
    set->setValue("CurrentUserPwd",Myapp::CurrentUserPwd);
    set->setValue("CurrentUserType",Myapp::CurrentUserType);
    set->value("urrentUserId",Myapp::CurrentUserId);


    set->endGroup();
}
