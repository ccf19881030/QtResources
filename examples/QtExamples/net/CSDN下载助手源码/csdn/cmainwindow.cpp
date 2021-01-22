#include "cmainwindow.h"
#include "ui_cmainwindow.h"
#include <QIcon>
#include <QDir>
#include <QFileDialog>
#include "chelp.h"
#include "clogindialog.h"
#include <QDesktopServices>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QMessageBox>

CMainWindow::CMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CMainWindow)
{
    ui->setupUi(this);

    // 设置日志输出地
    CHelp::g_pLineEdit = ui->textEdit_Log;

    CHelp::setLog(QString("登陆成功!!欢迎您使用CSDN下载助手!"));

    m_pTimer = new QTimer(this);
    connect(m_pTimer, SIGNAL(timeout()), &m_GetIntegral, SLOT(evaluateResource()));

    m_pTimerAutoRun = new QTimer(this);
    connect(m_pTimerAutoRun, SIGNAL(timeout()), this, SLOT(on_pBtnEvaluate_clicked()));

}

CMainWindow::~CMainWindow()
{
    delete ui;
  //  m_Thread.wait();
   // m_DownThread.wait();
}

void CMainWindow::init()
{
    m_pBtnIntegralInfo = new QToolButton;
    m_pBtnIntegralInfo->setText(QString("我的积分"));
    m_pBtnIntegralInfo->setIcon(QIcon("://img/Integral.png"));
    m_pBtnIntegralInfo->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    ui->toolBar->addWidget(m_pBtnIntegralInfo);
    ui->toolBar->addSeparator();
    connect(m_pBtnIntegralInfo, SIGNAL(clicked()), this, SLOT(slotBtnIntegralInfoClick()));

    m_pBtnDown = new QToolButton;
    m_pBtnDown->setText(QString("下载资源"));
    m_pBtnDown->setIcon(QIcon("://img/down.png"));
    m_pBtnDown->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    ui->toolBar->addWidget(m_pBtnDown);
    ui->toolBar->addSeparator();
    connect(m_pBtnDown, SIGNAL(clicked()), this, SLOT(slotBtnDownClick()));

    m_pBtnAbout = new QToolButton;
    m_pBtnAbout->setText(QString("关于助手"));
    m_pBtnAbout->setIcon(QIcon("://img/about.png"));
    m_pBtnAbout->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    ui->toolBar->addWidget(m_pBtnAbout);
    m_pAboutDialog = new CAboutDialog;
    connect(m_pBtnAbout, SIGNAL(clicked()), m_pAboutDialog, SLOT(show()));

    m_pBtnExit = new QToolButton;
    m_pBtnExit->setText(QString("退出系统"));
    m_pBtnExit->setIcon(QIcon("://img/exit.png"));
    m_pBtnExit->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    ui->toolBar->addWidget(m_pBtnExit);
    connect(m_pBtnExit, SIGNAL(clicked()), this, SLOT(close()));

    // 开启多线程
    m_GetIntegral.moveToThread(&m_Thread);
    connect(&m_Thread, SIGNAL(finished()), &m_GetIntegral, SLOT(deleteLater()));
    m_Thread.start();

    m_DownResource.moveToThread(&m_DownThread);
    connect(&m_DownThread, SIGNAL(finished()), &m_DownResource, SLOT(deleteLater()));
    m_DownThread.start();

    // 设置两个类所需要的cookie
    m_GetIntegral.setCookie(CLoginDialog::getCookie());
    m_DownResource.setCookie(CLoginDialog::getCookie());

    m_Account = CLoginDialog::getAccount();
    m_nIntegral =0;
    //updateUserInfoLabel(); // 更新
    // 修改成直接获取用户积分
    on_pBtnUpdateUserInfo_clicked();

    //-----
    ui->label_ShowFileInfo->setWordWrap(true);

    // -----
    connect(&m_DownResource, SIGNAL(setFileInfo(QString)), this, SLOT(showDownInfo(QString)));

    connect(&m_GetIntegral, SIGNAL(stopEvaluate()), this, SLOT(stopEvaluateTimer()));

    connect(&m_DownResource, SIGNAL(sendDownloadUrl(QString)), this, SLOT(getDownloadUrl(QString)));

    connect(&m_GetIntegral, SIGNAL(sendSimulationDownOver()), this,SLOT(getSimulationDownOverSignal()));
}

void CMainWindow::slotBtnIntegralInfoClick()
{
    ui->stackedWidget->setCurrentWidget(ui->IntegralInfoWidget);
}

void CMainWindow::slotBtnDownClick()
{
    ui->stackedWidget->setCurrentWidget(ui->DownWidget);
}

