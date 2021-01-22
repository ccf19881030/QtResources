#include "maindialog.h"
#include <QTime>
#include <QTimer>
#include "qicmp.h"
#include "ui_maindialog.h"
#include <QHostAddress>
#include <QDebug>
#include <QMessageBox>
#include <QHeaderView>
#include "ui_detail.h"
#define qd qDebug()<<

static int threadCount;
static int onLineCount;

MainDialog::MainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainDialog)
{
    ui->setupUi(this);
    initSpinBox();
    initView();

    timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(updateTime()));
    timer->setInterval(1000);

    QHostInfo::lookupHost("10.1.12.107",
                          this, SLOT(printResults(QHostInfo)));
    //初始化线程状态
    isStop=true;
}

MainDialog::~MainDialog()
{
    delete ui;
}

void MainDialog::initSpinBox()
{

    QVector<int>ipFields=splitIpAddr(getLocalhost());
    if(ipFields.count()<4) return;
    ui->spinBox->setMinimum(0);
    ui->spinBox->setMaximum(255);
    ui->spinBox->setValue(ipFields.at(0));

    ui->spinBox_2->setMinimum(0);
    ui->spinBox_2->setMaximum(255);
    ui->spinBox_2->setValue(ipFields.at(1));

    ui->spinBox_3->setMinimum(0);
    ui->spinBox_3->setMaximum(255);
    ui->spinBox_3->setValue(ipFields.at(2));

    ui->spinBox_4->setMinimum(0);
    ui->spinBox_4->setMaximum(255);
    ui->spinBox_4->setValue(1);

    ui->spinBox_5->setMinimum(0);
    ui->spinBox_5->setMaximum(255);
    ui->spinBox_5->setValue(255);

    ui->spinBox_6->setMinimum(100);
    ui->spinBox_6->setMaximum(30000);
    ui->spinBox_6->setValue(1000);

    ui->spinBox_7->setMinimum(1);
    ui->spinBox_7->setMaximum(50);
    ui->spinBox_7->setValue(10);
}

void MainDialog::initView()
{
    QStringList list;
    list<<tr("IP地址")<<tr("时间")<<tr("主机名")<<tr("返回信息");
    model=new QStandardItemModel(this);
    model->setColumnCount(list.count());
    for(int i=0;i<list.count();i++){
        model->setHeaderData(i,Qt::Horizontal,list.at(i),Qt::DisplayRole);
    }

    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setShowGrid(false);
    ui->tableView->setAlternatingRowColors(true);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->horizontalHeader()->resizeSections(QHeaderView::Interactive);
    ui->tableView->setSortingEnabled(true);
    ui->tableView->setModel(model);

    //查看主机信息
    connect(ui->tableView,SIGNAL(clicked(QModelIndex)),this,SLOT(printResults(QModelIndex)));
}


QString MainDialog::getLocalhost()
{

    QHostInfo hostInfo=QHostInfo::fromName(QHostInfo::localHostName());
    QList<QHostAddress>list=hostInfo.addresses();
    QString myIpAddr;
    foreach(QHostAddress addr,list){
        if(addr.protocol()==QAbstractSocket::IPv4Protocol){
            myIpAddr=addr.toString();
            break;
        }
    }
    return myIpAddr;

}

QVector<int> MainDialog::splitIpAddr(QString ipAddr)
{
    QVector<int> splits;
    if(ipAddr.isEmpty())
        return splits;

    QStringList valList=ipAddr.split('.',QString::SkipEmptyParts);
    for(int i=0;i<valList.count();i++){
        QString val=valList.at(i);
        splits.append(val.toInt());
    }
    return splits;
}

QString MainDialog::constructIpAddr(QVector<int> ipSplits)
{
    if(ipSplits.count()<4)
        return QString();
    return QString(tr("%1.%2.%3.%4").arg(ipSplits.at(0)).arg(ipSplits.at(1)).arg(ipSplits.at(2)).arg(ipSplits.at(3)));
}

