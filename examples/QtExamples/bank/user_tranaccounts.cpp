#include "user_tranaccounts.h"
#include "ui_user_tranaccounts.h"
#include "widget.h"
#include <QMessageBox>
#include "deal_user.h"
#include <QProgressDialog>
#include "worker_log.h"

extern int yyy;
extern const QString IP;

user_tranaccounts::user_tranaccounts(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::user_tranaccounts)
{
    blocksize = 0;
    ui->setupUi(this);
    this->ui->yesorno->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
    this->ui->yesorno->button(QDialogButtonBox::Ok)->setText(tr("确定"));          //将buttonbox中的ok 变成汉化
    this->ui->yesorno->button(QDialogButtonBox::Cancel)->setText(tr("取消"));
    this->ui->user_passward1->setEchoMode(QLineEdit::Password);                   //密码方式显示文本
    this->ui->user_passward2->setEchoMode(QLineEdit::Password);
}

user_tranaccounts::~user_tranaccounts()
{
    delete ui;
}

void user_tranaccounts::on_close_music_clicked()
{
    Widget w;
    //w.sound->stop();
}

void user_tranaccounts::on_yesorno_clicked(QAbstractButton *button)
{
    str.cmd = USER_TRANMONEY;
    str.user_num = this->ui->user_num->text().toInt();
    str.user_id = this->ui->user_id->text();
    QString pass1, pass2;
    pass1 = this->ui->user_passward1->text();
    pass2 = this->ui->user_passward2->text();
    str.recv_people = this->ui->tran_people->text();
    str.first_money = this->ui->tran_money->text();

    if(this->ui->yesorno->button(QDialogButtonBox::Ok) == button)           //判断按下的是否为"确定”按钮
    {
        if(this->ui->user_num->text() == "" | this->ui->user_id->text() == "" | this->ui->user_passward1->text() == "" |
                this->ui->user_passward2->text() == "" | this->ui->tran_people->text() == "" | this->ui->tran_money->text() == "")
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

        QProgressDialog dialog(tr("正在转账"),tr("取消"), 0, 30000, this);
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

        switch (message.cmd)
        {
            case TRANMONEY_SUCCESS:
            {
                QMessageBox::information(this, tr("消息"), "转账成功!", QMessageBox::Ok);
                save_data();                                    //保存本地
                this->close();
                deal_user D(this);
                D.show();
                D.exec();
                break;
            }
            case ERROR:
            {
                QMessageBox::information(this, tr("消息"), tr("账号密码不匹配!"), QMessageBox::Ok);
                this->close();
                deal_user D(this);
                D.show();
                D.exec();
                break;
            }
            case OVER_MONEY:
            {
                QString S = QString("您的余额已不足！还剩%1元").arg(message.money);
                QMessageBox::information(this, tr("消息"), S, QMessageBox::Ok);
                this->close();
                deal_user D(this);
                D.show();
                D.exec();
                break;
            }
            case NO_TRANPEOPLE:
            {
                QMessageBox::information(this, tr("消息"), tr("对方未注册!"), QMessageBox::Ok);
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

void user_tranaccounts::read_server()
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

void user_tranaccounts::save_data()
{
    QDateTime current_date_time = QDateTime::currentDateTime();
    QString current_date = current_date_time.toString("yyyy-MM-dd hh:mm:ss");
    QString save = QString("\n%1\t0.00\t%2\t0.00\t-%3\t\t%4\t\t%5").arg(current_date).arg(str.first_money).arg(str.first_money).arg(message.money).arg(yyy);
    qDebug()<<save;

    QString filename = QString("%1的存折.txt").arg(message.user_name);
    QFile file(filename);
    if(!file.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Append))
    {
        qDebug()<<file.errorString();
    }
    file.write(save.toLatin1());
    file.close();
}
