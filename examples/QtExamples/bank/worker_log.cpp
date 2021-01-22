#include "worker_log.h"
#include "widget.h"
#include "connect.h"
#include "deal_user.h"
#include "worker_init.h"
#include "ui_logging.h"
#include <QDebug>
#include <QPushButton>
#include <QProgressDialog>
#include <QMessageBox>
#include <QtNetwork>

QString xxx;
int yyy;
extern const QString IP;

void work_log::on_Yesorno_clicked(QAbstractButton *button)
{
    Send_MSG str;
    QString n = this->work_ui.num->text();
    str.work_num = n.toInt();
    qDebug()<<str.work_num;
    str.work_passward = this->work_ui.passward->text();
    qDebug()<<str.work_passward;
    str.cmd = WORKER_LOG;

    if(this->work_ui.Yesorno->button(QDialogButtonBox::Ok) == button)           //判断按下的是否为"确定”按钮
    {
        if(this->work_ui.num->text() == "" | this->work_ui.passward->text() == "")
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

        switch (message.cmd)
        {
            case LOG_SUCCESS:
            {
                xxx = message.work_name;
                yyy = message.work_num;
                QMessageBox::information(this, tr("消息"), tr("登录成功！"), QMessageBox::Ok);
                this->close();
                deal_user D(this);
                D.show();
                D.exec();
                break;
            }
            case LOG_EXIST:
            {
                QMessageBox::information(this, tr("消息"), tr("登录失败：该员工已登录!"), QMessageBox::Ok);
                this->close();
                Widget w;
                w.show();
                w.exec();
                break;
            }
            case ERROR:
            {
                QMessageBox::information(this, tr("消息"), tr("登录失败：该员工未注册!"), QMessageBox::Ok);
                this->close();
                Widget w;
                w.show();
                w.exec();
                break;
            }
        }
    }
    else if(button == this->work_ui.Yesorno->button((QDialogButtonBox::Cancel)))
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

void work_log::read_server()
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
    qDebug()<<message.cmd;
    qDebug()<<"工号："<<message.work_num;
    qDebug()<<"姓名："<<message.work_name;
}

void work_log::on_close_music_clicked()
{
    Widget w;
    //w.sound->stop();
}
