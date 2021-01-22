#include "widget.h"
#include "ui_widget.h"
#include "tcpsocket.h"
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle("客户端");
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    ui->pushButton->setEnabled(false);
    QString ipAddress="192.168.1.102";
    socket=new tcpsocket(this);
    socket->connectToHost(ipAddress,8010);
    connect(socket,SIGNAL(readyRead()),this,SLOT(readData()));
}

void Widget::readData()
{
    QByteArray buffer=socket->readAll();
    qDebug()<<buffer;
    ui->listWidget->addItem(buffer);
}

void Widget::on_pushButton_2_clicked()
{
    QString str=ui->lineEdit->text();
    if(str.isEmpty())
        return;
    QByteArray byte=str.toUtf8();

    socket->write(byte);
}
