#include "frmdata.h"
#include "ui_frmdata.h"
#include "myStaticClass.h"

frmData::frmData(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frmData)
{
    ui->setupUi(this);
    FormHelper::FormInCenter(this);
    FormHelper::FormNotResize(this);
    FormHelper::FormOnTop(this);
    FormHelper::FormOnlyCloseButton(this);
    FormHelper::SetMyStyle(this);

    myData=new myDataHelper(QCoreApplication::applicationDirPath()+"/alarm.db");
    this->ChangeEnable(false);

}

frmData::~frmData()
{
    delete ui;
}

void frmData::ChangeEnable(bool b)
{
    ui->tableView->setEnabled(b);
    ui->btn1->setEnabled(b);
    ui->btn2->setEnabled(b);
    ui->btn3->setEnabled(b);
    ui->btn4->setEnabled(b);
    ui->btn5->setEnabled(b);
}

void frmData::on_btn1_clicked()
{
    QString sql="select * from information";
    myData->BindData(sql,ui->tableView);
}

void frmData::on_btn2_clicked()
{
    QString sql="select * from information";
    QStringList mylist;
    mylist<<"编号"<<"子系统"<<"防区号"<<"事件"<<"日期"<<"时间";
    myData->BindData(sql,ui->tableView,mylist);

    ui->tableView->verticalHeader()->hide();//隐藏左边那列
    ui->tableView->setColumnWidth(0,50);//设置列宽
    ui->tableView->setColumnWidth(1,50);
    ui->tableView->setColumnWidth(2,50);
    ui->tableView->setColumnWidth(3,90);
    ui->tableView->setColumnWidth(4,90);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);//正行选择
}

void frmData::on_btn3_clicked()
{
    QStringList mysql;
    mysql.append("insert into information(subsystem,defenceid,incident,triggerdate,triggertime) values('1','010','防区发生报警1','2011-01-02','12:21:12')");
    mysql.append("insert into information(subsystem,defenceid,incident,triggerdate,triggertime) values('1','011','防区发生报警2','2011-01-02','12:21:12')");
    mysql.append("insert into information(subsystem,defenceid,incident,triggerdate,triggertime) values('1','012','防区发生报警3','2011-01-02','12:21:12')");
    mysql.append("insert into information(subsystem,defenceid,incident,triggerdate,triggertime) values('1','013','防区发生报警4','2011-01-02','12:21:12')");
    mysql.append("insert into information(subsystem,defenceid,incident,triggerdate,triggertime) values('1','014','防区发生报警5','2011-01-02','12:21:12')");
    if (myData->ExecuteSqls(mysql))
    {
        MyMessageBox::ChMessageOnlyOk(tr("批量插入数据成功！"));
    }
    else
    {
        MyMessageBox::ChMessageOnlyOk(tr("批量插入数据失败！"));
    }
}

void frmData::on_btnOpen_clicked()
{
    if (ui->btnOpen->text()=="打开数据库")
    {
        if (myData->OpenDataBase())
        {
            ui->btnOpen->setText("关闭数据库");
            MyMessageBox::ChMessageOnlyOk(tr("打开数据库成功！"));
            this->ChangeEnable(true);
        }
        else
        {
            MyMessageBox::ChMessageOnlyOk(tr("打开数据库失败！"));
        }
    }
    else
    {
        if (myData->CloseDataBase())
        {
            ui->btnOpen->setText("打开数据库");
            MyMessageBox::ChMessageOnlyOk(tr("关闭数据库成功！"));
            this->ChangeEnable(false);
        }
        else
        {
            MyMessageBox::ChMessageOnlyOk(tr("关闭数据库失败！"));
        }
    }

}

void frmData::on_btn4_clicked()
{

}
