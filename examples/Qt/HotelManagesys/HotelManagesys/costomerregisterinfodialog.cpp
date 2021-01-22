#include "costomerregisterinfodialog.h"
#include "ui_costomerregisterinfodialog.h"

#include <QDebug>
#include <QSqlRecord>
#include <QSqlQuery>
#include "app/myhelper.h"

CostomerRegisterInfoDialog::CostomerRegisterInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CostomerRegisterInfoDialog)
{
    ui->setupUi(this);
    this->InitForm();
}

CostomerRegisterInfoDialog::~CostomerRegisterInfoDialog()
{
    delete ui;
}

void CostomerRegisterInfoDialog::InitForm()
{
    ColumnNames[0] = tr("客户编号");
    ColumnNames[1] = tr("姓名");
    ColumnNames[2] = tr("性别");
    ColumnNames[3] = tr("密码");
    ColumnNames[4] = tr("电话");
    ColumnNames[5] = tr("地址");
    ColumnNames[6] = tr("注册时间");
    ColumnNames[7] = tr("备注");

    ColumnWidths[0] = 70;
    ColumnWidths[1] = 100;
    ColumnWidths[2] = 80;
    ColumnWidths[3] = 100;
    ColumnWidths[4] = 100;
    ColumnWidths[5] = 200;
    ColumnWidths[6] = 160;
    ColumnWidths[7] = 200;

    BindCustomInfo("customer",ui->tableView,ColumnNames,ColumnWidths);

    ui->CustomerNo->setEnabled(false);  //客户编号不允许修改
    ui->pbnSave->setEnabled(false);
    ui->pbnCancel->setEnabled(false);

    SetLineEditNoEdit();
    this->connect(ui->tableView,SIGNAL(clicked(QModelIndex)),SLOT(showCustomerInfo()));

    //正则表达式，对输入的内容进行限制，电话号码11位
    QRegExp rxPhone("\\d{11}$");
    QRegExpValidator *regPhone = new QRegExpValidator(rxPhone,this);
    ui->CustomerPhone->setValidator(regPhone);
}

void CostomerRegisterInfoDialog::RefreshInfo()
{
     BindCustomInfo("customer",ui->tableView,ColumnNames,ColumnWidths);
}

void CostomerRegisterInfoDialog::BindCustomInfo(QString tableName, QTableView *tableView, QString columnNames[], int columnWidths[])
{
    QueryModel = new QSqlQueryModel(this);
    QString sql = "SELECT *FROM " + tableName+";";
    qDebug() <<sql;
    QueryModel->setQuery(sql);
    tableView->setModel(QueryModel);

    //依次设置列标题、列宽等
    for (int i = 0;i<tableView->model()->columnCount();i++)
    {
        QueryModel->setHeaderData(i,Qt::Horizontal,columnNames[i]);     //设置列标题
        tableView->setColumnWidth(i,columnWidths[i]);                   //设置列宽
    }

    tableView->horizontalHeader()->setHighlightSections(false);         //点击表头时不对表头光亮
    tableView->setSelectionMode(QAbstractItemView::ContiguousSelection);//选中模式为多行选中
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);     //选中整行
    tableView->setStyleSheet( "QTableView::item:hover{background-color:rgb(92,188,227,200)}"
                              "QTableView::item:selected{background-color:#1B89A1}");
}

void CostomerRegisterInfoDialog::ClearCustomerInfo()
{
    ui->CustomerNo->clear();
    ui->ledSex->clear();
    ui->CustomerName->clear();
    ui->CustomerRePwd->clear();
    ui->CustomerPhone->clear();
    ui->ledCustomDate->clear();
    ui->CustomerAddress->clear();
    ui->CustomerRemark->clear();
}

void CostomerRegisterInfoDialog::SetLineEditNoEdit()
{
    ui->CustomerNo->setEnabled(false);
    ui->ledSex->setEnabled(false);
    ui->CustomerName->setEnabled(false);
    ui->CustomerRePwd->setEnabled(false);
    ui->CustomerPhone->setEnabled(false);
    ui->ledCustomDate->setEnabled(false);
    ui->CustomerAddress->setEnabled(false);
    ui->CustomerRemark->setEnabled(false);
}

void CostomerRegisterInfoDialog::SetLineEditEdit()
{
    ui->CustomerNo->setEnabled(true);
    ui->ledSex->setEnabled(true);
    ui->CustomerName->setEnabled(true);
    ui->CustomerRePwd->setEnabled(true);
    ui->CustomerPhone->setEnabled(true);
    ui->ledCustomDate->setEnabled(true);
    ui->CustomerAddress->setEnabled(true);
    ui->CustomerRemark->setEnabled(true);
}