void CMainWindow::updateUserInfoLabel()
{
    ui->lab_UserInfo->setText(QString("欢迎您:  %1            您当前积分:  %2 积分").arg(m_Account).arg(m_nIntegral));
}

/*
 *
 *  关于模拟资源下载按钮:
 *
 *        从url.txt文件中获取爬虫目的网址。这里，我们通过把每次爬虫的进度覆盖到used.txt文件
 *          当中。 下一次使用时， 进行比较获得爬虫的起点网址
 *
 *        当然url.txt文件的内容可修改，添加爬虫网址。(比如c++ c区域的网址 然后程序爬虫资源内容)
 */
void CMainWindow::on_pBtnSimulationDown_clicked()
{
    // 为防止用户频繁使用，加以本次试用限制。
    static int useCount =0;
    useCount++;
    if (useCount == 3) {

        QMessageBox::warning(this, QString("提示"), QString("本软件仅供交流与学习!本次试用次数已达上限!谢谢您的使用!"), QString("确定"));
        return;
    }

    QFile file1("used.txt"); //
    QStringList list1;
    list1.clear();
    if (file1.open(QFile::ReadOnly)) {

        QTextStream in1(&file1);
        list1 = in1.readAll().split('\t');
        file1.close();
    }

    QFile file2("url.txt"); //
    file2.open(QFile::ReadOnly);
    QTextStream in(&file2);

    QStringList list = in.readAll().split("\r\n");
    file2.close();

    int lastPage = 1;
    QString url;
    if (list1.isEmpty()) {

        lastPage = 1;
        url = list.at(0);

    } else {

        if (list1.at(1).toInt()>50) {

            if (list.count()>= list.indexOf(list1.at(0)) +1) {

                url = list.at(list.indexOf(list1.at(0)) +1);

            } else {

                CHelp::setLog(QString("当前资源列表已经用完!请自行修改url.txt文件!"));
                return;
            }
        } else {


            url = list1.at(0);
            lastPage = list1.at(1).toInt() +1;
            qDebug()<< url<< "   "<< lastPage;

        }
    }

    //qDebug()<< url<< lastPage;

    m_GetIntegral.getDownUrlList(url, lastPage);

    m_GetIntegral.startSimulationDown();

    file1.open(QFile::WriteOnly);
    QTextStream out(&file1);
    out<< url<< '\t'<< QString::number(lastPage+4);
    file1.close();
}

void CMainWindow::on_pBtnUpdateUserInfo_clicked()
{
    m_nIntegral = m_GetIntegral.getIntegralNum();
    updateUserInfoLabel();
}

void CMainWindow::showDownInfo(const QString &content)
{
    ui->label_ShowFileInfo->setText(content);
}

void CMainWindow::on_pBtnDownUrlOk_clicked()
{
    QString str = ui->lineEdit_DownAdd->text();
    // 新增: 如果用户输入资源介绍页面地址，进行修改
    if (str.contains("detail")) {

        str = "http://download.csdn.net/download" + str.mid(str.indexOf("detail") + 6);
    }
    m_DownResource.resolveUrl(str, CLoginDialog::getCookie());
}

void CMainWindow::on_pBtnEvaluate_clicked()
{
    CHelp::setLog(QString("正在准备评价资源!!请稍等!"));
    // 修复
    m_pTimer->start(70000);

    ui->pBtnEvaluate->setEnabled(false);
    m_GetIntegral.getEvaluateResourceList();

    m_pTimerAutoRun->stop();
}

void CMainWindow::stopEvaluateTimer()
{
    m_pTimer->stop();
    ui->pBtnEvaluate->setEnabled(true);
    CHelp::setLog(QString("资源评价完毕!!正在刷新积分!"));
    on_pBtnUpdateUserInfo_clicked();
    QMessageBox::information(this, QString("提示"), QString("资源评价完毕!请查看积分!"),QString("确定"));
    ui->pBtnAutoRun->setChecked(false);
}

void CMainWindow::on_pBtn_StartDown_clicked()
{
    QDesktopServices::openUrl(QUrl(m_DownUrl));
}

void CMainWindow::getDownloadUrl(const QString &link)
{
   ui->lineEdit_DownUrl->setText(link);
   m_DownUrl = link;
}

void CMainWindow::on_pBtnAutoRun_clicked()
{
    // 自动运行
    on_pBtnSimulationDown_clicked();
}

void CMainWindow::getSimulationDownOverSignal()
{
    if (ui->pBtnAutoRun->isChecked()) {

        m_pTimerAutoRun->start(11*60000); // 11分钟
    }
}
