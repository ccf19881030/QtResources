/*
 *      文件名: clogindialog.h
 *
 *      功能: 实现用户的登录
 *      工作流程: 先从csdn页面获取登录所需要的元素，再组合用户名和密码进行登录
 *             登陆成功，则关闭窗口，返回1  登陆失败，提示用户   用户关闭窗口，不返回值
 *
 *      作者: wu5151
 *      博客地址: http://blog.csdn.net/wu5151
 */

#ifndef CLOGINDIALOG_H
#define CLOGINDIALOG_H

#include <QDialog>
#include <QString>

namespace Ui {
class CLoginDialog;
}

class CLoginDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit CLoginDialog(QWidget *parent = 0);
    ~CLoginDialog();

    void getLoginFeature();

    // 供其它类获取通行证: cookie
    static QString getCookie();

    // 供主界面获取用户账号
    static QString getAccount();

    static QString g_Cookie;

    static QString g_Account; // 用户名
    
private slots:
    void on_pBtnLogin_clicked();

    void on_pBtnRegister_clicked();

private:
    void init();

    Ui::CLoginDialog *ui;

    QString m_Lt;
    QString m_Execution;
    QString m_Cookie;

};

#endif // CLOGINDIALOG_H
