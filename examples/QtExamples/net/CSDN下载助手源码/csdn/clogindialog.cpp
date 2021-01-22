#include "clogindialog.h"
#include "ui_clogindialog.h"
#include <QtNetwork/qnetworkreply.h>
#include <QtNetwork/QNetworkRequest>
#include <QEventLoop>
#include <QString>
#include <QRegExp>
#include <QMessageBox>
#include <QByteArray>
#include <QDebug>
#include <QDesktopServices>
#include <QHBoxLayout>
#include <QLabel>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QFile>
#include <QTextStream>

CLoginDialog::CLoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CLoginDialog)
{
    ui->setupUi(this);

    // 先获取登录所需要的元素  失败，则退出
    getLoginFeature();

#if (QT_VERSION <= QT_VERSION_CHECK(5,0,0))
    setWindowFlags(Qt::Dialog | Qt::WindowSystemMenuHint);
#else
    setWindowFlags(Qt::WindowCloseButtonHint);
#endif

    // 初始化窗口
    init();

    // 获取用户配置
    QFile file("config.in");
    if (file.open(QFile::ReadOnly)) {

        QList<QByteArray> list = file.readAll().split('\t');
        if (list.count() == 2) {

            ui->lineEdit_Account->setText(list.at(0));
            ui->lineEdit_Pass->setText(list.at(1));
            file.close();
        }
    } else {

        // 提示
        int res = QMessageBox::information(this, QString("使用须知"),QString("本软件绿色无毒,仅供同仁学习与交流,不得用于其他用途."), QString("我同意用户须知"), QString("我不同意"));
        if (res == 0)
            return;
        else
            exit(0);
    }


}

CLoginDialog::~CLoginDialog()
{
    delete ui;
}

void CLoginDialog::init()
{
    QLabel *lab = new QLabel;
    lab->setPixmap(QPixmap("://img/login-locked.png"));
    QHBoxLayout *lay1 = new QHBoxLayout(ui->lineEdit_Account);
    lay1->addWidget(lab);
    ui->lineEdit_Account->setTextMargins(30, 0, 0, 0);

    QLabel *lab2 = new QLabel;
    lab2->setPixmap(QPixmap("://img/login-key-icon.png"));
    QHBoxLayout *lay2 = new QHBoxLayout(ui->lineEdit_Pass);
    lay2->addWidget(lab2);
    ui->lineEdit_Pass->setTextMargins(30, 0, 0, 0);

}

