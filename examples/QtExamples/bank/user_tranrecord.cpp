#include "user_tranrecord.h"
#include "ui_user_tranrecord.h"
#include "widget.h"
#include <QMessageBox>
#include "deal_user.h"
#include <QProgressDialog>
#include "worker_log.h"
#include "record.h"

extern int yyy;
extern const QString IP;
QString ReCord;

user_tranRecord::user_tranRecord(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::user_tranRecord)
{
    blocksize = 0;
    ui->setupUi(this);
    this->ui->Yesorno->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
    this->ui->Yesorno->button(QDialogButtonBox::Ok)->setText(tr("确定"));          //将buttonbox中的ok 变成汉化
    this->ui->Yesorno->button(QDialogButtonBox::Cancel)->setText(tr("取消"));
    this->ui->passward->setEchoMode(QLineEdit::Password);                   //密码方式显示文本
}

user_tranRecord::~user_tranRecord()
{
    delete ui;
}

void user_tranRecord::on_close_music_clicked()
{
    Widget w;
    //w.sound->stop();
}

void user_tranRecord::on_Yesorno_clicked(QAbstractButton *button)
{
    QString ecf = QString("%1").arg(yyy);
    this->ui->num->setText(ecf);
    str.work_num = this->ui->num->text().toInt();
    str.work_passward = this->ui->passward->text();
    str.cmd = LOOK_RECORD;

    if(this->ui->Yesorno->button(QDialogButtonBox::Ok) == button)           //判断按下的是否为"确定”按钮
    {
        if(this->ui->num->text() == "" | this->ui->passward->text() == "")
        {
            QMessageBox::warning(this, tr("警告"), tr("输入不能为空！"), QMessageBox::Ok);
            return;
        }

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

        QProgressDialog dialog(tr("正在登录"),tr("取消"), 0, 30000, this);
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
        qDebug()<<message.record;
        switch (message.cmd)
        {
            case LOOKRECORD_SUCCESS:
            {
                this->close();
                ReCord = message.record;
                record R;
                R.show();
                R.exec();
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
        }
    }
    else if(button == this->ui->Yesorno->button((QDialogButtonBox::Cancel)))
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

        Widget w;
        w.show();
        w.exec();
    }
}

void user_tranRecord::read_server()
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