QStringList MainDialog::getIpRange()
{
    QString ipAddr=tr("%1.%2.%3").arg(ui->spinBox->value()).arg(ui->spinBox_2->value()).arg(ui->spinBox_3->value());
    int a=ui->spinBox_4->value();
    int b=ui->spinBox_5->value();

    int minimum=qMin(a,b);
    int maximum=a+b-minimum;

    QStringList list;
    for(int i=minimum;i<=maximum;i++){
        list<<ipAddr+tr(".%1").arg(i);
    }
    return list;
}

void MainDialog::on_pushButton_clicked()
{
    //开始计时
    timer->start();
    //记录时间点
    secs=QTime::currentTime().secsTo(QTime(0,0,0));
    //初始化结束的线程个数
    threadCount=0;
    //初始化在线个数
    ui->label_15->setText(tr("0"));
    onLineCount=0;
    //清理上次的数据
    if(model->rowCount()>0)
        model->removeRows(0,model->rowCount());
    //不能同时多次开始ping
    ui->pushButton->setEnabled(false);
    //更改线程状态
    isStop=false;
    //复位选中索引的行号
    modelIndex=QModelIndex();

    QStringList ipRange=getIpRange();
    QIcmp::initThread();
    for(int i=0;i<ui->spinBox_7->value();i++){
        QIcmp *icmp=new QIcmp;
        threadList<<icmp;
        connect(icmp,SIGNAL(message(int,QString,QString)),this,SLOT(updateView(int,QString,QString)));
        connect(icmp,SIGNAL(finished()),this,SLOT(threadFinished()));
        icmp->setIpList(ipRange);
        icmp->setTimeout(ui->spinBox_6->value());
        icmp->start();
    }
}

void MainDialog::updateView(int timeout, QString destIp, QString status)
{
    QList<QStandardItem*>list;
    QStandardItem *item0=new QStandardItem(tr("    ")+destIp);
    QStandardItem *item1=new QStandardItem(tr("    ")+QString::number(timeout)+tr("ms"));
    QStandardItem *item2=new QStandardItem(tr("    %1").arg("请看详细"));
    QStandardItem *item3=new QStandardItem(tr("    ")+status);
    list<<item0<<item1<<item2<<item3;
    model->appendRow(list);
    ui->tableView->scrollToBottom();
    //更新在线个数
    if(status==tr("在线")){
        ui->label_15->setText(QString::number(++onLineCount));
    }
}

void MainDialog::on_pushButton_2_clicked()
{
    if(!ui->pushButton->isEnabled())
        ui->pushButton->setEnabled(true);
    QIcmp::stopThread();
    if(timer->isActive())
        timer->stop();
}

void MainDialog::on_pushButton_3_clicked()
{
    close();
}


void MainDialog::on_spinBox_4_valueChanged(int arg1)
{
    ui->spinBox_5->setValue(arg1);
}


void MainDialog::on_pushButton_4_clicked()
{
    if(model->rowCount()>0)
        model->removeRows(0,model->rowCount());
    ui->label_15->setText(tr("0"));
    ui->label_13->setText(tr("00:00:00"));
}

void MainDialog::updateTime()
{
    ui->label_13->setText(QTime::currentTime().addSecs(secs).toString());
}

void MainDialog::threadFinished()
{
    threadCount++;
    if(threadCount==ui->spinBox_7->value()){
        timer->stop();
        isStop=true;
        QMessageBox::information(this,tr(""),tr("Ping已完成!"),QMessageBox::Yes);
        for(int i=0;i<threadList.count();i++){
            delete threadList.at(i);
        }
        threadList.clear();
    }
}

void MainDialog::printResults(QModelIndex index)
{
    if(isStop){
        modelIndex=index;
    }
}

void MainDialog::on_pushButton_5_clicked()
{
    if(modelIndex.isValid()){
       QString info=model->data(model->index(modelIndex.row(),0),Qt::DisplayRole).toString().trimmed();
       QHostInfo::lookupHost(info,this,SLOT(showDetails(QHostInfo)));
       QDialog *detail=new QDialog;
       ui_dialog.setupUi(detail);
       detail->exec();
       delete detail;
    }
}

void MainDialog::showDetails(QHostInfo info)
{
        QString str=tr("Host: ")+info.hostName();
        str+=tr("\n%1").arg(info.addresses().first().toString());
        ui_dialog.label->setText(str);
}
