#include "deal_user.h"
#include "ui_deal_user.h"
#include "widget.h"
#include "worker_log.h"
#include "user_init.h"
#include "user_close.h"
#include "user_save_money.h"
#include "user_getmoney.h"
#include "user_tranaccounts.h"
#include "user_lookmoney.h"
#include "user_changepassward.h"
#include "user_account_detail.h"
#include "user_tranrecord.h"

extern QString xxx;
extern int yyy;
extern const QString IP;

deal_user::deal_user(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::deal_user)
{
    blocksize = 0;
    //sound = new QSound("../client/tiankong.wav", this);
    //sound->setLoops(-1);
    //sound->play();
    message.work_num = yyy;
    message.work_name = xxx;
    QString str = QString("职工：%1     姓名：%2   正在服务中....").arg(message.work_num).arg(message.work_name);
    qDebug()<<str;
    ui->setupUi(this);
    this->ui->welcome_label->setText(str);
}

deal_user::~deal_user()
{
    delete ui;
}

void deal_user::on_close_music_clicked()                    //关闭音乐
{
    Widget w;
    //w.sound->stop();
}

void deal_user::on_Exit_clicked()                           //退出
{
    tcpsocket = new QTcpSocket(this);
    tcpsocket->abort();
    tcpsocket->connectToHost(IP, SERV_PORT);

    Send_MSG str;
    str.cmd = EXIT;
    str.work_name = message.work_name;

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);
    out<<(quint16)0;
    out<<str;
    out.device()->seek(0);
    out<<(quint16)(block.size()-sizeof(quint16));
    tcpsocket->write(block, block.length());

    this->close();
    Widget w;
    w.show();
    w.exec();
}

void deal_user::on_init_user_clicked()                  //开户
{
    this->close();
    user_init U(this);
    U.show();
    U.exec();
}

void deal_user::on_close_account_clicked()              //销户
{
    this->close();
    user_close U(this);
    U.show();
    U.exec();
}

void deal_user::on_bank_save_clicked()                  //存款
{
    this->close();
    user_save_money U;
    U.show();
    U.exec();
}

void deal_user::on_get_money_clicked()                 //取款
{
    this->close();
    user_getmoney U;
    U.show();
    U.exec();
}

void deal_user::on_tran_accounts_clicked()              //转账
{
    this->close();
    user_tranaccounts U;
    U.show();
    U.exec();
}



void deal_user::on_look_money_clicked()                 //查看余额
{
    this->close();
    user_lookmoney U;
    U.show();
    U.exec();
}

void deal_user::on_change_passward_clicked()            //修改密码
{
    this->close();
    user_changepassward U;
    U.show();
    U.exec();
}

void deal_user::on_account_detail_clicked()             //账户明细
{
   this->close();
   user_account_detail U;
   U.show();
   U.exec();
}

void deal_user::on_tran_record_clicked()                //交易记录
{
    this->close();
    user_tranRecord U;
    U.show();
    U.exec();
}
