/*
 *      文件名: cmainwindow.h
 *
 *      功能: 程序主界面
 *
 *      作者: wu5151
 *      博客地址: http://blog.csdn.net/wu5151
 */

#ifndef CMAINWINDOW_H
#define CMAINWINDOW_H

#include <QMainWindow>
#include <QToolButton>
#include <QString>
#include <QThread>
#include "cgetintegral.h"
#include "cdownresource.h"
#include "caboutdialog.h"
#include <QTimer>

namespace Ui {
class CMainWindow;
}

class CMainWindow : public QMainWindow
{
    QThread m_Thread; // 此为模拟下载类的线程
    QThread m_DownThread; // 此为资源下载类的线程
    Q_OBJECT
    
public:
    explicit CMainWindow(QWidget *parent = 0);
    ~CMainWindow();

    void init();

protected slots:
    void slotBtnIntegralInfoClick(); // 工具栏我的积分 按钮的槽函数

    void slotBtnDownClick(); // 工具栏下载资源按钮 的槽函数

    void showDownInfo(const QString &content); // 接收下载资源界面解析后的文件信息

    void stopEvaluateTimer(); // 停止评价

    void getDownloadUrl(const QString &link); // 接收真正下载链接

    void getSimulationDownOverSignal(); // 接收模拟下载结束的信号 用于自动运行功能
    
private slots:
    void on_pBtnSimulationDown_clicked();

    void on_pBtnUpdateUserInfo_clicked();

    void on_pBtnDownUrlOk_clicked();

    void on_pBtnEvaluate_clicked();

    void on_pBtn_StartDown_clicked();

    void on_pBtnAutoRun_clicked();

protected:

    void updateUserInfoLabel(); // 更新用户的信息 帐户名和积分

private:
    Ui::CMainWindow *ui;

    QToolButton *m_pBtnIntegralInfo; // 积分信息界面
    QToolButton *m_pBtnDown; // 下载界面
    QToolButton *m_pBtnExit; //
    QToolButton *m_pBtnAbout;

    CAboutDialog *m_pAboutDialog;

    CGetIntegral m_GetIntegral;

    CDownResource m_DownResource;

    QString m_Account; // 用户名
    int m_nIntegral; // 当前积分

    QTimer *m_pTimer; // 此定时器用于评价资源，隔70秒评价一次

    QString m_DownUrl; // 资源下载界面解析后得到的URL

    QTimer *m_pTimerAutoRun; // 自动运行使用的定时器
};

#endif // CMAINWINDOW_H