/*
 *函数功能:实时显示当前表格中客户的信息到控件上
*/
void CostomerRegisterInfoDialog::showCustomerInfo()
{
    QSqlQueryModel userMode(ui->tableView);
    QString sql = "SELECT *FROM customer;";
    qDebug() <<sql;
    userMode.setQuery(QString(sql));
    int Row = ui->tableView->currentIndex().row();
    QSqlRecord record = userMode.record(Row);
    ui->CustomerNo->setText(record.value(0).toString());
    ui->CustomerName->setText(record.value(1).toString());
    ui->ledSex->setText(record.value(2).toString());
    ui->CustomerRePwd->setText(record.value(3).toString());
    ui->CustomerPhone->setText(record.value(4).toString());
    ui->CustomerAddress->setText(record.value(5).toString());
    ui->ledCustomDate->setText(record.value(6).toString());
    ui->CustomerRemark->setText(record.value(7).toString());
}

void CostomerRegisterInfoDialog::on_checkBoxPwd_clicked(bool checked)
{
    if(checked)
    {
        ui->CustomerRePwd->setEchoMode(QLineEdit::Normal);
        ui->checkBoxPwd->setText(tr("隐藏"));
    }
    else
    {
        ui->CustomerRePwd->setEchoMode(QLineEdit::Password);
        ui->checkBoxPwd->setText(tr("显示"));
    }
}

/*
 *函数功能：添加客户信息
*/
void CostomerRegisterInfoDialog::on_pbnAddUser_clicked()
{
    ClearCustomerInfo();
    SetLineEditEdit();

    ui->pbnAddUser->setEnabled(false);
    ui->pbnModify->setEnabled(false);

    ui->pbnSave->setEnabled(true);
    ui->pbnCancel->setEnabled(true);
}

void CostomerRegisterInfoDialog::on_pbnModify_clicked()
{
    SetLineEditEdit();
    ui->CustomerNo->setEnabled(false);      //编号不允许修改

    ui->pbnAddUser->setEnabled(false);
    ui->pbnModify->setEnabled(false);

    ui->pbnSave->setEnabled(true);
    ui->pbnCancel->setEnabled(true);
}

void CostomerRegisterInfoDialog::on_pbnCancel_clicked()
{
    SetLineEditEdit();
    ui->pbnAddUser->setEnabled(true);
    ui->pbnModify->setEnabled(true);

    ui->pbnAddUser->setEnabled(false);
    ui->pbnModify->setEnabled(false);
}

void CostomerRegisterInfoDialog::on_pbnSave_clicked()
{
    QString customerNo = ui->CustomerNo->text();
    QString customerSex = ui->ledSex->text();
    QString customerName = ui->CustomerName->text();
    QString customerPwd = ui->CustomerRePwd->text();
    QString customerPhone = ui->CustomerPhone->text();
    QString customerAddress = ui->CustomerAddress->text();
    QString customeDate = ui->ledCustomDate->text();
    QString customeRemark = ui->CustomerRemark->text();

    if(customerNo.isEmpty() && customerName.isEmpty()&& customerPwd.isEmpty()&&customerPhone.isEmpty())
    {
        myHelper::ShowMessageBoxInfo(tr("必须填满带 * 的内容!"));
    }
    else
    {
        QSqlQuery query;
        bool ok = query.prepare("INSERT INTO Customer (Id, CustomerName,CustomerSex,CustomerPassword,"
                                "CustomerPhone,CustomerAddress,CustomerData,CustomerRemark)"
                                "VALUES (:Id,:CustomerName,:CustomerSex,:CustomerPassword,:CustomerPhone,:CustomerAddress,:CustomerData,:CustomerRemark)");
        query.bindValue(":Id",customerNo);
        query.bindValue(":CustomerName",customerName);
        query.bindValue(":CustomerSex",customerSex);
        query.bindValue(":CustomerPassword",customerPwd);
        query.bindValue(":CustomerPhone",customerPhone);
        query.bindValue(":CustomerAddress",customerAddress);
        query.bindValue(":CustomerData",customeDate);
        query.bindValue(":CustomerRemark",customeRemark);
        query.setForwardOnly(true);
        query.exec();

        if(ok)
        {
            myHelper::ShowMessageBoxInfo(tr("注册成功!"));
        }
        RefreshInfo();

        ui->pbnAddUser->setEnabled(true);
        ui->pbnModify->setEnabled(true);
    }

}