void CLoginDialog::on_pBtnLogin_clicked()
{
    ui->pBtnLogin->setText(QString("正在登录,请稍等。。"));
    ui->pBtnLogin->setEnabled(false);

    QNetworkRequest networkRequest;

    networkRequest.setUrl(QUrl("http://passport.csdn.net/account/login;jsessionid=57B7511FB180C423750FF8485FEB316C.tomcat1?from=http://my.csdn.net/my/mycsdn"));
    networkRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    networkRequest.setRawHeader(QByteArray("Referer"), QByteArray("https://passport.csdn.net/account/login?from=http://my.csdn.net/my/mycsdn"));
    networkRequest.setRawHeader(QByteArray("Cookie"), m_Cookie.toLatin1());
    /*
     *username=tese&password=12345651&lt=
     *LT-2534065-JtNQtbSgtdlndU5zMjpu0EETUPiWod
     *&execution=e1s1&_eventId=submit
     *
     */
    g_Account = ui->lineEdit_Account->text();
    QByteArray postData = "username=" + ui->lineEdit_Account->text().toLatin1() + "&password=" +
            ui->lineEdit_Pass->text().toLatin1() + "&lt=" + m_Lt.toLatin1() + "&execution=" +
            m_Execution.toLatin1() + "&_eventId=submit";

    QNetworkAccessManager manager;
    QNetworkReply *reply = manager.post(networkRequest, postData);

    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    QString str = reply->readAll();
    reply->deleteLater();

    // 组装新的cookie  整个网站的通行证
    QString tmp = reply->rawHeader("Set-Cookie");

    if (!tmp.isEmpty()) {

        // 重新组装cookie
        QRegExp rx("UserName=[^;]{1,30};");
        rx.indexIn(tmp);
        g_Cookie = rx.cap(0);
        rx.setPattern("UserInfo=[^;]{1,200};");
        rx.indexIn(tmp);
        g_Cookie += rx.cap();
        rx.setPattern("UserNick=[^;]{1,30};");
        rx.indexIn(tmp);
        g_Cookie += rx.cap();
        rx.setPattern("AU=[^;]{1,30};");
        rx.indexIn(tmp);
        g_Cookie += rx.cap();
        rx.setPattern("UD=[^;]{1,200};");
        rx.indexIn(tmp);
        g_Cookie += rx.cap();
        rx.setPattern("UN=[^;]{1,30};");
        rx.indexIn(tmp);
        g_Cookie += rx.cap();
        rx.setPattern("UE=[^;]{1,200};");
        rx.indexIn(tmp);
        g_Cookie += rx.cap();
        rx.setPattern("access-token=[^;]{1,200};");
        rx.indexIn(tmp);
        g_Cookie += rx.cap();
    }

    if (str.contains("userInfo") && !g_Cookie.isEmpty()) {

        // 保存账号和密码
        if (ui->checkBox_RemPass->isChecked()) {

            QFile file("config.in");
            if (file.open(QFile::WriteOnly)) {

                QTextStream out(&file);
                out<< ui->lineEdit_Account->text()<< '\t'<< ui->lineEdit_Pass->text();
                file.close();
            }
        } else {

            // 用户未勾选记住密码，则删掉配置文件
            QDir dir = QDir::currentPath();
            dir.remove("config.in");
        }
        done(1); // 登录成功，返回1
        close();
    } else {

        QMessageBox::warning(this, QString("提示"), QString("登录失败!请检查用户名和密码!"), QString("确定"));
        ui->pBtnLogin->setText(QString("登  录"));
        ui->pBtnLogin->setEnabled(true);
        qDebug()<< str;
    }
}

void CLoginDialog::getLoginFeature()
{
    // 修复:  修改https网址成http 。 用https时，会产生error creating ssl content错误

    QNetworkAccessManager manager;
    QNetworkReply *reply = manager.get(QNetworkRequest(QUrl("http://passport.csdn.net/account/login?from=http://my.csdn.net/my/mycsdn")));

    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();


    QString str = reply->readAll();
    reply->deleteLater();

    // 先判断网页访问是否成功
    if (reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt()!= 200)
    {
      //  qWarning()<< reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
        QMessageBox::warning(this, QString("警告"), QString("网络连接失败!"), QString("确定"));
        exit(0);
        return;
    }

    // 正则表达式匹配登陆元素
    /*
     *<input type="hidden" name="lt" value="LT-2780076-afAuDvwMNK0ognpslyK5X2ae1K9OVJ" />
     *<input type="hidden" name="execution" value="e2s1" />
     */

    QRegExp rx("LT-[^\"]{1,200}\"");
    rx.indexIn(str);

    m_Lt = rx.cap(0).remove("\"");

    rx.setPattern("execution\" value=\"[^\"]{4,4}\"");
    rx.indexIn(str);
    m_Execution = rx.cap(0).remove("execution\" value=\"").remove("\"");

    m_Cookie = reply->rawHeader("Set-Cookie");
    m_Cookie.remove("Path=/; HttpOnly");
}

QString CLoginDialog::getCookie()
{
    return g_Cookie;
}

void CLoginDialog::on_pBtnRegister_clicked()
{
    QDesktopServices::openUrl(QUrl("https://passport.csdn.net/account/register"));
}

QString CLoginDialog::getAccount()
{
    return g_Account;
}

QString CLoginDialog::g_Cookie;
QString CLoginDialog::g_Account;
