#include "user_init.h"
#include "ui_user_init.h"
#include "widget.h"
#include "connect.h"
#include "deal_user.h"
#include <QMessageBox>
#include <QFile>
#include <QProgressDialog>

extern const QString IP;

user_init::user_init(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::user_init)
{
    blocksize = 0;
    ui->setupUi(this);
    this->ui->yesorno->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
    this->ui->yesorno->button(QDialogButtonBox::Ok)->setText(tr("确定"));          //将buttonbox中的ok 变成汉化
    this->ui->yesorno->button(QDialogButtonBox::Cancel)->setText(tr("取消"));
    this->ui->user_passward1->setEchoMode(QLineEdit::Password);                   //密码方式显示文本
    this->ui->user_passward2->setEchoMode(QLineEdit::Password);
}

user_init::~user_init()
{
    delete ui;
}

void user_init::on_close_music_clicked()
{
    Widget w;
    //w.sound->stop();
}

void user_init::on_yesorno_clicked(QAbstractButton *button)
{
    Send_MSG str;
    QString pass1, pass2;
    str.cmd = USER_INIT;
    str.user_name = this->ui->user_name->text();
    str.user_id = this->ui->user_id->text();
    pass1 = this->ui->user_passward1->text();
    pass2 = this->ui->user_passward2->text();
    str.first_money = this->ui->first_money->text();

    if(this->ui->yesorno->button(QDialogButtonBox::Ok) == button)           //判断按下的是否为"确定”按钮
    {
        if(this->ui->user_name->text() == "" | this->ui->user_id->text() == "" | this->ui->user_passward1->text() == "" |
                this->ui->user_passward2->text() == "" | this->ui->first_money->text() == "")
        {
            QMessageBox::warning(this, tr("警告"), tr("输入不能为空！"), QMessageBox::Ok);
            return;
        }
        if(pass1 != pass2)
        {
            QMessageBox::warning(this, tr("警告"), tr("密码输入错误，请再次输入！"), QMessageBox::Ok);
            return;
        }
        str.user_passward = pass1;

        tcpsocket = new QTcpSocket(this);
        tcpsocket->abort();
        tcpsocket->connectToHost(IP, SERV_PORT);

        QByteArray block;
        QDataStream out(&block, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_4_0);
        out<<(quint16)0;
        out<<str;
        out.device()->seek(0);
        out<<(quint16)(block.size()-sizeof(quint16));
        tcpsocket->write(block, block.length());

        connect(tcpsocket, SIGNAL(readyRead()), this, SLOT(read_server()));

        QProgressDialog dialog(tr("正在注册"),tr("取消"), 0, 30000, this);
        dialog.setWindowTitle(tr("进度"));
        dialog.setWindowModality(Qt::WindowModal);
        dialog.show();
        for(int k = 0; k < 30000; k++)
        {
            dialog.setValue(k);
            QCoreApplication::processEvents();
            if(dialog.wasCanceled())
            {
                break;
            }
        }
        dialog.setValue(30000);

        switch(message.cmd)
        {
            case INIT_SUCCESS:                                                      //注册成功
            {
                QString str1 = QString("注册成功\n账号为%1").arg(message.user_num);
                QMessageBox::information(this, tr("消息"), str1, QMessageBox::Ok);
                SaveUserInit();                                                     //账户保存本地
                this->close();
                deal_user D(this);
                D.show();
                D.exec();
                break;
            }
            case ERROR:                                                             //注册失败
            {
                QMessageBox::information(this, tr("消息"), tr("注册失败：该用户已被注册!"), QMessageBox::Ok);
                this->close();
                deal_user D(this);
                D.show();
                D.exec();
                break;
            }
        }

    }
    else if(button == this->ui->yesorno->button((QDialogButtonBox::Cancel)))
    {
        this->close();

        QProgressDialog dialog(tr("正在返回主界面"),tr("取消"), 0, 30000, this);
        dialog.setWindowTitle(tr("进度"));
        dialog.setWindowModality(Qt::WindowModal);
        dialog.show();
        for(int k = 0; k < 30000; k++)
        {
            dialog.setValue(k);
            QCoreApplication::processEvents();
            if(dialog.wasCanceled())
            {
                break;
            }
        }
        dialog.setValue(30000);

        deal_user D(this);
        D.show();
        D.exec();
    }
}

void user_init::read_server()
{
    QDataStream in(tcpsocket);

    in.setVersion(QDataStream::Qt_4_6);                 //加密传输
    if(blocksize == 0)
    {
        if(tcpsocket->bytesAvailable() < (int)sizeof(quint16))
        {
            return;
        }
        in>>blocksize;
    }
    if(tcpsocket->bytesAvailable() < blocksize)
    {
        return;
    }
    in>>message;                                        //将读到的存入message

}

void user_init::SaveUserInit()                          //存折信息保存本地以打印
{
    QDateTime current_date_time = QDateTime::currentDateTime();
    QString current_date = current_date_time.toString("yyyy-MM-dd hh:mm:ss");
    QString save = QString("户名\t账号\t开户银行\t开户金额\t\t日期\n%1\t%2\t中国银行\t%3\t\t%4\n\n\n\t日期\t\t现存\t支出\t利息\t 转账 \t\t余额\t\t职工号").arg(message.user_name).arg(message.user_num).arg(message.money).arg(current_date);
    qDebug()<<save;

    QString filename = QString("%1的存折.txt").arg(message.user_name);
    QFile file(filename);
    if(!file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        qDebug()<<file.errorString();
    }
    file.write(save.toLatin1());
    file.close();
}
