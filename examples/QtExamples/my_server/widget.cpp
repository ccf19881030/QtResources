#include "widget.h"
#include "ui_widget.h"
#include<QDebug>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle("多线程服务端");
    tcpserver=new mytcpserver(this);
    connect(tcpserver,SIGNAL(updataData(QByteArray)),this,SLOT(updataData(QByteArray)));//把数据发送服务端页面
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    ui->pushButton->setEnabled(false);

}

void Widget::updataData(QByteArray byte)
{
    ui->listWidget->addItem(byte);
}

void Widget::on_pushButton_2_clicked()
{
    QString str=ui->lineEdit->text();
    if(str.isEmpty())
        return;
    emit sendData(str.toUtf8());
}
