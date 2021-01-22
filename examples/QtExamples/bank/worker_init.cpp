#include "ui_init_worker.h"
#include "worker_init.h"
#include <QDebug>
#include "widget.h"
#include "connect.h"
#include <QProgressDialog>
#include <QMessageBox>
#include <QtNetwork>

extern const QString IP;

void work_init::on_yesorno_clicked(QAbstractButton *button)
{
    Send_MSG str;
    str.work_id =  this->Init_ui.identify->text();               //身份证
    qDebug()<<str.work_id;
    str.work_name = this->Init_ui.work_name->text();              //姓名
    qDebug()<<str.work_name;
    str.work_passward = this->Init_ui.passward->text();           //密码
    qDebug()<<str.work_passward;
    str.cmd = WORKER_INIT;

    if(this->Init_ui.yesorno->button(QDialogButtonBox::Ok) == button)           //判断按下的是否为"确定”按钮
    {
        if(this->Init_ui.identify->text() == "" | this->Init_ui.identify->text() == "" | this->Init_ui.passward->text() == "")
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
            case INIT_SUCCESS:
            {
                QString str1 = QString("注册成功\n工号为%1").arg(message.work_num);
                QMessageBox::information(this, tr("消息"), str1, QMessageBox::Ok);
                this->close();
                Widget w;
                w.show();
                w.exec();
                break;
            }
            case ERROR:
            {
                QMessageBox::information(this, tr("消息"), tr("注册失败：该员工已被注册!"), QMessageBox::Ok);
                this->close();
                Widget w;
                w.show();
                w.exec();
                break;
            }
        }

    }
    else if(button == this->Init_ui.yesorno->button((QDialogButtonBox::Cancel)))
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


void work_init::on_close_music_clicked()
{
    Widget w;
    //w.sound->stop();
}

void work_init::read_server()
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
